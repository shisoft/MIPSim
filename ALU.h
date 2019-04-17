//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_ALU_H
#define PROJECT_3_ALU_H

#include "Stages.h"

enum Op {
    AND,
    OR,
    ADD,
    SUB,
    MUL,
    SLT,
    NOR
};

class ALU {
public:
    data compute(data a, data b, Op op);
};


#endif //PROJECT_3_ALU_H
