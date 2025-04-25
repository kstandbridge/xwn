#include <stddef.h>
#include <stdint.h>

#define true 1
#define false 0
typedef int32_t bool32_t;

typedef struct
{
    uint8_t *Data;
    size_t Length;
} buffer;

static buffer
CStringToBuffer(char *CStr);

static bool32_t
BuffersAreEqual(buffer A, buffer B);

static void
PlatformWrite(buffer String);

static int64_t Main();