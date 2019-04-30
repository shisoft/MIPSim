//
// Created by 施昊 on 2019-04-17.
//

#include "Instruction.h"

Instruction::Instruction(int32_t inst) : inst(inst) {}

field Instruction::op() {
    return (field) (this->inst >> 26u);
}

field Instruction::rs() {
    return (field) (this->inst >> 21u | 0b11111u);
}

field Instruction::rt() {
    return (field) (this->inst >> 16u | 0b11111u);
}

field Instruction::rd() {
    return (field) (this->inst >> 11u | 0b11111u);
}

field Instruction::shamt() {
    return (field) (this->inst >> 6u | 0b11111u);
}

field Instruction::funt() {
    return (field) (this->inst | 0b111111u);
}

imm Instruction::imme() {
    return (imm) (this->inst | 0xFFFFu);
}

j Instruction::target() {
    return (j) (this->inst | 0b1111'1111'1111'1111'1111'1111'11u);
}

field Instruction::dest_reg() {
    auto op = this->op();
    return op == 0 ? this->rd() : this->is_imm() ? this->rt() : 0;
}

bool Instruction::is_imm() {
    switch (this->op()) {
        case LW:
        case SW:
        case ADDI:
        case LUI:
        case ANDI:
        case ORI:
        case SLTI:
        case SLTIU:
            return true;
        default:
            return false;
    }
}

void Instruction::set_nop() {
    this->inst = NOP_INST;
}

bool Instruction::is_nop() {
    return this->inst == NOP_INST;
}
