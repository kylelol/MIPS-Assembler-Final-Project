#ifndef __ASSEMBER_H__
#define __ASSEMBER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "vector.h"


/*******************************************************************************
 *
 * Invokes the assembling of a collection of MIPS assembly instructions.
 *
 *******************************************************************************
 *
 * PARAMETERS
 *  mips_assembly       Vector holding the MIPS assembly instructions which
 *          are to be assembled.
 *  machine_code        Empty vector to hold the 32-bit binary instructions
 *          which will result from the assembling.
 *
 ******************************************************************************/
void
assemble(
         vector_string_t * mips_assembly,
         vector_uint_t * machine_code
        );

/*******************************************************************************
 ***** DEFINE YOUR FUNCTIONS BELOW *********************************************
 ******************************************************************************/

typedef enum { ent, txt, end} mipsAssemblerDirectiveEnum;

void convertNewInstruction ( char **instruction, int size);
int assemblerDirectiveInstruction( char *instruction);
int instructionIsALabel(char *instruction);




#endif // __ASSEMBER_H__
