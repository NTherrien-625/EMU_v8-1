# EMU_v8-1
## Table of Contents:
1. Overview
2. Registers
3. ALU
4. Instructions
5. Writing Your First Program!

# Overview
The EMU-8v1 arcitecture is a purely EMUlated (ba dum tiss), 8-bit architecture. EMU and its iterations have been in development since December 2021 by github user me, NTherrien-625. This architecture is not Turing Complete since it does not have its own data memory, but the next iteration is planned to have its own data memory, expanded instruction set, and C compiler for the architecture using the LLVM framework. EMU started as a personal project demonstrating my knowledge of computer organization, and will contiune to grow with my education. 

# Registers
EMU-8v1 has four, 8-bit registers, one 16-bit register, and a flags register.
### 8-Bit registers:
Registers R1, R2, and R3 are the three general purpose registers. Register PC is the program counter, which points to the ROM address storing the next instruction. All four of these registers can be manipulated by the programmer directly with ALU instructions and the PC can be manipulated indirectly with the jump instructions.
### 16-Bit register:
Register IR is the instruction register, which stores the instruction being currently executed. At each address in the ROM an instruction is held. When the processor arrives at a new place in the ROM the instruction is moved from memory into the IR. This register can not be directly manipulated by the programmer, only indirectly with jump instructions.
### Flags register:
EMU-8v1 has 2 flags in the flag register, a zero and a sign flag. The zero flag is toggled high when the result of a computation is 0, and toggled low when the result of a computation is anything but 0. The sign flag is toggled high when the result of a computation is negative, and toggled low when the result of a computation is 0 or positive. Flags can not be manipulated by the programmer.

# ALU
The ALU is the the heart of any processor. EMU-8v1 uses an 8-bit ALU with 8 operations, all of which can manipulate the flags register. 
* Addition
* Subtraction
* Bitwise AND
* Bitwise OR
* Bitwise NOT
* Bitwise XOR
* Logical Shift Left
* Logical Shift Right

Additionally the ALU operations have one-to-one mapping to an architecture instruction, for example binary subtraction maps to SUB.

