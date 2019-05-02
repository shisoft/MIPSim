//
// Created by 施昊 on 2019-04-17.
//

#include <string>
#include <sstream>
#include "Instruction.h"
#include "format.h"

Instruction::Instruction(uint32_t inst) : inst(inst) {}

field Instruction::op() const {
    return (field) (this->inst >> 26u);
}

field Instruction::rs() const {
    return (field) (this->inst >> 21u & 0b11111u);
}

field Instruction::rt() const {
    return (field) (this->inst >> 16u & 0b11111u);
}

field Instruction::rd() const {
    return (field) (this->inst >> 11u & 0b11111u);
}

field Instruction::shamt() const {
    return (field) (this->inst >> 6u & 0b11111u);
}

field Instruction::funt() const {
    return (field) (this->inst & 0b111111u);
}

imm Instruction::imme() const {
    return (imm) (this->inst & 0xFFFFu);
}

j Instruction::target() const {
    return (j) (this->inst & 0b1111'1111'1111'1111'1111'1111'11u);
}

field Instruction::dest_reg() {
    auto op = this->op();
    return op == 0 ? this->rd() : this->is_imm() ? this->rt() : 0;
}

bool Instruction::is_imm() const {
    return this->op() != 0;
}

void Instruction::set_nop() {
    this->inst = NOP_INST;
}

bool Instruction::is_nop() const {
    return this->inst == NOP_INST;
}

std::string Instruction::as_hex() const {
    std::stringstream stream;
    stream << "0x" << std::hex << this->inst;
    return stream.str();
}

std::string Instruction::as_bin() const {
    return std::bitset<32>(this->inst).to_string();
}

std::string Instruction::as_asm() const {
    std::stringstream stream;
    auto op = this->op();
    if (this->is_imm()) {
        switch (op) {
            case ADDI:
                stream << "ADDI";
                break;
            case LW:
                stream << "LW";
                break;
            case SW:
                stream << "SW";
                break;
            case BEQ:
                stream << "BEQ";
                break;
            case LUI:
                stream << "LUI";
                break;
            case ANDI:
                stream << "ANDI";
                break;
            case ORI:
                stream << "ORI";
                break;
            case SLTI:
                stream << "SLTI";
                break;
            case SLTIU:
                stream << "SLTIU";
                break;
            default:
                stream << "???I";
                break;
        }
        stream << " " << reg_name(this->rt());
        if (op != LUI) {
            stream << " " << reg_name(this->rs());
        }
        stream << " 0x" << std::hex << this->imme();
    } else {
        auto funct = this->funt();
        switch (funct) {
            case ADD:
                stream << "ADD";
                break;
            case SUB:
                stream << "SUB";
                break;
            case MUL:
                stream << "MUL";
                break;
            case AND:
                stream << "AND";
                break;
            case OR:
                stream << "OR";
                break;
            case NOR:
                stream << "NOR";
                break;
            case SLT:
                stream << "SLT";
                break;
            default:
                stream << "???" << std::bitset<6>(funct).to_string();
                break;
        }
        stream << " " << reg_name(this->rd()) << " " << reg_name(this->rs()) << " " << reg_name(this->rt());
    }
    return stream.str();
}

std::string reg_name(field reg) {
    switch (reg) {
        case 0:
            return "$zero";
        case 1:
            return "$at";
        case 2 ... 3:
            return string_format("$v%d", reg - 2);
        case 4 ... 7:
            return string_format("$a%d", reg - 4);
        case 8 ... 15:
            return string_format("$t%d", reg - 8);
        case 16 ... 23:
            return string_format("$s%d", reg - 16);
        case 24 ... 25:
            return string_format("$t%d", reg - 24 + 8);
        case 26 ... 27:
            return string_format("$k%d", reg - 26);
        case 28:
            return "$gp";
        case 29:
            return "$sp";
        case 30:
            return "$fp";
        case 31:
            return "$ra";
        default:
            return "-";
    }
}

