
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
    "add", // Done
    "div",
    "jr",
    "mflo",
    "mult",
    "sll",
    "sub",
    "addi", // Done
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
    int k = 0;
    for ( k=0; k < mips_assembly->size; k++)
        printf("%s\n", mips_assembly->elements[k]);
    // Allocate the label array.
    labelArray = (label_node_t**)malloc(sizeof(label_node_t*) * (strlen(mips_assembly->elements[0]) / 2) );
    
    // Loop through the instructions
    int i=0;
    for (i = 0; i < mips_assembly->size; i++)
    {
        // Check if instruction is an assembler directive.
        if ( mips_assembly->elements[i][0] == '.')
        {
            mipsAssemblerDirectiveEnum value = assemblerDirectiveInstruction( mips_assembly->elements[i] );
            
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
        else if ( instructionIsALabel( mips_assembly->elements[i] ) )
        {
            // TODO: Store the index of the label, for jump calls. 
        }
        
        // Otherwise check which MIPS instruction is being executed. 
        else
        {
            // Get the instruction.
            char *instruction = mips_assembly->elements[i];
            instruction = strtok(instruction, " ");
            
            mipsInstructionEnum value = mipsInstructionValue( instruction );
            
            switch (value)
            {
                case add:
                {
                    machine_code->elements[i] = mipsInstructionAdd( instruction );
                    printf("%u\n", machine_code->elements[i]);
                    break;
                }
                case divi:
                {
                    machine_code->elements[i] = mipsInstructionDiv( instruction );
                    printf("%u\n", machine_code->elements[i]);
                    break;
                }
                case jr:
                {
                    
                    break;
                }
                case mflo:
                {
                    machine_code->elements[i] = mipsInstructionDiv( instruction );
                    printf("%u\n", machine_code->elements[i]);
                    break;
                }
                case mult:
                {
                    machine_code->elements[i] = mipsInstructionMult(instruction);
                    printf("%u\n",machine_code->elements[i] );
                    break;
                }
                case sll:
                {
                    
                    break;
                }
                case sub:
                {
                    machine_code->elements[i] = mipsInstructionAddi(instruction);
                    printf("%u\n",machine_code->elements[i] );
                    break;
                }
                case addi:
                {
                    machine_code->elements[i] = mipsInstructionAddi(instruction);
                    printf("%u\n",machine_code->elements[i] );
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
                    machine_code->elements[i] = mipsInstructionLW(instruction);
                    printf("%u\n",machine_code->elements[i] );
                    break;
                }
                case sw:
                {
                    machine_code->elements[i] = mipsInstructionLW(instruction);
                    printf("%u\n",machine_code->elements[i] );
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
    unsigned int registerS = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rt].
    instruction = strtok(NULL, " $");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
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

unsigned int mipsInstructionDiv( char *instruction)
{
    unsigned int returnValue = 0;
    
    // Get the value of R[rt]
    instruction = strtok(NULL, " $,");
    unsigned int registerS = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rt]
    instruction = strtok(NULL, " $,");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
    returnValue = (registerS << 21) + (registerT << 16) + 26;
    
    return returnValue;
    
}


//mult $s, $t
//0000 00ss ssst tttt 0000 0000 0001 1000

unsigned int mipsInstructionMult( char *instruction)
{
    unsigned int returnValue = 0;
    
    // Get the value of R[rt]
    instruction = strtok(NULL, " $,");
    unsigned int registerS = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rt]
    instruction = strtok(NULL, " $,");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
    returnValue = (registerS << 21) + (registerT << 16) + 24;
    
    
    return returnValue;
}


//lw
//lw $t, offset($s)
//1000 11ss ssst tttt iiii iiii iiii iiii

unsigned int mipsInstructionLW( char *instruction)
{
    // Initialize the return value;
    unsigned int returnValue = 0;
    
    // Get the value of R[rt]
    instruction = strtok(NULL, " $,");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
    // Get the immediate value.
    instruction = strtok(NULL, " (");
    unsigned int immediateValue = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rs]
    instruction = strtok(NULL, " $)");
    unsigned int registerS = convertRegisterNameToValue(instruction);

    
    // Generate the machine code.
    returnValue = (35 << 26) + (registerS << 21) + (registerT << 16) + immediateValue;
    
    //int opcode = 35;
    //returnValue = (opcode << 26);
    
    return returnValue;
}

unsigned int mipsInstructionSw( char *instruction)
{
    // Initialize the return value;
    unsigned int returnValue = 0;
    
    // Get the value of R[rt]
    instruction = strtok(NULL, " $,");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
    // Get the immediate value.
    instruction = strtok(NULL, " (");
    unsigned int immediateValue = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rs]
    instruction = strtok(NULL, " $)");
    unsigned int registerS = convertRegisterNameToValue(instruction);
    
    
    // Generate the machine code.
    returnValue = (43 << 26) + (registerS << 21) + (registerT << 16) + immediateValue;
    
    //int opcode = 35;
    //returnValue = (opcode << 26);
    
    return returnValue;
}

//sub
//sub $d, $s, $t
//0000 00ss ssst tttt dddd d000 0010 0010
unsigned int mipsInstructionSub( char *instruction)
{
    unsigned int returnValue = 0;
    
    // Get the value of R[rd].
    instruction = strtok(NULL, " $,");
    unsigned int registerD = convertRegisterNameToValue(instruction);
    
    //Get the value of R[rs].
    instruction = strtok(NULL, " $,");
    unsigned int registerS = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rt].
    instruction = strtok(NULL, " $");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
    // Generate the machine code.
    returnValue = (registerS << 21) + (registerT << 16) + (registerD << 11) + 34;
    
    return returnValue;
}


//mflo
//mflo $d
//0000 0000 0000 0000 dddd d000 0001 0010
unsigned int mipsInstructionMflo( char *instruction)
{
    unsigned int returnValue = 0;
    
    instruction = strtok(NULL, "$");
    unsigned int registerD = convertRegisterNameToValue(instruction);
    
    returnValue = (registerD << 11) + 18;
    
    return returnValue;
}





