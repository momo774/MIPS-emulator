#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cstdint>
#include "memory.h"
#include "registers.h"

class Instructions
{
public:
    static void execute(uint32_t instruction, Memory &memory, Registers &registers);

private:
    static void executeRType(uint32_t instruction, Registers &registers);
    static void executeIType(uint32_t instruction, Memory &memory, Registers &registers);
    static void executeJType(uint32_t instruction, Registers &registers);
};

#endif