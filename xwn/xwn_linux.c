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

    if(FailedTests == 0)
    {
        WriteFormat("%d out of %d tests passed\n", TotalTests, TotalTests);
    }
    else
    {
        WriteFormat("%d out of %d tests failed\n", FailedTests, TotalTests);
    }

    PlatformExit(Result);
}