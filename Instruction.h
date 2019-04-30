//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_INSTRUCTION_H
#define PROJECT_3_INSTRUCTION_H


#include <cstdint>
#include "wires.h"

// The simulator should implement the following instructions:
// add, sub, addi, mul, lw, sw, beq, lui, and, andi, or, ori, sll, srl, slti, and sltiu

enum OpCode {
    ADDI = 0b001000u,
    LW = 0b100011u,
    SW = 0b101011u,
    BEQ = 0b000100u,
    LUI = 0b001111u,
    ANDI = 0b001100u,
    ORI = 0b001101u,
    SLTI = 0b001010u,
    SLTIU = 0b001011u,
};

enum FunctCode {
    ADD = 0b100000u,
    SUB = 0b100010u,
    MUL = 0b011000u,
    AND = 0b100100u,
    OR = 0b100101u,
    NOR = 0b100111u,
    SLT = 0b101010u
};

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

    field dest_reg();
    bool is_imm();
};


#endif //PROJECT_3_INSTRUCTION_H
