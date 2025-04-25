#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#define true 1
#define false 0
typedef int32_t bool32_t;

#include "xwn/xwn_string.h"

static void
PlatformWrite(buffer String);

static void
WriteFormat(char *Format, ...);

#include "xwn/xwn_test.h"

static int64_t Main();
