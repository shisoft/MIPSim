//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_STAGES_H
#define PROJECT_3_STAGES_H


#include <cstdint>

enum Stage {
    IF, ID, EX, MEM, WB
};

struct IF_ID {
    int32_t NPC;
    int32_t IR;
};

struct ID_EX {
    int32_t A;
    int32_t B;
    int32_t IMM;
    int32_t NPC;
};

struct EX_MEM {
    int32_t cond;
    int32_t ALUOut;
};

struct MEM_WD {
    int32_t LMD;
    int32_t ALUOut;
};

class Stages {
    // define latches
    IF_ID ifId;
    ID_EX idEx;
    EX_MEM exMem;
    MEM_WD memWd;
};


#endif //PROJECT_3_STAGES_H
