#include <stdio.h>
#include <stdlib.h>

#include "../include/assembler.h"

int main( int argc, char** argv )
{
    if( argc <= 1 )
    {
        fprintf( stderr, "Please specify files." );
        return EXIT_FAILURE;
    }

    /* Starting the assembler on every file starting from end to begin. */
    while( argc-- > 1 )
        start_assembler( argv[ argc ] );

    return EXIT_SUCCESS;
}
