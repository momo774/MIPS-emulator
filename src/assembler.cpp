#include "assembler.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iomanip>

void Assembler::assemble(const std::string &filename, Memory &memory)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
        return;
    }

    std::string line;
    uint32_t address = 0;

    std::unordered_map<std::string, uint32_t> labels;

    // First pass: identify labels
    int lineNumber = 0;
    while (std::getline(file, line))
    {
        lineNumber++;
        std::istringstream iss(line);
        std::string label;

        if (iss >> label)
        {
            if (label.back() == ':')
            {
                label.pop_back();
                labels[label] = address;
            }
        }

        std::string opcode;
        iss >> opcode;

        if (opcode == ".word")
        {
            address += 4;
        }
        else if (opcode == ".byte")
        {
            address += 1;
        }
        else if (opcode == ".asciiz")
        {
            std::string str;
            iss >> std::quoted(str);
            address += str.length() + 1;
        }
        else
        {
            address += 4;
        }
    }

    // Second pass: assemble instructions
    file.clear();
    file.seekg(0);
    address = 0;
    lineNumber = 0;

    while (std::getline(file, line))
    {
        lineNumber++;
        std::istringstream iss(line);
        std::string opcode;

        if (iss >> opcode)
        {
            if (opcode.back() == ':')
            {
                continue;
            }

            if (opcode == ".word")
            {
                uint32_t value;
                iss >> value;
                memory.writeWord(address, value);
                address += 4;
            }
            else if (opcode == ".byte")
            {
                uint8_t value;
                iss >> value;
                memory.writeByte(address, value);
                address += 1;
            }
            else if (opcode == ".asciiz")
            {
                std::string str;
                iss >> std::quoted(str);
                for (char c : str)
                {
                    memory.writeByte(address, c);
                    address += 1;
                }
                memory.writeByte(address, 0);
                address += 1;
            }
            else
            {
                // Assemble instruction and store in memory
                // ...
                address += 4;
            }
        }
    }
}