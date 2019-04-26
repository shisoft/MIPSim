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
    field dest_reg();
    imm imme();
    j target();
};


#endif //PROJECT_3_INSTRUCTION_H
