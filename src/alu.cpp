
#include "alu.hpp"

static ALUResult make_result(std::uint8_t value, bool carry = false) {
    return {
        value,
        value == 0,
        (value & 0x80) != 0,
        carry
    };
}

ALUResult alu_add(std::uint8_t a, std::uint8_t b) {
    unsigned sum = static_cast<unsigned>(a) + b;
    return make_result(static_cast<std::uint8_t>(sum), sum > 255);
}

ALUResult alu_sub(std::uint8_t a, std::uint8_t b) {
    std::uint8_t value = static_cast<std::uint8_t>(a - b);
    return make_result(value, a < b);
}

ALUResult alu_and(std::uint8_t a, std::uint8_t b) {
    return make_result(static_cast<std::uint8_t>(a & b));
}

ALUResult alu_or(std::uint8_t a, std::uint8_t b) {
    return make_result(static_cast<std::uint8_t>(a | b));
}

ALUResult alu_xor(std::uint8_t a, std::uint8_t b) {
    return make_result(static_cast<std::uint8_t>(a ^ b));
}

ALUResult alu_not(std::uint8_t a) {
    return make_result(static_cast<std::uint8_t>(~a));
}

ALUResult alu_shl(std::uint8_t a) {
    bool carry = (a & 0x80) != 0;
    return make_result(static_cast<std::uint8_t>(a << 1), carry);
}

ALUResult alu_shr(std::uint8_t a) {
    bool carry = (a & 0x01) != 0;
    return make_result(static_cast<std::uint8_t>(a >> 1), carry);
}

ALUResult alu_inc(std::uint8_t a) {
    return make_result(static_cast<std::uint8_t>(a + 1));
}

ALUResult alu_dec(std::uint8_t a) {
    return make_result(static_cast<std::uint8_t>(a - 1));
}
