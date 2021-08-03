#ifndef DEBUG_LOGGER_GUARD_H
#define DEBUG_LOGGER_GUARD_H

typedef enum { 
    LOG_ERROR,
    LOG_WARNING,
    LOG_NORMAL
} LogType;

/* Same as printf, but with a color and with a print to file. */
extern void debug_log(LogType type, const char* fmt, ...);

#endif /* LOGGER_GUARD_H */
