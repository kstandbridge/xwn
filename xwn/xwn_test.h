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
