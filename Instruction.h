//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_INSTRUCTION_H
#define PROJECT_3_INSTRUCTION_H


#include <cstdint>

typedef uint8_t field;
typedef int16_t imm;
typedef int32_t j;

// The simulator should implement the following instructions:
// add, sub, addi, mul, lw, sw, beq, lui, and, andi, or, ori, sll, srl, slti, and sltiu

class Instruction {
private:
    uint32_t inst;
public:
    Instruction(int32_t inst);
    field op();
    field rs();
    field rt();
    field rd();
    field shamt();
    field funt();
    imm imme();
    j target();
};


#endif //PROJECT_3_INSTRUCTION_H
