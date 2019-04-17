//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_STAGES_H
#define PROJECT_3_STAGES_H


#include <cstdint>

typedef int32_t data;

enum Stage {
    IF, ID, EX, MEM, WB
};

class IF_ID {
private:
    data NPC;
    data IR;
public:
    IF_ID(data npc, data ir);

    data getNpc() const;

    data getIr() const;
};

class ID_EX {
private:
    data A;
    data B;
    data IMM;
    data NPC;
public:
    ID_EX(data a, data b, data imm, data npc);

    data getA() const;

    data getB() const;

    data getImm() const;

    data getNpc() const;
};

class EX_MEM {
private:
    data cond;
    data ALUOut;
    data IR;
    data B;
public:
    EX_MEM(data cond, data aluOut, data ir, data b);

    data getCond() const;

    data getAluOut() const;

    data getIr() const;

    data getB() const;
};

class MEM_WD {
private:
    data LMD;
    data ALUOut;
    data IR;
public:
    MEM_WD(data lmd, data aluOut, data ir);

    data getLmd() const;

    data getAluOut() const;

    data getIr() const;
};

class Stages {
    // define stage latches
    IF_ID ifId;
    ID_EX idEx;
    EX_MEM exMem;
    MEM_WD memWd;
};


#endif //PROJECT_3_STAGES_H
