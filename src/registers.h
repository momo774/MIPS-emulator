#ifndef REGISTERS_H
#define REGISTERS_H

#include <cstdint>
#include <array>

class Registers
{
public:
    Registers();
    uint32_t getPC();
    void setPC(uint32_t value);
    void incrementPC(uint32_t offset);

    uint32_t get(uint32_t index);
    void set(uint32_t index, uint32_t value);

private:
    std::array<uint32_t, 32> data;
    uint32_t pc;
};

#endif