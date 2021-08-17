#include <stdio.h>
#include <stdlib.h>

#include "../include/assembler.h"

int main( int argc, char** argv )
{
    int ret;

    if( argc <= 1 )
    {
        fprintf( stderr, "Please specify files." );
        return EXIT_FAILURE;
    }

    // here
    /* Starting the assembler on every file starting from end to begin. */
    while( argc-- > 1 )
    {
        ret = start_assembler( argv[ argc ] ) == EXIT_FAILURE ?
            EXIT_FAILURE : ret;
    }

    return ret;
}
