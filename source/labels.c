#include "../include/labels.h"

#include "utils/my_inttypes.h"
#include <string.h>

static const LabelInfo lookup_table [] ={
    { ".db"     , LABEL_data_byte  },
    { ".dw"     , LABEL_data_word  },
    { ".dh"     , LABEL_data_dword },
    { ".asciz"  , LABEL_asciz      },
    { ".entry"  , LABEL_entry      },
    { ".extern" , LABEL_extern     }
};

static const size_t lookup_table_size = sizeof( lookup_table ) / sizeof( LabelInfo );

/* ------------------------------------------------------------------------- */

const LabelInfo* get_label_info_from_str( const char* str )
{
    size_t i;
    for( i = 0; i < lookup_table_size; i++ )
    {
        const LabelInfo* lookup = &lookup_table[ i ];

        if( strcmp( lookup->name, str ) == 0 )
            return lookup;
    }

    return NULL;
}

/* ------------------------------------------------------------------------- */

const LabelInfo* get_label_info_from_label( LabelTypes type )
{
    size_t i;
    for( i = 0; i < lookup_table_size; i++ )
    {
        const LabelInfo* lookup = &lookup_table[ i ];

        if( type == lookup->label )
            return lookup->name;
    }

    return NULL;
}
