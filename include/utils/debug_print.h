#ifndef DEBUG_PRINT_GUARD_H
#define DEBUG_PRINT_GUARD_H

typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_NORMAL
} LogType;

/* Same as printf, but with a color and with a print to file. */
extern void debug_print( LogType type, const char* fmt, ... );

#endif /* DEBUG_PRINT_GUARD_H */
