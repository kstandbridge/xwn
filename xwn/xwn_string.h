
typedef struct
{
    uint8_t *Data;
    size_t Length;
} buffer;

static buffer
CStringToBuffer(char *CStr);

static bool32_t
BuffersAreEqual(buffer A, buffer B);

static buffer
FormatBuffer(uint8_t *Data, char *Format, ...);