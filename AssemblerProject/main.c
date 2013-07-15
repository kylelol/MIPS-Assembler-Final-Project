/*******************************************************************************
 *******************************************************************************
 *******************************************************************************
 *
 * Do NOT modify this file!!!
 *
 *******************************************************************************
 *
 * This file contains main(). The reading of the input file and writing of
 * the output file are invoked in this file.
 *
 * To execute this program, at the command line type:
 *      ./assembler   NAME_OF_INPUT_FILE   NAME_OF_OUTPUT_FILE
 *
 *******************************************************************************
 *******************************************************************************
 ******************************************************************************/

#include "assembler.h"

int
main(int argc, char ** argv)
{
    printf("%d", argc);
    printf("%s\n", argv[0]);
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    
    /*if (argc != 3)
    {
            printf("%d", (8 << 26) + ( 8<<21) + (8<<16) + 1 );
        fprintf(
                stderr,
                "To execute this program, use the following command line call:\n"
               );
        fprintf(
                stderr,
                "\t./assembler   NAME_OF_INPUT_FILE   NAME_OF_OUTPUT_FILE\n"
               );
        exit(1);
    }*/
    
    vector_string_t * mips_assembly = vector_string_create();
    vector_uint_t * machine_code = vector_uint_create();
    
    read_file(argv[1], mips_assembly);
    assemble(mips_assembly, machine_code);
    write_file(argv[2], machine_code);
    
    vector_string_destroy(mips_assembly);
    vector_uint_destroy(machine_code);
    
    return 0;
}



