#ifndef LABELS_GUARD_H
#define LABELS_GUARD_H

#include "utils/my_inttypes.h"

typedef enum {

    LABEL_data_byte = 0,  /* .db     */
    LABEL_data_word,      /* .dh     */
    LABEL_data_dword,     /* .dw     */
    LABEL_asciz,          /* .asciz  */
    LABEL_entry,          /* .entry  */
    LABEL_extern,         /* .extern */
    LABEL_UNKNOWN

} LabelTypes;

/* ------------------------------------------------------------------------- */

typedef struct {
    const char* name;
    LabelTypes  label;
    uint8_t     bytes;
} LabelInfo;

/* ------------------------------------------------------------------------- */

/* A function to retrieve the label info based on a string. */
extern const LabelInfo* get_label_info_from_str( const char* str );

/* A function to retrieve the label info based on a type. */
extern const LabelInfo* get_label_info_from_label( LabelTypes type );

#endif /* LABELS_GUARD_H */

