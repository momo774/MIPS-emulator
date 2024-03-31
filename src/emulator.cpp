#include "emulator.h"
#include "instructions.h"

Emulator::Emulator() : memory(), registers(), assembler(), cache(1024, 64, 4)
{
    // Initialize emulator components
}

void Emulator::run(const std::string &filename)
{
    // Load and assemble MIPS code
    assembler.assemble(filename, memory);

    // Execute instructions
    while (true)
    {
        uint32_t pc = registers.getPC();
        uint32_t instruction;
        if (cache.read(pc, instruction))
        {
            // Instruction found in cache
        }
        else
        {
            // Instruction not found in cache, read from memory
            instruction = memory.readWord(pc);
            cache.write(pc, instruction);
        }

        Instructions::execute(instruction, memory, registers);
        registers.incrementPC(4);

        if (pc == 0xFFFFFFFF)
        {
            break; // Exit the emulator when PC reaches the end of memory
        }
    }
}