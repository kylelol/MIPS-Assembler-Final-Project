
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
#define MIPS_ASSEMBLER_INSTRUCTIONS_ARRAY_SIZE 14
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
    "div", // Done
    "jr",  // Done
    "mflo", // Done
    "mult", // Done
    "sll",  // Done
    "sub",  // Done
    "addi", // Done
    "bltz", // Done
    "bne", // Done
    "lw",   // Done
    "sw",   //Done
    "j",    //Done
    "jal"   //Done
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


const char *mipsRegisterAddress[32] =
{
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "16",
    "17",
    "18",
    "19",
    "20",
    "21",
    "22",
    "23",
    "24",
    "25",
    "26",
    "27",
    "28",
    "29",
    "30",
    "31"
};

void
assemble(
         vector_string_t * mips_assembly,
         vector_uint_t * machine_code
        )
{
    //int k = 0;
    //for ( k=0; k < mips_assembly->size; k++)
        //printf("%s\n", mips_assembly->elements[k]);
    // Allocate the label array.
    //labelArray = (label_node_t**)malloc(sizeof(label_node_t*) * (strlen(mips_assembly->elements[0]) / 2) );
    
    // Loop through the instructions
    int index = 0;
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
            continue;
        }
        
        // Otherwise check which MIPS instruction is being executed. 
        else
        {
            index++;
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
                    machine_code->elements[i] = mipsInstructionJr( instruction );
                    printf("%u\n", machine_code->elements[i]);
                    break;
                }
                case mflo:
                {
                    machine_code->elements[i] = mipsInstructionMflo( instruction );
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
                    machine_code->elements[i] = mipsInstructionSll(instruction);
                    printf("%u\n",machine_code->elements[i] );
                    break;
                }
                case sub:
                {
                    machine_code->elements[i] = mipsInstructionSub(instruction);
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
                    machine_code->elements[i] = mipsInstructionBltz(instruction, mips_assembly, index);
                    printf("%u\n",machine_code->elements[i] );
                    break;
                }
                case bne:
                {
                    machine_code->elements[i] = mipsInstructionBne(instruction, mips_assembly, index);
                    printf("%u\n",machine_code->elements[i] );
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
                    machine_code->elements[i] = mipsInstructionSw(instruction);
                    printf("%u\n",machine_code->elements[i] );
                    break;
                }
                case j:
                {
                    machine_code->elements[i] = mipsInstructionJ(instruction, mips_assembly, index);
                    printf("%u\n",machine_code->elements[i] );
                    break;
                }
                case jal:
                {
                    machine_code->elements[i] = mipsInstructionJal(instruction, mips_assembly, index);
                    printf("%u\n",machine_code->elements[i] );
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
        char *tempRegisterAddr = (char * )mipsRegisterAddress[i];
        //char val = (int)regName[0] - 48;
        
        if (strcmp(regName, tempRegisterName) == 0 || strcmp(regName, tempRegisterAddr) == 0)
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
    returnValue = returnValue | (registerS << 21);
    returnValue = returnValue | (registerT << 16);
    returnValue = returnValue | (registerD << 11);
    returnValue = returnValue | (32);
        
    return returnValue;
    
    
}


