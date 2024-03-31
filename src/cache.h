#ifndef CACHE_H
#define CACHE_H

#include <cstdint>
#include <vector>

class Cache
{
public:
    Cache(uint32_t size, uint32_t blockSize, uint32_t associativity);
    bool read(uint32_t address, uint32_t &value);
    void write(uint32_t address, uint32_t value);

private:
    struct CacheBlock
    {
        bool valid;
        uint32_t tag;
        std::vector<uint8_t> data;
    };

    uint32_t size;
    uint32_t blockSize;
    uint32_t associativity;
    uint32_t numSets;
    std::vector<std::vector<CacheBlock>> sets;

    uint32_t getIndex(uint32_t address);
    uint32_t getTag(uint32_t address);
};

#endif