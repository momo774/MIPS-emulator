#include <iostream>
#include "emulator.h"

int main()
{
    Emulator emulator;
    emulator.run("examples/example.asm");
    return 0;
}