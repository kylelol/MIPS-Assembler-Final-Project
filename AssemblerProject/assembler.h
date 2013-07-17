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
typedef
struct label_node
{
    int index;
    char * label;
}
label_node_t;

typedef enum { ent, txt, end} mipsAssemblerDirectiveEnum;
typedef enum {add, divi, jr, mflo, mult, sll, sub, addi, bltz, bne, lw, sw, j, jal} mipsInstructionEnum;

void convertNewInstruction ( char **instruction, int size);
int assemblerDirectiveInstruction( char *instruction);
int instructionIsALabel(char *instruction);
int mipsInstructionValue( char *instruction);
int convertRegisterNameToValue( char *regName );
unsigned int mipsInstructionAdd( char *instruction);
unsigned int mipsInstructionAddi( char *instruction);
unsigned int mipsInstructionDiv( char *instruction);
unsigned int mipsInstructionLW( char *instruction);
unsigned int mipsInstructionMult( char *instruction);
unsigned int mipsInstructionSw( char *instruction);
unsigned int mipsInstructionSub( char *instruction);
unsigned int mipsInstructionMflo( char *instruction);
unsigned int mipsInstructionJr( char *instruction);
unsigned int mipsInstructionBltz( char *instruction);




#endif // __ASSEMBER_H__
