#include "cpu.hpp"
#include <fstream>
#include <bitset>
#include <iostream>
#include <iomanip>

CPU::CPU() {
    PC = R1 = R2 = R3 = 0;
    zero = sign = false;
    for (int i = 0; i < 256; ++i)
        ROM[i] = 0;
    IR = 0;
    tempDecode.first = tempDecode.second = tempDecode.third = tempDecode.fourth = 0;
}

CPU::CPU(std::string bin) {
    PC = R1 = R2 = R3 = 0;
    zero = sign = false;

    std::fstream instructions;
    instructions.open(bin);

    int romCounter = 0;
    std::string tempString = "";
    int tempInstruction = 0;
    while (getline(instructions, tempString)) {
        tempInstruction = std::stoi(tempString, nullptr, 2);
        ROM[romCounter] = tempInstruction;
        romCounter++;
    }
    
    instructions.close();

    IR = 0;
    tempDecode.first = tempDecode.second = tempDecode.third = tempDecode.fourth = 0;
}

void CPU::fetch() {
    IR = ROM[PC];
    PC += 1;
}

void CPU::decode() {
    std::bitset<16> instructionBits = std::bitset<16> (IR);
    std::bitset<2> modeBits;
    std::bitset<4> opcodeBits;
    std::bitset<2> registerBits;
    std::bitset<8> operandBits;

    modeBits[1] = instructionBits[15];
    modeBits[0] = instructionBits[14];
    opcodeBits[3] = instructionBits[13];
    opcodeBits[2] = instructionBits[12];
    opcodeBits[1] = instructionBits[11];
    opcodeBits[0] = instructionBits[10];
    registerBits[1] = instructionBits[9];
    registerBits[0] = instructionBits[8];
    operandBits[7] = instructionBits[7];
    operandBits[6] = instructionBits[6];
    operandBits[5] = instructionBits[5];
    operandBits[4] = instructionBits[4];
    operandBits[3] = instructionBits[3];
    operandBits[2] = instructionBits[2];
    operandBits[1] = instructionBits[1];
    operandBits[0] = instructionBits[0];

    tempDecode.first = modeBits.to_ulong();
    tempDecode.second = opcodeBits.to_ulong();
    tempDecode.third = registerBits.to_ulong();
    tempDecode.fourth = operandBits.to_ulong();
}

void CPU::effectiveAddress() {
    switch (tempDecode.first) {
    case IMP:
        break;
    
    case IMM:
        tempDecode.fourth = tempDecode.fourth;
        break;

    case DIR:
        break;

    case REG:
        switch (tempDecode.fourth) {
        case 0:
            tempDecode.fourth = PC;
            break;
        
        case 1:
            tempDecode.fourth = R1;
            break;
        
        case 2:
            tempDecode.fourth = R2;
            break;
        
        case 3:
            tempDecode.fourth = R3;
            break;
        }
    }
}

