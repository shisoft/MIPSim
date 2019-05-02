//
// Created by Shi Hao on 2019-05-01.
//

#ifndef PROJECT_3_ASSEMBLER_H
#define PROJECT_3_ASSEMBLER_H


#include <string>
#include "wires.h"
#include "Instruction.h"

struct operation {
    field op;
    field funct;
};

operation read_op(std::string &asm_line, size_t &pos);
field read_reg(std::string &asm_line, size_t &pos);
imm read_imme(std::string &asm_line, size_t &pos);
void read_spaces(std::string &asm_line, size_t &pos);
Instruction to_instruction(std::string &code);

#endif //PROJECT_3_ASSEMBLER_H
