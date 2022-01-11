# EMU_v8-1
## Table of Contents:
1. Overview
2. Registers
    + General Purpose Registers
    + Reserved Registers
4. ALU
5. Instruction Format
    + Addressing Modes
6. Instructions
    + operand8
    + ALU Instructions
    + Jump/Conditional Instructions
7. Writing your first program!
## Overview
The EMU-8v1 arcitecture is an 8-bit, purely EMUlated (I know, very funny), architecture. EMU and its 
iterations have been in development since December 2021 by github user me, NTherrien-625. EMU started
as a personal project demonstrating my knowledge of computer organization, and will contiune to grow
with my education. Maybe there will be an EMU operation system is in the future?
## Registers
EMU-8v1 has three general purpose (GP) registers and three reserved registers.
### GP Registers
The GP registers are each 8-bits wide and can store any value of that size. The registers are named R1-R3.
### Reserved Registers
The first reserved register is the program counter (PC). The PC stores the 8-bit ROM address of the
instruction that is going to be executed NEXT. The PC CAN be altered by the programmer, but should at their
own risk as the program might not execute as expected.

Next up to bat is the instruction register (IR). The IR is 16-bits wide and stores the instruction that is 
CURRENTLY being executed. Unlike the PC, the IR CAN'T be altered by the programmer.

Last is the flags register. The flags register is 2-bits wide, leaving room for two flags that are toggled during
CPU computation, the sign and zero flags. The sign flag is triggered high when the result of and ALU operation
has the left most bit set to 1, and triggered low when the result of and ALU operation has the left most bit set 
to 0. The zero flag is triggered high result of and ALU operation has all bits set to 0, and triggered low when
result of and ALU operation has any bit set to 1.
## ALU
The ALU, the key to it all! EMU-8v1 uses an 8-bit ALU with 8 operations, all of which will set/clear the flags.
Additionally, each ALU operation translates to an assembly instruction (which will be described in another section).
The 8 ALU operations are addition, subtraction, bitwise and, bitwise or, bitwise not, bitwise xor, logical shift left, 
and logical shift right.
## Instruction Format
The EMU-8v1 architecture uses a constant, 16-bit instruction size. The instructions are broken up into 4 blocks.
| = 1 = | == 2 == | = 3 = | ==== 4 ==== |
Block 1:
Block 1 is a 2-bit value that designates the addressing mode of the instruction, resulting in 4 total modes.

    ====================
    | Addressing Modes |
    ====================

    Implied:
    Implied is NOT USED in EMU-8v1, as there are no implied instructions, but implied instructions are planned
    for EMU-8v2.

    Immediate:
    Immediate is used in EMU-8v1. Immediate addressing indicates that the operand is immediatly stored in the
    instruction itself. No additional data needs to be fetched for an immediate (IMM) instruction.

    Direct:
    Direct it NOT USED in EMU-8v1, as there is no way to interface with memory, but methods to do so are planned
    for EMU-8v2.

    Register is used in EMU-8v1. Register addressing indicates that the operand is stored in a register specified
    by the instruction. For the instruction to execute data must be fetched from the register.

Block 2:
Block 2 is a 4-bit value that designates the opcode of the instruction, resulting in 16 total operations, which will
be explained more below.
Block 3:
Block 3 is a 2-bit value that designates the register the result of an operation will be stored. Data can only be 
stored in PC, R1, R2, and R3. The IR is omitted from block 3 to maintain a nice, 2 byte instruction size. Additionally, 
direct manipulation of the IR can lead to unexpected things.
Block 4:
Block 4 is an 8-bit value that can be interpreted in 2 different ways, which is coincidentally how many addressing 
mode are in EMU-8v1. In immediate mode, block 4 will store the 8 bit value being used in the operation. In register
mode, block 4 will store the register that stores the data for the operation.
## Instructions
A majority of instructions use operand8 in them, which can mean one of two things depending on the context, determined
by the programmer.

    ============
    | operand8 |
    ============
    operand8 refers to the 8-bit value that stores the data/points to the data needed to finish the operation. operand8
    can be in one of two forms, both of which are valid where operand8 is used. The first is immediate operand8 where a
    constant value with "4" or "15" is placed into the instruction directly. The second is register operand8 where a register
    is specified with "PC" or "R3" (destinationRegister is specified in the same way).

