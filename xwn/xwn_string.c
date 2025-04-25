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