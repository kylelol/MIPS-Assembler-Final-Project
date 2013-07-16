
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
#define MIPS_ASSEMBLER_INSTRUCTIONS_ARRAY_SIZE 13
#define MIPS_REGISTER_ARRAY_SIZE 32
#define ZERO_CHAR_VALUE 48

const char *mipsAssemblerDirectiveInstructions[3] =
{
    ".ent", // 0
    ".txt", // 1
    ".end" // 2
    
};

const char *mipsAssemblerInstructions[15] =
{
    "add",
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

const char *mipsRegisters[32] =
{
    "zero",
    "at",
    "v0",
    "v1",
    "a0",
    "a1",
    "a2",
    "a3",
    "t0",
    "t1",
    "t2",
    "t3",
    "t4",
    "t5",
    "t6",
    "t7",
    "s0",
    "s1",
    "s2",
    "s3",
    "s4",
    "s5",
    "s6",
    "s7",
    "t8",
    "t9",
    "k0",
    "k1",
    "gp",
    "sp",
    "fp",
    "ra"
};

label_node_t **labelArray;

void
assemble(
         vector_string_t * mips_assembly,
         vector_uint_t * machine_code
        )
{
    // Allocate the label array.
    labelArray = (label_node_t**)malloc(sizeof(label_node_t*) * (strlen(mips_assembly->elements[0]) / 2) );
    
    // 2D array to hold the instructions. 
    char **instructions = (char**)malloc(sizeof(char*) * strlen(mips_assembly->elements[0]));
    char *newMipsInstruction = strtok(mips_assembly->elements[0], "\r");
       
    // Parse the instructions from the vector_string_t into the 2D array.
    int i=0;
    int labelIndex=0;
    while (newMipsInstruction != NULL)
    {
        // Allocate the space.
        instructions[i] = (char*)malloc(sizeof(char) * strlen(newMipsInstruction));
        
        // Store the instruction.
        instructions[i] = newMipsInstruction;
        
        // If a label, store the index, and label string for lookup later.
        if (instructionIsALabel(newMipsInstruction))
        {
            label_node_t *node = (label_node_t*)malloc(sizeof(label_node_t));
            node->index = i;
            node->label = newMipsInstruction;
            labelArray[labelIndex] = node;
                        
            labelIndex++;
        }
        
        // Move to the next instruction.
        newMipsInstruction = strtok(NULL, "\r");
        
        printf("%s\n", instructions[i]);
        i++;
    }
    
    // Loop through the instructions
    int length = i;
    for (i = 0; i < length; i++)
    {
        // Check if instruction is an assembler directive.
        if ( instructions[i][0] == '.')
        {
            mipsAssemblerDirectiveEnum value = assemblerDirectiveInstruction( instructions[i] );
            
            switch (value)
            {
                // .ent directive.
                case ent:
                {
                    
                    break;
                }
                
                // .txt directive.
                case txt:
                {
                    break;
                }
                    
                // .end directive.
                case end:
                {
                    break;
                }
                  
                // Must be an error.
                default:
                {
                    break;
                }
            }
        }
        
        // Check if instruction is a label
        else if ( instructionIsALabel( instructions[i] ) )
        {
            // TODO: Store the index of the label, for jump calls. 
        }
        
        // Otherwise check which MIPS instruction is being executed. 
        else
        {
            // Get the instruction.
            char *instruction = instructions[i];
            instruction = strtok(instruction, " ");
            
            mipsInstructionEnum value = mipsInstructionValue( instruction );
            
            switch (value)
            {
                case add:
                {
                    machine_code->elements[i] = mipsInstructionAdd( instruction );
                    printf("%d\n", machine_code->elements[i]);
                    break;
                }
                case divi:
                {
                    
                    break;
                }
                case jr:
                {
                    
                    break;
                }
                case mflo:
                {
                    
                    break;
                }
                case mult:
                {
                    
                    break;
                }
                case sll:
                {
                    
                    break;
                }
                case sub:
                {
                    
                    break;
                }
                case addi:
                {
                    machine_code->elements[i] = mipsInstructionAddi(instruction);
                    printf("%d\n",machine_code->elements[i] );
                    break;
                }
                case bltz:
                {
                    
                    break;
                }
                case bne:
                {
                    
                    break;
                }
                case lw:
                {
                    
                    break;
                }
                case sw:
                {
                    
                    break;
                }
                case j:
                {
                    
                    break;
                }
                case jal:
                {
                    
                    break;
                }
                
                // Instruction must be an error.d
                default:
                {
                    break;
                }
            }
        }
        
    }
}

/*******************************************************************************
 ***** IMPLEMENT YOUR FUNCTIONS BELOW ******************************************
 ***** REMEMBER TO DEFINE YOUR FUNCTIONS IN assembler.h ************************
 ******************************************************************************/

#pragma mark MIPS Helper Functions

int mipsInstructionValue( char *instruction)
{
    int i = 0;
    for (i = 0; i < MIPS_ASSEMBLER_INSTRUCTIONS_ARRAY_SIZE; i++)
    {
        char *tempInstruction = (char * )mipsAssemblerInstructions[i];
        
        if ( strcmp(instruction, tempInstruction) == 0)
        {
            return i;
        }
    }
    
    return -1;
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
        return 1;
    }
    
    return 0;
}

int convertRegisterNameToValue( char *regName )
{
    int i = 0;
    for (i = 0; i < MIPS_REGISTER_ARRAY_SIZE; i++)
    {
        char *tempRegisterName = (char * )mipsRegisters[i];
        int val = (int)regName[0] - ZERO_CHAR_VALUE;
        
        if (strcmp(regName, tempRegisterName) == 0 || val == i)
            return i;
    }
    
    return -1;
}

#pragma mark MIPS Instruction Functions

unsigned int mipsInstructionAdd( char *instruction)
{
    unsigned int returnValue = 0;
    
    // Get the value of R[rd].
    instruction = strtok(NULL, " $,");
    unsigned int registerD = convertRegisterNameToValue(instruction);
    
    //Get the value of R[rs].
    instruction = strtok(NULL, " $,");
    unsigned int registerS = (int)instruction[0] - ZERO_CHAR_VALUE;
    
    // Get the value of R[rt].
    instruction = strtok(NULL, " $");
    unsigned int registerT = (int)instruction[0] - ZERO_CHAR_VALUE;
    
    // Generate the machine code.
    returnValue = (registerS << 21) + (registerT << 16) + (registerD << 11) + 32;
        
    return returnValue;
    
    
}
unsigned int mipsInstructionAddi( char *instruction)
{
    // Initialize the return value;
    unsigned int returnValue = 0;
    
    // Get the value of R[rt]
    instruction = strtok(NULL, " $,");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rs]
    instruction = strtok(NULL, " $,");
    unsigned int registerS = (int)instruction[0] - ZERO_CHAR_VALUE;
    
    // Get the immediate value.
    instruction = strtok(NULL, " ");
    unsigned int immediateValue = (int)instruction[0] - ZERO_CHAR_VALUE;
    
    // Generate the machine code. 
    returnValue = (8 << 26) + (registerS << 21) + (registerT << 16) + immediateValue;
        
    return returnValue;
}




