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

static int64_t Main();