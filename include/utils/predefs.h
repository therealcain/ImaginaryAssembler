#ifndef PREDEFS_GUARD_H
#define PREDEFS_GUARD_H

#if defined(_WIN32)
# define PLATFORM_WINDOWS
#elif defined(__unix__)
# define PLATFORM_UNIX
#else
# define PLATFORM_UNKNOWN
#endif

/* ------------------------------------------------------------------------- */

#ifndef __cplusplus
# ifndef __STDC_VERSION__
#  define COMPILER_ANSI_C
# endif
#endif

#endif /* PREDEFS_GUARD_H */

