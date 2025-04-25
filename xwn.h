#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#define true 1
#define false 0
typedef int32_t bool32_t;

#include "xwn/xwn_string.h"

static void
PlatformWrite(buffer String);

static void
WriteFormat(char *Format, ...)
{
    uint8_t Buffer[256];
    va_list ArgList;

    va_start(ArgList, Format);
    buffer String = FormatBufferArgs(Buffer, Format, ArgList);
    va_end(ArgList);

    PlatformWrite(String);
}

static volatile int64_t TotalTests = 0;
static volatile int64_t FailedTests = 0;

#define AssertEqualString(Expected, Actual) \
    ++TotalTests; \
    if(!BuffersAreEqual(Expected, Actual)) \
    { \
        ++FailedTests; \
        WriteFormat("%s(%d): equal string assert fail.\n\t\tExpected:\t'%S'\n\t\tActual:\t\t'%S'\n", \
                    __FILE__, __LINE__, Expected, Actual); \
    }

#define AssertNotEqualString(Expected, Actual) \
    ++TotalTests; \
    if(BuffersAreEqual(Expected, Actual)) \
    { \
        ++FailedTests; \
        WriteFormat("%s(%d): not equal string assert fail.\n\t\tExpected:\t'%S'\n\t\tActual:\t\t'%S'\n", \
                    __FILE__, __LINE__, Expected, Actual); \
    }

static int64_t Main();
