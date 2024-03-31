#include "instructions.h"
#include "utils.h"
#include <xcharconv.h>
#include <iostream>

void Instructions::execute(uint32_t instruction, Memory &memory, Registers &registers)
{
    uint32_t opcode = instruction >> 26;

    switch (opcode)
    {
    case 0x00: // R-type instructions
        executeRType(instruction, registers);
        break;
    case 0x02: // J-type instructions
    case 0x03:
        executeJType(instruction, registers);
        break;
    default: // I-type instructions
        executeIType(instruction, memory, registers);
        break;
    }
}

void Instructions::executeRType(uint32_t instruction, Registers &registers)
{
    uint32_t rs = (instruction >> 21) & 0x1F;
    uint32_t rt = (instruction >> 16) & 0x1F;
    uint32_t rd = (instruction >> 11) & 0x1F;
    uint32_t shamt = (instruction >> 6) & 0x1F;
    uint32_t funct = instruction & 0x3F;

    switch (funct)
    {
    case 0x20: // add
        registers.set(rd, registers.get(rs) + registers.get(rt));
        break;
    case 0x22: // sub
        registers.set(rd, registers.get(rs) - registers.get(rt));
        break;
    case 0x24: // and
        registers.set(rd, registers.get(rs) & registers.get(rt));
        break;
    case 0x25: // or
        registers.set(rd, registers.get(rs) | registers.get(rt));
        break;
    case 0x26: // xor
        registers.set(rd, registers.get(rs) ^ registers.get(rt));
        break;
    case 0x27: // nor
        registers.set(rd, ~(registers.get(rs) | registers.get(rt)));
        break;
    case 0x00: // sll
        registers.set(rd, registers.get(rt) << shamt);
        break;
    case 0x02: // srl
        registers.set(rd, registers.get(rt) >> shamt);
        break;
    case 0x03: // sra
        registers.set(rd, static_cast<int32_t>(registers.get(rt)) >> shamt);
        break;
    case 0x08: // jr
        registers.setPC(registers.get(rs));
        break;
    case 0x10:                                // mfhi
        registers.set(rd, registers.get(32)); // HI register
        break;
    case 0x12:                                // mflo
        registers.set(rd, registers.get(33)); // LO register
        break;
    case 0x18: // mult
        int64_t result = static_cast<int64_t>(registers.get(rs)) * static_cast<int64_t>(registers.get(rt));
        registers.set(32, static_cast<uint32_t>(result >> 32)); // HI register
        registers.set(33, static_cast<uint32_t>(result));       // LO register
        break;
    case 0x19: // multu
        uint64_t unsignedResult = static_cast<uint64_t>(registers.get(rs)) * static_cast<uint64_t>(registers.get(rt));
        registers.set(32, static_cast<uint32_t>(unsignedResult >> 32)); // HI register
        registers.set(33, static_cast<uint32_t>(unsignedResult));       // LO register
        break;
    case 0x1A:                                                                           // div
        registers.set(32, static_cast<uint32_t>(registers.get(rs) / registers.get(rt))); // HI register
        registers.set(33, static_cast<uint32_t>(registers.get(rs) % registers.get(rt))); // LO register
        break;
    case 0x1B:                                                    // divu
        registers.set(32, registers.get(rs) / registers.get(rt)); // HI register
        registers.set(33, registers.get(rs) % registers.get(rt)); // LO register
        break;
    default:
        std::cerr << "Unimplemented R-type instruction: " << std::hex << funct << std::endl;
        break;
    }
}

void Instructions::executeIType(uint32_t instruction, Memory &memory, Registers &registers)
{
    uint32_t opcode = instruction >> 26;
    uint32_t rs = (instruction >> 21) & 0x1F;
    uint32_t rt = (instruction >> 16) & 0x1F;
    uint32_t imm = instruction & 0xFFFF;

    switch (opcode)
    {
    case 0x08: // addi
        registers.set(rt, registers.get(rs) + Utils::signExtend(imm, 16));
        break;
    case 0x09: // addiu
        registers.set(rt, registers.get(rs) + Utils::signExtend(imm, 16));
        break;
    case 0x0C: // andi
        registers.set(rt, registers.get(rs) & imm);
        break;
    case 0x0D: // ori
        registers.set(rt, registers.get(rs) | imm);
        break;
    case 0x0E: // xori
        registers.set(rt, registers.get(rs) ^ imm);
        break;
    case 0x0A: // slti
        registers.set(rt, static_cast<int32_t>(registers.get(rs)) < static_cast<int32_t>(Utils::signExtend(imm, 16)));
        break;
    case 0x0B: // sltiu
        registers.set(rt, registers.get(rs) < Utils::signExtend(imm, 16));
        break;
    case 0x23: // lw
    {
        uint32_t address = registers.get(rs) + Utils::signExtend(imm, 16);
        registers.set(rt, memory.readWord(address));
    }
    break;
    case 0x21: // lh
    {
        uint32_t address = registers.get(rs) + Utils::signExtend(imm, 16);
        registers.set(rt, Utils::signExtend(memory.readByte(address) | (memory.readByte(address + 1) << 8), 16));
    }
    break;
    case 0x25: // lhu
    {
        uint32_t address = registers.get(rs) + Utils::signExtend(imm, 16);
        registers.set(rt, memory.readByte(address) | (memory.readByte(address + 1) << 8));
    }
    break;
    case 0x20: // lb
    {
        uint32_t address = registers.get(rs) + Utils::signExtend(imm, 16);
        registers.set(rt, Utils::signExtend(memory.readByte(address), 8));
    }
    break;
    case 0x24: // lbu
    {
        uint32_t address = registers.get(rs) + Utils::signExtend(imm, 16);
        registers.set(rt, memory.readByte(address));
    }
    break;
    case 0x2B: // sw
    {
        uint32_t address = registers.get(rs) + Utils::signExtend(imm, 16);
        memory.writeWord(address, registers.get(rt));
    }
    break;
    case 0x29: // sh
    {
        uint32_t address = registers.get(rs) + Utils::signExtend(imm, 16);
        memory.writeByte(address, registers.get(rt) & 0xFF);
        memory.writeByte(address + 1, (registers.get(rt) >> 8) & 0xFF);
    }
    break;
    case 0x28: // sb
    {
        uint32_t address = registers.get(rs) + Utils::signExtend(imm, 16);
        memory.writeByte(address, registers.get(rt) & 0xFF);
    }
    break;
    case 0x0F: // lui
        registers.set(rt, imm << 16);
        break;
    case 0x04: // beq
        if (registers.get(rs) == registers.get(rt))
        {
            registers.setPC(registers.getPC() + Utils::signExtend(imm, 16) * 4);
        }
        break;
    case 0x05: // bne
        if (registers.get(rs) != registers.get(rt))
        {
            registers.setPC(registers.getPC() + Utils::signExtend(imm, 16) * 4);
        }
        break;
    default:
        std::cerr << "Unimplemented I-type instruction: " << std::hex << opcode << std::endl;
        break;
    }
}

void Instructions::executeJType(uint32_t instruction, Registers &registers)
{
    uint32_t opcode = instruction >> 26;
    uint32_t address = instruction & 0x03FFFFFF;

    switch (opcode)
    {
    case 0x02: // j
        registers.setPC((registers.getPC() & 0xF0000000) | (address << 2));
        break;
    case 0x03: // jal
        registers.set(31, registers.getPC());
        registers.setPC((registers.getPC() & 0xF0000000) | (address << 2));
        break;
    default:
        std::cerr << "Unimplemented J-type instruction: " << std::hex << opcode << std::endl;
        break;
    }
}