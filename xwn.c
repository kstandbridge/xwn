#include "xwn/xwn_string.c"

#ifdef __linux__

#include "xwn/xwn_linux.c"

#else

#error "Unsupported platform"

#endif

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