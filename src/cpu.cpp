
#include "cpu.hpp"
#include "alu.hpp"

#include <iomanip>
#include <iostream>

DecodedOpcode decode(Byte op) {
    Byte group = (op >> 4) & 0x0F;
    Byte index = op & 0x0F;

    return {group, index};
}

void step(CPU& cpu) {
    if (cpu.halted) {
        std::cout << "halted\n";
        return;
    }

    Byte op = mem_get(*cpu.mem, cpu.pc);

    switch (op) {
    case OP_HALT:
        cpu.halted = true;
        cpu.pc += 1;
        break;

    case OP_NOP:
        cpu.pc += 1;
        break;

    case OP_ADD: {
        ALUResult r = alu_add(cpu.a, cpu.b);
        cpu.a = r.value;
        cpu.f.z = r.z;
        cpu.f.n = r.n;
        cpu.f.c = r.c;
        cpu.pc += 1;
        break;
    }

    case OP_SUB: {
        ALUResult r = alu_sub(cpu.a, cpu.b);
        cpu.a = r.value;
        cpu.f.z = r.z;
        cpu.f.n = r.n;
        cpu.f.c = r.c;
        cpu.pc += 1;
        break;
    }

    case OP_AND: {
        ALUResult r = alu_and(cpu.a, cpu.b);
        cpu.a = r.value;
        cpu.f.z = r.z;
        cpu.f.n = r.n;
        cpu.f.c = false;
        cpu.pc += 1;
        break;
    }

    case OP_OR: {
        ALUResult r = alu_or(cpu.a, cpu.b);
        cpu.a = r.value;
        cpu.f.z = r.z;
        cpu.f.n = r.n;
        cpu.f.c = false;
        cpu.pc += 1;
        break;
    }

    case OP_XOR: {
        ALUResult r = alu_xor(cpu.a, cpu.b);
        cpu.a = r.value;
        cpu.f.z = r.z;
        cpu.f.n = r.n;
        cpu.f.c = false;
        cpu.pc += 1;
        break;
    }

    case OP_NOT: {
        ALUResult r = alu_not(cpu.a);
        cpu.a = r.value;
        cpu.f.z = r.z;
        cpu.f.n = r.n;
        cpu.f.c = false;
        cpu.pc += 1;
        break;
    }

    case OP_SHL: {
        ALUResult r = alu_shl(cpu.a);
        cpu.a = r.value;
        cpu.f.z = r.z;
        cpu.f.n = r.n;
        cpu.f.c = r.c;
        cpu.pc += 1;
        break;
    }

    case OP_SHR: {
        ALUResult r = alu_shr(cpu.a);
        cpu.a = r.value;
        cpu.f.z = r.z;
        cpu.f.n = r.n;
        cpu.f.c = r.c;
        cpu.pc += 1;
        break;
    }

    case OP_INC: {
        ALUResult r = alu_inc(cpu.a);
        cpu.a = r.value;
        cpu.f.z = r.z;
        cpu.f.n = r.n;
        cpu.pc += 1;
        break;
    }

    case OP_DEC: {
        ALUResult r = alu_dec(cpu.a);
        cpu.a = r.value;
        cpu.f.z = r.z;
        cpu.f.n = r.n;
        cpu.pc += 1;
        break;
    }

    default:
        std::cout << "unknown opcode: 0x"
                  << std::hex << static_cast<unsigned>(op)
                  << std::dec << '\n';
        cpu.pc += 1;
        break;
    }
}

void dump_regs(const CPU& cpu) {
    std::cout << "PC=" << cpu.pc
              << " A=" << static_cast<unsigned>(cpu.a)
              << " B=" << static_cast<unsigned>(cpu.b)
              << " Z=" << cpu.f.z
              << " N=" << cpu.f.n
              << " C=" << cpu.f.c
              << '\n';
}

