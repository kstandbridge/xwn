
static buffer
CStringToBuffer(char *CStr)
{
    buffer Result =
    {
        .Data = (uint8_t *)CStr,
        .Length = 0
    };
    uint8_t *At = Result.Data;
    while(*At++)
    {
        ++Result.Length;
    }

    return Result;
}

static bool32_t
BuffersAreEqual(buffer A, buffer B)
{
    bool32_t Result = true;
    if(A.Length == B.Length)
    {
        uint8_t *AtA = A.Data;
        uint8_t *AtB = B.Data;
        size_t Length = A.Length;
        while(Length--)
        {
            if(AtA++ != AtB++)
            {
                Result = false;
                break;
            }
        }
    }
    else
    {
        Result = false;
    }

    return Result;
}

static void
PlatformWrite(buffer String)
{
    asm volatile (
        "mov $1, %%rax\n" 
        "mov $1, %%rdi\n" 
        "mov %0, %%rsi\n"
        "mov %1, %%rdx\n"
        "syscall\n"
        :
        : "r" (String.Data), "r" (String.Length)
        : "rax", "rdi", "rsi", "rdx"
    );
}

static void
PlatformExit(int64_t status)
{
    asm volatile (
        "mov $60, %%rax\n"
        "mov %0, %%rdi\n" 
        "syscall\n"
        :
        : "r" (status)
        : "rax", "rdi"
    );
}

void _start()
{
    int64_t Result = Main();

    PlatformExit(Result);
}