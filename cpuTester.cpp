#include "cpu.hpp"
#include <iostream>

void defaultConstructorTest();

void testCPU();

int main() {

    defaultConstructorTest();
    testCPU();

    return 0;
}

void defaultConstructorTest() {
    CPU cpu;
    return;
}

void testCPU() {
    CPU cpu("main.bin");
    cpu.loopCPU();
}