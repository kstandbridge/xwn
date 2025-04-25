#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint8_t *Data;
    size_t Length;
} buffer;

static buffer
CStringToBuffer(char *CStr);

static void
PlatformWrite(buffer String);

static int64_t Main();