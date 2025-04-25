static void
RunStringEqualTests()
{
    AssertEqualString(CStringToBuffer("foo bar bas"),
                      CStringToBuffer("foo bar bas"));

    AssertNotEqualString(CStringToBuffer("foo bar bas"),
                         CStringToBuffer("foo bas"));

    AssertNotEqualString(CStringToBuffer("foo bas"),
                         CStringToBuffer("foo bar bas"));

    AssertEqualString(CStringToBuffer("สวัสดีชาวโลก"),
                      CStringToBuffer("สวัสดีชาวโลก"));
}

static void
RunStringFormatTests()
{

    {
        uint8_t Data[64];
        buffer String = FormatBuffer(Data, "before %d after", 42);
        AssertEqualString(CStringToBuffer("before 42 after"), String);
    }

    {
        uint8_t Data[64];
        buffer String = FormatBuffer(Data, "before %d after", 1234567890);
        AssertEqualString(CStringToBuffer("before 1234567890 after"), String);
    }

    {
        uint8_t Data[64];
        buffer String = FormatBuffer(Data, "before %d after", 9876543210);
        AssertEqualString(CStringToBuffer("before 9876543210 after"), String);
    }
}

static void
RunStringTests()
{
    RunStringEqualTests();
    RunStringFormatTests();
}