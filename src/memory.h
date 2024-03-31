#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <vector>

class Memory
{
public:
    Memory();
    uint32_t readWord(uint32_t address);
    void writeWord(uint32_t address, uint32_t value);
    uint8_t readByte(uint32_t address);
    void writeByte(uint32_t address, uint8_t value);

private:
    std::vector<uint8_t> data;
};

#endif