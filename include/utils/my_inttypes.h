#ifndef MY_INTTYPES_GUARD_H
#define MY_INTTYPES_GUARD_H

#include "predefs.h"

#ifdef COMPILER_ANSI_C
/* Assuming machine is 32bit. */
typedef signed char     int8_t;
typedef unsigned char   uint8_t;
typedef signed short    int16_t;
typedef unsigned short  uint16_t;
typedef signed int      int32_t;
typedef unsigned int    uint32_t;
typedef uint32_t        size_t;
typedef int32_t         ssize_t;
#else
# include <stdint.h>
# include <stddef.h>
# ifdef PLATFORM_UNIX
#  include <sys/types.h> /* for ssize_t */
# else
/* Nasty way to override ssize_t if its defined somehow. */
#  define ssize_t int32_t
# endif
#endif

#endif /* MY_INTTYPES_GUARD_H */

