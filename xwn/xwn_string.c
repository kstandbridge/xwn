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

typedef enum
{
    Format_Unknown,

    Format_Specifier,
    Format_SignedIntegar,
    Format_CString,

    Format_EndOfStream,
} format_token;

typedef struct 
{
    uint8_t *Data;
    uint8_t *Tail;
    uint8_t *At;
} format_state;

static format_token
GetNextFormatToken(format_state *State)
{
    format_token Result = Format_Unknown;

    char C = State->At[0];
    ++State->At;

    switch(C)
    {
        case '\0' : { Result = Format_EndOfStream; } break;
        case '%': { Result = Format_Specifier; } break;
        case 'd':
        case 'i': { Result = Format_SignedIntegar; } break;
        case 's': { Result = Format_CString; } break;
    }
    
    return Result;
}


static buffer
FormatBufferArgs(uint8_t *Data, char *Format, va_list ArgList)
{
    format_state State =
    {
        .Data = Data,
        .Tail = Data,
        .At = (uint8_t *)Format
    };

    bool32_t Parsing = true;
    while(Parsing)
    {
        format_token Token = GetNextFormatToken(&State);
        switch(Token)
        {
            case Format_EndOfStream:
            {
                Parsing = false;
            } break;

            case Format_Specifier:
            {
                format_token ParamToken = GetNextFormatToken(&State);
                switch(ParamToken)
                {
                    case Format_SignedIntegar:
                    {
                        int64_t Value = va_arg(ArgList, int64_t);
                        char *Digits = "0123456789";
                        int64_t Base = 10;
                        uint8_t *Start = State.Tail;
                        do
                        {
                            uint64_t DigitIndex = (Value % Base);
                            char Digit = Digits[DigitIndex];
                            *State.Tail++ = Digit;

                            Value /= Base;
                        } while(Value != 0);
                        uint8_t *End = State.Tail;

                        while(Start < End)
                        {
                            --End;
                            uint8_t Temp = *End;
                            *End = *Start;
                            *Start = Temp;
                            ++Start;
                        }

                    } break;

                    case Format_CString:
                    {
                        uint8_t *At = va_arg(ArgList, uint8_t *);
                        while(At[0] != '\0')
                        {
                            *State.Tail++ = *At++;
                        }
                    } break;

                    case Format_Unknown:
                    case Format_Specifier:
                    case Format_EndOfStream:
                    {
                        // TODO(kstandbridge): Error handling
                        Parsing = false;
                    } break;
                }
            } break;

            case Format_SignedIntegar:
            case Format_CString:
            {
                // TODO(kstandbridge): Error handling
                Parsing = false;
            } break;
            
            case Format_Unknown:
            {
                *State.Tail++ = State.At[-1];
            } break;
        }
    }

    buffer Result = 
    {
        .Data = State.Data,
        .Length = State.Tail - State.Data
    };

    return Result;
}

static buffer
FormatBuffer(uint8_t *Data, char *Format, ...)
{
    va_list ArgList;

    va_start(ArgList, Format);
    buffer Result = FormatBufferArgs(Data, Format, ArgList);
    va_end(ArgList);

    return Result;

}