# Instructions
## Instruction Format
The EMU-8v1 architecture uses a constant, 16-bit instruction size. Instructions are broken up into 4 blocks.<br><br>
![image](https://user-images.githubusercontent.com/83658619/184535482-309643a5-e8ef-4fd9-a743-574c724cb3ad.png)
### Block 1 - Addressing Modes
Block one is a 2-bit value which designates the addressing mode the processor needs to use for an instruction. An addressing mode indicates where data necessary for an operation is (register, memory, etc). There are four possible addressing modes in the EMU_v8-1 architecture, inspired by the x86 archiecture.
#### Implied
The implied addressing mode indicates that the instruction uses no data. The current architecture iteration has no implied instructions. A good example of an implied instuction would be a "clear zero" instruction (CLZ) which always clears the zero flag.
#### Immediate
The immediate addressing mode indicates that the necessary data is stored in the instruction itself. Instructions in the current architecture like `ADD R1, 5` use immedate addressing. The 5 we want to add into R1 will be given its own sector of the binary instruction that gets assembled.
#### Direct
The direct addressing mode indicates that the necessary data is stored somewhere in memory. The current architecture iteration has no direct instructions since data memory is not present. In the next iteration though when data memory is added direct addressing will be available through instructions formatted as `ADD R2, [5]`. This instruction goes to location 5 in data memory, and add those contents to R2.
#### Register
The register addressing mode indicates that the necessary data is stored in another register. Instructions in the current architecture like `ADD R3, R1` use register addressing. When the processor sees it is in register mode it checks what register it needs data from, then goes over to that register and uses it as necessary.
### Block 2 - Opcode
Block two is a 4-bit value which designates the operation the processor is currently executing. There is a one-to-one mapping of opcodes to the instruction set.
#### 0000 - ADD
```
Instruction Syntax: ADD destinationRegister, operand8
Data Flow:          destinationRegister <- destinationRegister + operand8
Desciprtion:        The sum of destinationRegister and operand8 is placed into destinationRegister, overriding the data
                    present before the instruction.
Flags set:          Zero [Y]
                    Sign [Y]
```
#### 0001 - SUB
```
Instruction Syntax: SUB destinationRegister, operand8
Data Flow:          destinationRegister <- destinationRegister - operand8
Description:        The difference of destinationRegister and operand8 is placed into destinationRegister, overriding 
                    the data present before the instruction.
Flags set:          Zero [Y]
                    Sign [Y]
```
#### 0010 - AND
```
Instruction Syntax: AND destinationRegister, operand8
Data Flow:          destinationRegister <- destinationRegister && operand8
Description:        The and of each bit in destinationRegister with each bit in operand8 is placed into destinationRegister, 
                    overriding the data present before the instruction.
Flags set:          Zero [Y]
                    Sign [Y]
```
#### 0011 - OR
```
Instruction Syntax: OR destinationRegister, operand8
Data Flow:          destinationRegister <- destinationRegister || operand8
Description:        The or of each bit in destinationRegister with each bit in operand8 is placed into destinationRegister, 
                    overriding the data present before the instruction.
Flags set:          Zero [Y]
                    Sign [Y]
```
#### 0100 - NOT
```
Instruction Syntax: NOT destinationRegister
Data Flow:          destinationRegister <- ~destinationRegister
Description:        The not of each bit in destinationRegister is placed into destinationRegister, overriding the data 
                    present before the instruction.
Flags set:          Zero [Y]
                    Sign [Y]
```
#### 0101 - XOR
```
Instruction Syntax: XOR destinationRegister, operand8
Data Flow:          destinationRegister <- destinationRegister ^ operand8
Description:        The xor of each bit in destinationRegister with each bit in operand8 is placed into destinationRegister, 
                    overriding the data present before the instruction.
Flags set:          Zero [Y]
                    Sign [Y]
```
#### 0110 - SHL
```
Instruction Syntax: SHL destinationRegister, operand8
Data Flow:          destinationRegister <- operand8 << 1
Description:        operand8 is shifted left by one bit, the same as multiplying by 2, and is placed into destinationRegister, 
                    overriding the data present before the instruction.
Flags set:          Zero [Y]
                    Sign [Y]
```
#### 0111 - SHR
```
Instruction Syntax: SHR destinationRegister, operand8
Data Flow:          destinationRegister <- operand8 >> 1
Description:        operand8 is shifted left by one bit, the same as multiplying by 2, and is placed into destinationRegister, 
                    overriding the data present before the instruction.
Flags set:          Zero [Y]
                    Sign [Y]
```
#### 1000 - JMP
```
Instruction Syntax: JMP address
Data Flow:          PC <- address
Description:        PC is set to address regardless of flags.
Psuedocode:         PC = address
```
#### 1001 - JG
```
Instruction Syntax: JG address
Data Flow:          PC <- address
Description:        PC is set to address only if Zero = 0 and Sign = 0.
Psuedocode:         IF NOT ZERO AND NOT SIGN
                        PC = address
                    ELSE
                        PC = PC
```
#### 1010 - JL
```
Instruction Syntax: JL address
Data Flow:          PC <- address
Description:        PC is set to address only if Zero = 0 and Sign = 1.
Psuedocode:         IF NOT ZERO AND SIGN
                        PC = address
                    ELSE
                        PC = PC
```
#### 1011 - JE
```
Instruction Syntax: JE address
Data Flow:          PC <- address
Description:        PC is set to address only if Zero = 1 and Sign = 0.
Psuedocode:         IF ZERO AND NOT SIGN
                        PC = address
                    ELSE
                        PC = PC
```
#### 1100 - JGE
```
Instruction Syntax: JGE address
Data Flow:          PC <- address
Description:        PC is set to address if Zero = 1 or Sign = 0.
Psuedocode:         IF ZERO OR NOT SIGN
                        PC = address
                    ELSE
                        PC = PC
```
#### 1101 - JLE
```
Instruction Syntax: JLE address
Data Flow:          PC <- address
Description:        PC is set to address if Zero = 1 or Sign = 1.
Psuedocode:         IF ZERO OR SIGN
                        PC = address
                    ELSE
                        PC = PC
```
#### 1110 - JNE
```
Instruction Syntax: JNE address
Data Flow:          PC <- address
Description:        PC is set to address only if Zero = 0.
Psuedocode:         IF NOT ZERO
                        PC = address
                    ELSE
                        PC = PC
```
#### 1111 - CMP
```
Instruction Syntax: CMP destinationRegister, operand8
Data Flow:          No data is overwritten
Description:        destinationRegister - operand8 is performed but no data is overwriten in destinationRegister.
                    This lets flags get set without any loss of data.
Flags set:          Zero [Y]
                    Sign [Y]
```
### Block 3 - Destination Register
Block three is a 2-bit value which designates the register which will be overwritten by an instruction (if applicable).
### Block 4 - operand8
operand8 refers to the 8-bit value that stores the data needed for an operation. In an implied instruction operand8 is always 0, no data is needed. In an immediate instruction operand8 is assembled into the value it needs. In a direct instruction operand8 is assembled into the memory location data is grabbed from. When the instruction is being decoded, the processor goes to the specified memory location and grabs the data. In a register instruction operand8 is assembled into the register data is grabbed from. When the instruction is being decoded, the processor goes to the specified regiters ad grabs the data.

# Writing your first program!
## Step 1
Open a new text file and type into it

    "ADD R1, 5"

## Step 2
Save the file as "main.emu". When the assembler runs it will look for a file named main.emu to assemble, and no other
.emu files. Make sure you save the file to the same directory you have the emulator saved.

## Step 3
Run the assembler with the command

    "python3 ./assembler.py"

in the same place you have the emulator and main.emu saved.

## Step 4
Compile the emulator with the command

    "make cpuTester"

## Step 5
Run your program with the command 

    "./cpuTester"

the cpu will run on its own and stop when there is no more code to run. Look for the 5 in R1!
