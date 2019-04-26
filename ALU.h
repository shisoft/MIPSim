//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_ALU_H
#define PROJECT_3_ALU_H

#include "StageLatchess.h"

typedef int64_t alu_res;

enum Op {
    AND,
    OR,
    ADD,
    SUB,
    MUL,
    SLT,
    NOR,
    LS,
    NOP
};

class ALU {
public:
    alu_res compute(data a, data b, Op op);
};


#endif //PROJECT_3_ALU_H
