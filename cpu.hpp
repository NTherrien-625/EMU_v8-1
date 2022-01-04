#ifndef CPU_HPP
#define CPU_HPP

#include <string>

struct fourple {
    int first;
    int second;
    int third;
    int fourth;
};

enum Mode {IMP = 0, IMM, DIR, REG};

class CPU {
private:

    // Registers are signed chars because EMU-8v1 is 8 bits and we want negative numbers
    signed char PC;
    signed char R1;
    signed char R2;
    signed char R3;

    // The instruction register is an unsigned char because instruction are 16 bits long
    unsigned short int IR;

    // The ROM stores instructions and can "technically" be as big as we want, but we will go with 256 x 2 bytes
    unsigned short int ROM[256];

    // Flags will be booleans, the simplest data type for 0/1
    bool zero;
    bool sign;

    // The fourple is used when decoding an instruction
    fourple tempDecode;

public:
    // Default constructor, don't ever use this
    CPU();

    // Overloaded constructor that dumps the contents of the binary to the ROM, always use this
    CPU(std::string bin);

    void fetch();
    void decode();
    void effectiveAddress();
    void execute();
    void dump();
    void loopCPU();
};

#endif
