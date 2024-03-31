#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include "memory.h"

class Assembler
{
public:
    void assemble(const std::string &filename, Memory &memory);
};

#endif