#include "memory.h"

Memory::Memory()
{
    data.resize(1024 * 1024); // 1MB memory
}

uint32_t Memory::readWord(uint32_t address)
{
    uint32_t value = 0;
    for (int i = 0; i < 4; i++)
    {
        value |= static_cast<uint32_t>(data[address + i]) << (i * 8);
    }
    return value;
}

void Memory::writeWord(uint32_t address, uint32_t value)
{
    for (int i = 0; i < 4; i++)
    {
        data[address + i] = static_cast<uint8_t>((value >> (i * 8)) & 0xFF);
    }
}

uint8_t Memory::readByte(uint32_t address)
{
    return data[address];
}

void Memory::writeByte(uint32_t address, uint8_t value)
{
    data[address] = value;
}