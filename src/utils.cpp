#include "utils.h"

namespace Utils
{
    int32_t signExtend(uint32_t value, uint32_t bits)
    {
        uint32_t mask = 1 << (bits - 1);
        return static_cast<int32_t>((value ^ mask) - mask);
    }
}