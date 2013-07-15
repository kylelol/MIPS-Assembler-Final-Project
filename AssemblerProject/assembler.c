
#include "assembler.h"
#include <string.h>

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

#define MIPS_ASSEMBLER_DIRECTIVE_INSTRUCTIONS_SIZE 3

const char *mipsAssemblerDirectiveInstructions[3] = { ".ent", // 0
                                                  ".txt", // 1
                                                  ".end" // 2
                                                };

const char mipsAssemblerInstructions[15][4] = { "add",
                                          "div",
                                          "jr",
                                          "mflo",
                                          "mult",
                                          "sll",
                                          "sub",
                                          "addi",
                                          "bltz",
                                          "bne",
                                          "lw",
                                          "sw",
                                          "j",
                                          "jal"
                                        };
void
assemble(
         vector_string_t * mips_assembly,
         vector_uint_t * machine_code
        )
{
    
    char **instructions = (char**)malloc(sizeof(char*) * strlen(mips_assembly->elements[0]));
   char *newMipsInstruction = strtok(mips_assembly->elements[0], " ");
   
   // char *newMipsInstruction = mips_assembly->elements[0];
    int i=0;
    while (newMipsInstruction != NULL)
    {
        instructions[i] = (char*)malloc(sizeof(char) * strlen(newMipsInstruction));
        
        instructions[i] = newMipsInstruction;
        newMipsInstruction = strtok(NULL, " ,\r");
        
        printf("%s\n", instructions[i]);
        i++;
    }
    
   convertNewInstruction(instructions, (int)strlen(mips_assembly->elements[0]));
    
    
    
}

/*******************************************************************************
 ***** IMPLEMENT YOUR FUNCTIONS BELOW ******************************************
 ***** REMEMBER TO DEFINE YOUR FUNCTIONS IN assembler.h ************************
 ******************************************************************************/

void convertNewInstruction ( char **instruction, int size)
{
    
    int i = 0;
    for (i=0; i < size; i++)
    {
        // Check if the instruction is an assembler directive instruction.
        // Denoted with a '.' before the instruction.
        if ( instruction[i][0] == '.')
        {
            mipsAssemblerDirectiveEnum value =  assemblerDirectiveInstruction(instruction[i]);
        
            switch (value)
            {
                
                case ent:
                    // get next instruction.
                    printf("%s", instruction[i + 1]);
                    i++;
                    break;
                case txt:
                    // Skip to next instruction
                    break;
                
                case end:
                    // get the next label
                    break;
                
                default:
                    printf("must be an error");
                    break;
            }

        }
        
        else if ( instructionIsALabel(instruction[i]) )
        {
            // TODO: Implement label instructions. 
        }
        
        else
        {
            // TODO: Implement instructions
        }
    }
}



int assemblerDirectiveInstruction( char *instruction)
{
    int i = 0;
    for (i = 0; i < MIPS_ASSEMBLER_DIRECTIVE_INSTRUCTIONS_SIZE; i++ )
    {
        char *tempInstruction = (char * )mipsAssemblerDirectiveInstructions[i];
        
        if ( strcmp(instruction, tempInstruction) == 0 )
        {
            return i;
        }
    }
    
    return -1;
}

int instructionIsALabel(char *instruction)
{
    size_t length = strlen(instruction);
    
    if ( instruction[length-1] == ':')
    {
        printf("\n%c----", instruction[length-1]);
        return 1;
    }
    
    return 0;
}


