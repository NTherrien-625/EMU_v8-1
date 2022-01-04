# EMU_v8-1
Table of Contents:
1. Overview
2. Registers
3. ALU
4. Instruction Format
    4a. Addressing Modes
5. Instructions
    5a. operand8
    5b. ALU Instructions
    5c. Jump/Conditional Instructions
6. Writing your first program!

============
| Overview |
============

The EMU-8v1 arcitecture is an 8-bit, purely EMUlated (I know, very funny), architecture. EMU and its 
iterations have been in development since December 2021 by github user me, NTherrien-625. EMU started
as a personal project demonstrating my knowledge of computer organization, and will contiune to grow
with my education. Maybe there will be an EMU operation system is in the future?

=============
| Registers |
=============

EMU-8v1 has four, 8-bit registers, one 16-bit register, and a flags register.

8-Bit registers:
Registers R1, R2, and R3 are the three general purpose registers. Register PC is the program counter, 
which points to the ROM address storing the next instruction. All four of these registers can be 
manipulated by the programmer.

16-Bit register:
Register IR is the instruction register, which stores the instruction being currently executed. This register
CAN NOT be manipulted by the programmer, I promise I'll explain later.

Flags register:
EMU-8v1 has 2 flags in the flag register, a zero and a sign flag. The zero flag is toggled high when the 
result of a computation is 0, and toggled low when the result of a computation is anything but 0. The sign 
flag is toggled high when the result of a computation is negative, and toggled low when the result of a
computation is 0 or positive. These flags can ONLY be changed by operations, there are no dedicated set
and clear instructions.

=======
| ALU |
=======

The ALU, the key to it all! EMU-8v1 uses an 8-bit ALU with 8 operations, all of which will set/clear the flags.
Additionally, each ALU operation translates to an assembly instruction (which will be described in another section).
The 8 ALU operations are addition, subtraction, bitwise and, bitwise or, bitwise not, bitwise xor, logical shift left, 
and logical shift right.

======================
| Instruction Format |
======================

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

================
| Instructions |
================

A majority of instructions use operand8 in thme, which can mean one of two things depending on the context, determined
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

===============================
| Writing your first program! |
===============================

Step 1:
Open a new text file and type into it

    "ADD R1, 5"

Step 2:
Save the file as "main.emu". When the assembler runs it will look for a file named main.emu to assemble, and no other
.emu files. Make sure you save the file to the same directory you have the emulator saved.

Step 3:
Run the assembler with the command

    "python3 ./assembler.py"

in the same place you have the emulator and main.emu saved.

Step 4:
Compile the emulator with the command

    "make cpuTester"

Step 5:
Run your program with the command 

    "./cpuTester"

the cpu will run on its own and stop when there is no more code to run. Look for the 5 in R1!