//addi $t, $s, imm
//0010 00ss ssst tttt iiii iiii iiii iiii
unsigned int mipsInstructionAddi( char *instruction)
{
    // Initialize the return value;
    unsigned int returnValue = 0;
    
    // Get the value of R[rt]
    instruction = strtok(NULL, " $,");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rs]
    instruction = strtok(NULL, " $,");
    unsigned int registerS = convertRegisterNameToValue(instruction);
    
    // Get the immediate value.
    instruction = strtok(NULL, " ");
    //printf("instruction %s\n", instruction);
    int immediateValue = 0;
    sscanf(instruction, "%d" , &immediateValue);
    //printf("imm value %d\n", immediateValue);
    
    // Generate the machine code. 
    returnValue = returnValue | (8 << 26);
    returnValue = returnValue | (registerS << 21);
    returnValue = returnValue | (registerT << 16);
    returnValue = returnValue | (immediateValue & 0xFFFF);
        
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
    
    returnValue = returnValue | (registerS << 21);
    returnValue = returnValue | (registerT << 16);
    returnValue = returnValue | (26);
    
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
    
    returnValue = returnValue | (registerS << 21);
    returnValue = returnValue | (registerT << 16);
    returnValue = returnValue | (24);
    
    
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
    int immediateValue = 0;
    sscanf(instruction, "%d", &immediateValue);
    //unsigned int immediateValue = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rs]
    instruction = strtok(NULL, " $)");
    unsigned int registerS = convertRegisterNameToValue(instruction);

    
    // Generate the machine code.
    returnValue = returnValue | (35 << 26);
    returnValue = returnValue | (registerS << 21);
    returnValue = returnValue | (registerT << 16);
    returnValue = returnValue | (immediateValue & 0xFFFF);
        
    
    //int opcode = 35;
    //returnValue = (opcode << 26);
    
    return returnValue;
}

//sw $t, offset($s)
//1010 11ss ssst tttt iiii iiii iiii iiii
unsigned int mipsInstructionSw( char *instruction)
{
    // Initialize the return value;
    unsigned int returnValue = 0;
    
    // Get the value of R[rt]
    instruction = strtok(NULL, " $,");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
    // Get the immediate value.
    instruction = strtok(NULL, " (");
    int immediateValue = 0;
    sscanf(instruction, "%d", &immediateValue);
    //unsigned int immediateValue = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rs]
    instruction = strtok(NULL, " $)");
    unsigned int registerS = convertRegisterNameToValue(instruction);
    
    
    // Generate the machine code.
    returnValue = returnValue | (43 << 26);
    returnValue = returnValue | (registerS << 21);
    returnValue = returnValue | (registerT << 16);
    returnValue = returnValue | (immediateValue & 0xFFFF);
    
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
    returnValue = returnValue | (registerS << 21);
    returnValue = returnValue | (registerT << 16);
    returnValue = returnValue | (registerD << 11);
    returnValue = returnValue | (34);
    
    return returnValue;
}


//mflo
//mflo $d
//0000 0000 0000 0000 dddd d000 0001 0010
//works
unsigned int mipsInstructionMflo( char *instruction)
{
    unsigned int returnValue = 0;
    
    instruction = strtok(NULL, "$");
    unsigned int registerD = convertRegisterNameToValue(instruction);
    
    returnValue = returnValue | (registerD << 11);
    returnValue = returnValue | (18);
    
    return returnValue;
}

//jr
//jr $s
//0000 00ss sss0 0000 0000 0000 0000 1000
//works
unsigned int mipsInstructionJr( char *instruction)
{
    unsigned int returnValue = 0;
    
    instruction = strtok(NULL, "$");
    unsigned int registerS = convertRegisterNameToValue(instruction);
    
    returnValue = returnValue | (registerS << 21);
    returnValue = returnValue | (8);
    
    return returnValue;
}

//bltz
//bltz $s, offset
//0000 01ss sss0 0000 iiii iiii iiii iiii

//doesnt work yet?
unsigned int mipsInstructionBltz(char *instruction, vector_string_t *mips_assembly, int instructionIndex)
{
    unsigned int returnValue = 0;
    
    instruction = strtok(NULL, "$,");
    unsigned int registerS = convertRegisterNameToValue(instruction);
    
    //offset may be a label address
    instruction = strtok(NULL, " ");
    //printf("%s", instruction);
    unsigned int labelIndex = calculateJumpOffSet(mips_assembly, instruction);
    
    int offset = labelIndex - instructionIndex;

    if (offset < 0){
        offset -= 1;
    }
    
    returnValue = returnValue | (1 << 26);
    returnValue = returnValue | (registerS << 21);
    returnValue = returnValue | (offset & 0xFFFF);
    
    return returnValue;
}

