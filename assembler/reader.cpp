//
// Created by Shi Hao on 2019-05-01.
//

#include <string>
#include <sstream>
#include "reader.h"
#include "../Instruction.h"

operation read_op(std::string &asm_line, size_t &pos) {
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
    return 0;
}

imm read_imme(std::string &asm_line, size_t &pos) {
    return 0;
}

void read_spaces(std::string &asm_line, size_t &pos) {
    while (true) {
        char c = asm_line.at(pos);
        if (c != ' ' && c != '\t' && c != ',') {
            return;
        }
        pos++;
    }
}
