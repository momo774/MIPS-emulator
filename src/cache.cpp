#include "cache.h"
#include <cmath>

Cache::Cache(uint32_t size, uint32_t blockSize, uint32_t associativity)
    : size(size), blockSize(blockSize), associativity(associativity)
{
    numSets = size / (blockSize * associativity);
    sets.resize(numSets, std::vector<CacheBlock>(associativity));

    for (auto &set : sets)
    {
        for (auto &block : set)
        {
            block.valid = false;
            block.tag = 0;
            block.data.resize(blockSize);
        }
    }
}

bool Cache::read(uint32_t address, uint32_t &value)
{
    uint32_t index = getIndex(address);
    uint32_t tag = getTag(address);

    for (const auto &block : sets[index])
    {
        if (block.valid && block.tag == tag)
        {
            // Cache hit
            uint32_t offset = address & (blockSize - 1);
            value = *reinterpret_cast<const uint32_t *>(&block.data[offset]);
            return true;
        }
    }

    // Cache miss
    return false;
}

void Cache::write(uint32_t address, uint32_t value)
{
    uint32_t index = getIndex(address);
    uint32_t tag = getTag(address);

    // Find an empty block or evict an existing block
    uint32_t blockIndex = 0;
    for (blockIndex = 0; blockIndex < associativity; blockIndex++)
    {
        if (!sets[index][blockIndex].valid)
        {
            break;
        }
    }

    if (blockIndex == associativity)
    {
        // All blocks are valid, evict a random block
        blockIndex = rand() % associativity;
    }

    // Update the cache block
    sets[index][blockIndex].valid = true;
    sets[index][blockIndex].tag = tag;
    uint32_t offset = address & (blockSize - 1);
    *reinterpret_cast<uint32_t *>(&sets[index][blockIndex].data[offset]) = value;
}

uint32_t Cache::getIndex(uint32_t address)
{
    return (address / blockSize) % numSets;
}

uint32_t Cache::getTag(uint32_t address)
{
    return address / (blockSize * numSets);
}