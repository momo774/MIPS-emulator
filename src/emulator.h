#ifndef EMULATOR_H
#define EMULATOR_H

#include <string>
#include "memory.h"
#include "registers.h"
#include "assembler.h"
#include "cache.h"

class Emulator
{
public:
    Emulator();
    void run(const std::string &filename);

private:
    Memory memory;
    Registers registers;
    Assembler assembler;
    Cache cache;
};

#endif