void CPU::execute() {
    switch (tempDecode.second) {
    case 0:
        // ADD
        switch (tempDecode.third) {
        case 0:
            PC = PC + tempDecode.fourth;

            if (PC < 0)
                sign = true;
            else
                sign = false;
            if (PC == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 1:
            R1 = R1 + tempDecode.fourth;

            if (R1 < 0)
                sign = true;
            else
                sign = false;
            if (R1 == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 2:
            R2 = R2 + tempDecode.fourth;

            if (R2 < 0)
                sign = true;
            else
                sign = false;
            if (R2 == 0)
                zero = true;
            else
                zero = false;

            break;

        case 3:
            R3 = R3 + tempDecode.fourth;

            if (R3 < 0)
                sign = true;
            else
                sign = false;
            if (R3 == 0)
                zero = true;
            else
                zero = false;
            
            break;
        }
        break;
    
    case 1:
        // SUB
        switch (tempDecode.third) {
        case 0:
            PC = PC - tempDecode.fourth;

            if (PC < 0)
                sign = true;
            else
                sign = false;
            if (PC == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 1:
            R1 = R1 - tempDecode.fourth;

            if (R1 < 0)
                sign = true;
            else
                sign = false;
            if (R1 == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 2:
            R2 = R2 - tempDecode.fourth;

            if (R2 < 0)
                sign = true;
            else
                sign = false;
            if (R2 == 0)
                zero = true;
            else
                zero = false;

            break;

        case 3:
            R3 = R3 - tempDecode.fourth;

            if (R3 < 0)
                sign = true;
            else
                sign = false;
            if (R3 == 0)
                zero = true;
            else
                zero = false;
            
            break;
        }
        break;
    
    case 2:
        // AND
        switch (tempDecode.third) {
        case 0:
            PC = PC & tempDecode.fourth;

            if (PC < 0)
                sign = true;
            else
                sign = false;
            if (PC == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 1:
            R1 = R1 & tempDecode.fourth;

            if (R1 < 0)
                sign = true;
            else
                sign = false;
            if (R1 == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 2:
            R2 = R2 & tempDecode.fourth;

            if (R2 < 0)
                sign = true;
            else
                sign = false;
            if (R2 == 0)
                zero = true;
            else
                zero = false;

            break;

        case 3:
            R3 = R3 & tempDecode.fourth;

            if (R3 < 0)
                sign = true;
            else
                sign = false;
            if (R3 == 0)
                zero = true;
            else
                zero = false;
            
            break;
        }
        break;
    
    case 3:
        // OR
        switch (tempDecode.third) {
        case 0:
            PC = PC | tempDecode.fourth;

            if (PC < 0)
                sign = true;
            else
                sign = false;
            if (PC == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 1:
            R1 = R1 | tempDecode.fourth;

            if (R1 < 0)
                sign = true;
            else
                sign = false;
            if (R1 == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 2:
            R2 = R2 | tempDecode.fourth;

            if (R2 < 0)
                sign = true;
            else
                sign = false;
            if (R2 == 0)
                zero = true;
            else
                zero = false;

            break;

        case 3:
            //std::cout << "Adding to R3..." << std::endl;
            R3 = R3 | tempDecode.fourth;

            // Set flags
            if (R3 < 0)
                sign = true;
            else
                sign = false;
            if (R3 == 0)
                zero = true;
            else
                zero = false;
            
            break;
        }
        break;
    
    case 4:
        // NOT
        switch (tempDecode.third) {
        case 0:
            PC = ~tempDecode.fourth;

            if (PC < 0)
                sign = true;
            else
                sign = false;
            if (PC == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 1:
            R1 = ~tempDecode.fourth;

            if (R1 < 0)
                sign = true;
            else
                sign = false;
            if (R1 == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 2:
            R2 = ~tempDecode.fourth;

            if (R2 < 0)
                sign = true;
            else
                sign = false;
            if (R2 == 0)
                zero = true;
            else
                zero = false;

            break;

        case 3:
            R3 = ~tempDecode.fourth;

            if (R3 < 0)
                sign = true;
            else
                sign = false;
            if (R3 == 0)
                zero = true;
            else
                zero = false;

            break;
        }
        break;
    
    case 5:
        // XOR
        switch (tempDecode.third) {
        case 0:
            PC = PC ^ tempDecode.fourth;

            if (PC < 0)
                sign = true;
            else
                sign = false;
            if (PC == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 1:
            R1 = R1 ^ tempDecode.fourth;

            if (R1 < 0)
                sign = true;
            else
                sign = false;
            if (R1 == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 2:
            R2 = R2 ^ tempDecode.fourth;

            if (R2 < 0)
                sign = true;
            else
                sign = false;
            if (R2 == 0)
                zero = true;
            else
                zero = false;

            break;

        case 3:
            R3 = R3 ^ tempDecode.fourth;

            // Set flags
            if (R3 < 0)
                sign = true;
            else
                sign = false;
            if (R3 == 0)
                zero = true;
            else
                zero = false;

            break;
        }
        break;
    
    case 6:
        // SHL
        switch (tempDecode.third) {
        case 0:
            PC = (tempDecode.fourth << 1);

            if (PC < 0)
                sign = true;
            else
                sign = false;
            if (PC == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 1:
            R1 = (tempDecode.fourth << 1);

            if (R1 < 0)
                sign = true;
            else
                sign = false;
            if (R1 == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 2:
            R2 = (tempDecode.fourth << 1);

            if (R2 < 0)
                sign = true;
            else
                sign = false;
            if (R2 == 0)
                zero = true;
            else
                zero = false;

            break;

        case 3:
            R3 = (tempDecode.fourth << 1);

            if (R3 < 0)
                sign = true;
            else
                sign = false;
            if (R3 == 0)
                zero = true;
            else
                zero = false;

            break;
        }
        break;
    
    case 7:
        // SHR
        switch (tempDecode.third) {
        case 0:
            PC = tempDecode.fourth >> 1;

            if (PC < 0)
                sign = true;
            else
                sign = false;
            if (PC == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 1:
            R1 = tempDecode.fourth >> 1;

            if (R1 < 0)
                sign = true;
            else
                sign = false;
            if (R1 == 0)
                zero = true;
            else
                zero = false;

            break;
        
        case 2:
            R2 = tempDecode.fourth >> 1;

            if (R2 < 0)
                sign = true;
            else
                sign = false;
            if (R2 == 0)
                zero = true;
            else
                zero = false;

            break;

        case 3:
            R3 = tempDecode.fourth >> 1;

            if (R3 < 0)
                sign = true;
            else
                sign = false;
            if (R3 == 0)
                zero = true;
            else
                zero = false;

            break;
        }
        break;
    
    case 8:
        // JMP
        PC = tempDecode.fourth;
        break;
    
    case 9:
        // JG
        if (!sign and !zero)
            PC = tempDecode.fourth;
        break;
    
    case 10:
        // JL
        if (sign and !zero)
            PC = tempDecode.fourth;
        break;
    
    case 11:
        // JE
        if (zero)
            PC = tempDecode.fourth;
        break;
    
    case 12:
        // JGE
        if (!sign or zero)
            PC = tempDecode.fourth;
        break;
    
    case 13:
        // JLE
        if (sign or zero)
            PC = tempDecode.fourth;
        break;
    
    case 14:
        // JNE
        if (!zero)
            PC = tempDecode.fourth;
        break;
    
    case 15:
        // CMP
        signed char temp;
        switch (tempDecode.third) {
        case 0:
            temp = PC - tempDecode.fourth;
            if (temp < 0)
                sign = true;
            else 
                sign = false;
            if (temp == 0)
                zero = true;
            else
                zero = false;
            break;

        case 1:
            temp = R1 - tempDecode.fourth;

            if (temp < 0)
                sign = true;
            else 
                sign = false;
            if (temp == 0)
                zero = true;
            else
                zero = false;
            break;
        
        case 2:
            temp = R2 - tempDecode.fourth;

            if (temp < 0)
                sign = true;
            else 
                sign = false;
            if (temp == 0)
                zero = true;
            else
                zero = false;
            break;

        case 3:
            temp = R3 - tempDecode.fourth;

            if (temp < 0)
                sign = true;
            else 
                sign = false;
            if (temp == 0)
                zero = true;
            else
                zero = false;
            break;
        }
    }
}

void CPU::dump() {
    std::cout << "======================" << std::endl;
    std::cout << "|                    |" << std::endl;
    std::cout << "|    R1         R2   |" << std::endl;
    std::cout << "|  =====      =====  |" << std::endl;
    std::cout << "|  |" << std::setw(3) << int(R1) << "|      |" << std::setw(3) << int(R2) << "|  |" << std::endl;
    std::cout << "|  =====      =====  |" << std::endl;
    std::cout << "|                    |" << std::endl;
    std::cout << "|    R3         PC   |" << std::endl;
    std::cout << "|  =====      =====  |" << std::endl;
    std::cout << "|  |" << std::setw(3) << int(R3) << "|      |" << std::setw(3) << int(PC) << "|  |" << std::endl;
    std::cout << "|  =====      =====  |" << std::endl;
    std::cout << "|                    |" << std::endl;
    std::cout << "======================" << std::endl;
}

void CPU::loopCPU() {
    dump();
    do {
        fetch();
        decode();
        effectiveAddress();
        execute();
        dump();
    } 
    while (IR != 0);
}