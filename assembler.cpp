//
// Created by Shi Hao on 2019-05-01.
//

#include <string>
#include <sstream>
#include "assembler.h"
#include "Instruction.h"
#include "format.h"

operation read_op(std::string &asm_line, size_t &pos) {
    read_spaces(asm_line, pos);
    std::stringstream stream;
    while (true) {
        char c = asm_line.at(pos);
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            stream << std::tolower(c);
        } else {
            break;
        }
        pos++;
    }
    auto op_str = stream.str();
    operation op_out = operation();
    if (op_str == "add") {
        op_out.funct = ADD;
    } else if (op_str == "sub") {
        op_out.funct = SUB;
    } else if (op_str == "addi") {
        op_out.op = ADDI;
    } else if (op_str == "mul") {
        op_out.funct = MUL;
    } else if (op_str == "lw") {
        op_out.op = LW;
    } else if (op_str == "sw") {
        op_out.op = SW;
    } else if (op_str == "beq") {
        op_out.op = BEQ;
    } else if (op_str == "lui") {
        op_out.op = LUI;
    } else if (op_str == "and") {
        op_out.funct = AND;
    } else if (op_str == "andi") {
        op_out.op = ANDI;
    } else if (op_str == "or") {
        op_out.funct = OR;
    } else if (op_str == "ori") {
        op_out.op = ORI;
    } else if (op_str == "sll") {
        op_out.funct = SLL;
    } else if (op_str == "srl") {
        op_out.funct = SRL;
    } else if (op_str == "slti") {
        op_out.op = SLTI;
    } else if (op_str == "sltiu") {
        op_out.op = SLTIU;
    }
    return op_out;
}

field read_reg(std::string &asm_line, size_t &pos) {
    read_spaces(asm_line, pos);
    std::stringstream stream;
    if (asm_line.at(pos) != '$') {
        throw std::runtime_error(
                string_format(
                        "Expecting register symbol $ for %s, found '%c'",
                        asm_line.c_str(),
                        asm_line.at(pos)));
    }
    pos++;
    while (true) {
        char c = asm_line.at(pos);
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            stream << std::tolower(c);
        } else {
            break;
        }
        pos++;
    }
    auto reg_str = stream.str();
    auto read_dec = [](std::string &regs) {
        field res = 0;
        // skip the type tag char
        for (int i = 1; i < regs.length(); i++) {
            res = res * 10 + (regs.at(i) - '0');
        }
        return res;
    };
    char tag = reg_str.at(0);
    if (reg_str == "zero") {
        return 0;
    } else if (reg_str == "at") {
        return 1;
    } else if (tag == 'v') {
        return 2 + read_dec(reg_str);
    } else if (tag == 'a') {
        return 4 + read_dec(reg_str);
    } else if (tag == 't') {
        auto id = read_dec(reg_str);
        return id <= 7 ? 8 + id : 24 + id;
    } else if (tag == 's') {
        return 16 + read_dec(reg_str);
    } else if (tag == 'k') {
        return 26 + read_dec(reg_str);
    } else if (reg_str == "gp") {
        return 28;
    } else if (reg_str == "sp") {
        return 29;
    } else if (reg_str == "fp") {
        return 30;
    } else if (reg_str == "ra") {
        return 31;
    }
    return 31;
}

imm read_imme(std::string &asm_line, size_t &pos) {
    read_spaces(asm_line, pos);
    std::stringstream stream;
    if (asm_line.at(pos) != '0' || asm_line.at(pos + 1) != 'x') {
        throw std::runtime_error(
                string_format(
                        "Expecting register hexadecimal number for %s, found '%c%c'",
                        asm_line.c_str(),
                        asm_line.at(pos),
                        asm_line.at(pos + 1)));
    }
    pos += 2;
    while (true) {
        char c = asm_line.at(pos);
        if ((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9')) {
            stream << c;
        } else {
            break;
        }
        pos++;
    }
    imm out;
    stream >> std::hex >> out;
    return out;
}

void read_spaces(std::string &asm_line, size_t &pos) {
    while (true) {
        char c = asm_line.at(pos);
        if (c != ' ' && c != '\t' && c != ',' && c != '(' && c != ')') {
            return;
        }
        pos++;
    }
}

Instruction to_instruction(std::string &code) {
    size_t cursor = 0;
    auto op = read_op(code, cursor);
    uint32_t op_code = op.op;
    uint32_t funct_code = op.funct;
    uint32_t ins = op_code << 26u | funct_code;
    switch (op_code) {
        case LUI:
        {
            uint32_t t = read_reg(code, cursor);
            uint32_t i = read_imme(code, cursor);
            ins = ins | t << 16u | i;
            break;
        }
        case SW:
        case LW:
        {
            uint32_t t = read_reg(code, cursor);
            uint32_t offset = read_imme(code, cursor);
            uint32_t s = read_reg(code, cursor);
            ins = ins | s << 21u | t << 16u | offset;
            break;
        }
        case 0:
        {
            uint32_t d = read_reg(code, cursor);
            uint32_t s = read_reg(code, cursor);
            uint32_t t = read_reg(code, cursor);
            ins = ins | s << 21u | t << 16u | d << 11u;
            break;
        }
        default:
            uint32_t t = read_reg(code, cursor);
            uint32_t s = read_reg(code, cursor);
            uint32_t i = read_imme(code, cursor);
            ins = ins | s << 21u | t << 16u | i;
            break;
    }

    return {ins};
}