//
//one off?
//
//bne
//bne $s, $t, offset
//0001 01ss ssst tttt iiii iiii iiii iiii
unsigned int mipsInstructionBne(char *instruction, vector_string_t *mips_assembly, int instructionIndex)
{
    unsigned int returnValue = 0;
    
    instruction = strtok(NULL, " $,");
    unsigned int registerS = convertRegisterNameToValue(instruction);
    
    instruction = strtok(NULL, " $,");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
    instruction = strtok(NULL, " ");
    //printf("%s", instruction);
    unsigned int labelIndex = calculateJumpOffSet(mips_assembly, instruction);
    
    int offset = labelIndex - instructionIndex;
    
    if (offset < 0){
        offset -= 1;
    }
    
    returnValue = returnValue | (5 << 26);
    returnValue = returnValue | (registerS << 21);
    returnValue = returnValue | (registerT << 16);
    returnValue = returnValue | (offset & 0xFFFF);
    //printf("%u", returnValue);
    
    //printf("offset:%d labelIndex:%d instructionIndex:%d\n", offset, labelIndex, instructionIndex);
    
    return returnValue;
    
}

//
//one off????
//
//j
//j target
//0000 10ii iiii iiii iiii iiii iiii iiii
unsigned int mipsInstructionJ(char *instruction, vector_string_t *mips_assembly, int instructionIndex)
{
    int returnValue = 0;
    
    instruction = strtok(NULL, " ");
    int labelIndex = calculateJumpOffSet(mips_assembly, instruction);
    
    int offset = labelIndex - instructionIndex;
    //int offset = -8;
    
    if (offset < 0){
        offset -= 1;
    }
    
    
    returnValue = returnValue | (2 << 26);
    returnValue = returnValue | (offset & 0x3FFFFFF);
    //printf("%u", returnValue);
    
    //returnValue = (2 << 26) + offset;
    
    
    
    return returnValue;
}

//jal
//jal target
//0000 11ii iiii iiii iiii iiii iiii iiii
unsigned int mipsInstructionJal(char *instruction, vector_string_t *mips_assembly, int instructionIndex)
{
    unsigned int returnValue = 0;
    
    instruction = strtok(NULL, " ");
    unsigned int labelIndex = calculateJumpOffSet(mips_assembly, instruction);
    
    int offset = labelIndex - instructionIndex;
    
    if (offset < 0){
        offset -= 1;
    }
    
    returnValue = returnValue | (3 << 26);
    returnValue = returnValue | (offset & 0x3FFFFFF);
    //returnValue = (3 << 26) + offset;
    //printf("%u", returnValue);
    
    return returnValue;
}


//sll
//sll $d, $t, h
//0000 0000 000t tttt dddd dhhh hh00 0000
unsigned int mipsInstructionSll( char *instruction)
{
    unsigned int returnValue = 0;
    
    // Get the value of R[rd].
    instruction = strtok(NULL, " $,");
    unsigned int registerD = convertRegisterNameToValue(instruction);
    
    // Get the value of R[rt].
    instruction = strtok(NULL, " $,");
    unsigned int registerT = convertRegisterNameToValue(instruction);
    
    instruction = strtok(NULL, " ");
    //unsigned int immediateValue = convertRegisterNameToValue(instruction);
    int immediateValue = 0;
    sscanf(instruction, "%d", &immediateValue);
    
    // Generate the machine code.
    returnValue = returnValue | (registerT << 16);
    returnValue = returnValue | (registerD << 11);
    returnValue = returnValue | ((immediateValue << 6) & 0x7FF);
    
    return returnValue;
}



int calculateJumpOffSet(vector_string_t *mips_assembly, char *labelName)
{
    strcat(labelName, ":");
    
    //printf("%s", labelName);
    
    int labelIndex = 0;
    int index = 0;
    int i = 0;
    for ( i = 0; i < mips_assembly->size; i++)
    {
        if ( strcmp(labelName, mips_assembly->elements[i]) == 0)
        {
            labelIndex = index;
        }
        else if ( instructionIsALabel(mips_assembly->elements[i]))
        {
            continue;
        }
        else if ( mips_assembly->elements[i][0] == '.')
        {
            continue;
        }
        else
        {
            index++;
        }
    }
    
    if (labelIndex == 0)
    {
        labelIndex = 1;
    }
    
    return labelIndex;
    
}

