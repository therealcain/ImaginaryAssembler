#ifndef LABELS_GUARD_H
#define LABELS_GUARD_H

/*
#define XLABELTYPES     \
    X(LABEL_data_byte)  \
    X(LABEL_data_word)  \
    X(LABEL_data_dword) \
    X(LABEL_asciz)      \
    X(LABEL_entry)      \
    X(LABEL_extern)     \
    X(LABEL_UNKNOWN)
*/

typedef enum {

    LABEL_data_byte = 0,  /* .db     */
    LABEL_data_word,      /* .dh     */
    LABEL_data_dword,     /* .dw     */
    LABEL_asciz,          /* .asciz  */
    LABEL_entry,          /* .entry  */
    LABEL_extern,         /* .extern */
    LABEL_UNKNOWN

} LabelTypes;

/* A hash function to convert string to label. */
extern LabelTypes get_label_from_string(const char* string);

#endif /* LABELS_GUARD_H */

