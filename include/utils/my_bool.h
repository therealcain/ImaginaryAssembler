#ifndef MY_BOOL_GUARD_H
#define MY_BOOL_GUARD_H

#include "predefs.h"

#ifndef __cplusplus
# ifdef COMPILER_ANSI_C
typedef enum { false = 0, true } bool;
# else
#  include <stdbool.h>
# endif
#endif

#endif /* MY_BOOL_GUARD_H */