The instructions present in the EMU-8v1 architecture fall into one of two categories, ALU and Jump/Conditional instructions.
ALU instructions perform computations and set flags. Jump/Conditional instructions jump to different places in the program
based on the flags condition.

    ====================
    | ALU Instructions |
    ====================

    Instruction Syntax: ADD destinationRegister, operand8
    Data Flow:          destinationRegister <- destinationRegister + operand8
    Desciprtion:        The sum of destinationRegister and operand8 is placed into destinationRegister, overriding the data 
                        present before the instruction.
    Flags set:          Zero [Y]
                        Sign [Y]

    Instruction Syntax: SUB destinationRegister, operand8
    Data Flow:          destinationRegister <- destinationRegister - operand8
    Description:        The difference of destinationRegister and operand8 is placed into destinationRegister, overriding 
                        the data present before the instruction.
    Flags set:          Zero [Y]
                        Sign [Y]

    Instruction Syntax: ANFlags set:          Zero [Y]
                        Sign [Y]D destinationRegister, operand8
    Data Flow:          destinationRegister <- destinationRegister && operand8
    Description:        The and of each bit in destinationRegister with each bit in operand8 is placed into destinationRegister, 
                        overriding the data present before the instruction.
    Flags set:          Zero [Y]
                        Sign [Y]

    Instruction Syntax: OR destinationRegister, operand8
    Data Flow:          destinationRegister <- destinationRegister || operand8
    Description:        The or of each bit in destinationRegister with each bit in operand8 is placed into destinationRegister, 
                        overriding the data present before the instruction.
    Flags set:          Zero [Y]
                        Sign [Y]

    Instruction Syntax: NOT destinationRegister
    Data Flow:          destinationRegister <- ~destinationRegister
    Description:        The not of each bit in destinationRegister is placed into destinationRegister, overriding the data 
                        present before the instruction.
    Flags set:          Zero [Y]
                        Sign [Y]

    Instruction Syntax: XOR destinationRegister, operand8
    Data Flow:          destinationRegister <- destinationRegister ^ operand8
    Description:        The xor of each bit in destinationRegister with each bit in operand8 is placed into destinationRegister, 
                        overriding the data present before the instruction.
    Flags set:          Zero [Y]
                        Sign [Y]
    
    Instruction Syntax: SHL destinationRegister, operand8
    Data Flow:          destinationRegister <- operand8 << 1
    Description:        operand8 is shifted left by one bit, the same as multiplying by 2, and is placed into destinationRegister, 
                        overriding the data present before the instruction.
    Flags set:          Zero [Y]
                        Sign [Y]

    Instruction Syntax: SHR destinationRegister, operand8
    Data Flow:          destinationRegister <- operand8 >> 1
    Description:        operand8 is shifted left by one bit, the same as multiplying by 2, and is placed into destinationRegister, 
                        overriding the data present before the instruction.
    Flags set:          Zero [Y]
                        Sign [Y]

    =================================
    | Jump/Conditional Instructions |
    =================================

    Instruction Syntax: JMP address
    Data Flow:          PC <- address
    Description:        PC is set to address regardless of flags.
    Psuedocode:         PC = address

    Instruction Syntax: JG address
    Data Flow:          PC <- address
    Description:        PC is set to address only if Zero = 0 and Sign = 0.
    Psuedocode:         IF NOT ZERO AND NOT SIGN
                            PC = address
                        ELSE
                            PC = PC
    
    Instruction Syntax: JL address
    Data Flow:          PC <- address
    Description:        PC is set to address only if Zero = 0 and Sign = 1.
    Psuedocode:         IF NOT ZERO AND SIGN
                            PC = address
                        ELSE
                            PC = PC
    
    Instruction Syntax: JE address
    Data Flow:          PC <- address
    Description:        PC is set to address only if Zero = 1 and Sign = 0.
    Psuedocode:         IF ZERO AND NOT SIGN
                            PC = address
                        ELSE
                            PC = PC
    
    Instruction Syntax: JGE address
    Data Flow:          PC <- address
    Description:        PC is set to address if Zero = 1 or Sign = 0.
    Psuedocode:         IF ZERO OR NOT SIGN
                            PC = address
                        ELSE
                            PC = PC
    
    Instruction Syntax: JLE address
    Data Flow:          PC <- address
    Description:        PC is set to address if Zero = 1 or Sign = 1.
    Psuedocode:         IF ZERO OR SIGN
                            PC = address
                        ELSE
                            PC = PC

    Instruction Syntax: JNE address
    Data Flow:          PC <- address
    Description:        PC is set to address only if Zero = 0.
    Psuedocode:         IF NOT ZERO
                            PC = address
                        ELSE
                            PC = PC

    Instruction Syntax: CMP destinationRegister, operand8
    Data Flow:          NO DATA IS OVERWRITTEN
    Description:        destinationRegister - operand8 is performed but no data is overwriten in destinationRegister.
                        This lets flags get set without any loss of data.
    Flags set:          Zero [Y]
                        Sign [Y]

## Writing your first program!

Step 1:
Open a new text file and type into it

    "ADD R1, 5"

Step 2:
Save the file as "main.emu". When the assembler runs it will look for a file named main.emu to assemble, and no other
.emu files. Make sure you save the file to the same directory you have the emulator saved.

Step 3:
Run the assembler with the command

    python3 ./assembler.py

in the same place you have the emulator and main.emu saved.

Step 4:
Compile the emulator with the command

    make cpuTester

Step 5:
Run your program with the command 

    ./cpuTester

the cpu will run on its own and stop when there is no more code to run. Look for the 5 in R1!
