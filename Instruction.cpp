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
