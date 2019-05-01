//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_ALU_H
#define PROJECT_3_ALU_H

#include "StageLatchess.h"
#include "wires.h"


enum Op {
    ALU_AND,
    ALU_OR,
    ALU_ADD,
    ALU_SUB,
    ALU_MUL,
    ALU_SLT,
    ALU_NOR,
    ALU_LS,
    ALU_RS,
    ALU_NOP
};

class ALU {
public:
    alu_res compute(reg_dat a, reg_dat b, Op op);
};


#endif //PROJECT_3_ALU_H
