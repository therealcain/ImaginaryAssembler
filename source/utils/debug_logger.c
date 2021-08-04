#include "../../include/utils/debug_logger.h"

#include <stdio.h>
#include <stdarg.h>

#define DEBUG_PREFIX "DEBUG LOGGER"

/* Print the message in a color mode. */
static
void print_colored(LogType type, const char* fmt, va_list arg)
{
#ifndef NDEBUG
    switch(type)
    {
    case LOG_WARNING:
        printf("\x1B[33m"); /* Yellow color code. */
        break;

    case LOG_ERROR:
        printf("\x1B[31m"); /* Red color code. */
        break;

    default:
        break;
    }

    vprintf(fmt, arg);

    printf("\x1B[0m"); /* Reset color codes. */
#endif
}
/* ------------------------------------------------------------------------- */

void debug_log(LogType type, const char* fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    print_colored(type, fmt, args);
    va_end(args);
}