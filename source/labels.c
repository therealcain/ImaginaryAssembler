#include "../include/labels.h"

#include "../include/utils/stdint.h"
#include <string.h>

typedef struct { 
    char*      name; 
    LabelTypes label;
} HashLabel;

static const HashLabel lookup_table[] = {
    { ".db"     , LABEL_data_byte  },
    { ".dw"     , LABEL_data_word  },
    { ".dh"     , LABEL_data_dword },
    { ".asciz"  , LABEL_asciz      },
    { ".entry"  , LABEL_entry      },
    { ".extern" , LABEL_extern     }
};

static const size_t lookup_table_size = sizeof(lookup_table) / sizeof(HashLabel);

LabelTypes get_label_from_string(const char* string)
{
    size_t i;
    for(i = 0; i < lookup_table_size; ++i)
    {
        const HashLabel* lookup = &lookup_table[i];

        if(strcmp(lookup->name, string) == 0)
            return lookup->label;
    }

    return LABEL_UNKNOWN;
}

const char* get_string_from_label(LabelTypes type)
{
    size_t i;
    for(i = 0; i < lookup_table_size; ++i)
    {
        const HashLabel* lookup = &lookup_table[i];

        if(type == lookup->label)
            return lookup->name;
    }

    return NULL;
}
