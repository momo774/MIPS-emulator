#include "registers.h"

Registers::Registers() : data{}, pc(0)
{
    // Initialize registers to zero
}

uint32_t Registers::getPC()
{
    return pc;
}

void Registers::setPC(uint32_t value)
{
    pc = value;
}

void Registers::incrementPC(uint32_t offset)
{
    pc += offset;
}

uint32_t Registers::get(uint32_t index)
{
    return data[index];
}

void Registers::set(uint32_t index, uint32_t value)
{
    data[index] = value;
}