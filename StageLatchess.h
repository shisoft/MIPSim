//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_STAGELATCHESS_H
#define PROJECT_3_STAGELATCHESS_H


#include <cstdint>
#include "Instruction.h"
#include "RegisterFile.h"

typedef int32_t data;

enum Stage {
    IF, ID, EX, MEM, WB
};

class IF_ID {
private:
    data NPC;
    Instruction IR;
public:
    IF_ID(data npc, const Instruction &ir);

    data getNpc() const;

    const Instruction &getIr() const;
};

class ID_EX {
private:
    data A;
    data B;
    data IMM;
    data NPC;
    Instruction IR;
public:
    ID_EX(data a, data b, data imm, data npc, const Instruction &ir);

    data getA() const;

    data getB() const;

    data getImm() const;

    data getNpc() const;

    const Instruction &getIr() const;
};

class EX_MEM {
private:
    data cond;
    data ALUOut;
    data B;
    Instruction IR;
public:
    EX_MEM(data cond, data aluOut, data b, const Instruction &ir);

    data getCond() const;

    data getAluOut() const;

    data getB() const;

    const Instruction &getIr() const;
};

class MEM_WB {
private:
    data LMD;
    data ALUOut;
    Instruction IR;
public:
    MEM_WB(data lmd, data aluOut, const Instruction &ir);

    data getLmd() const;

    data getAluOut() const;

    const Instruction &getIr() const;
};

class StageLatchess {
public:
    // define stage latches
    IF_ID ifId;
    ID_EX idEx;
    EX_MEM exMem;
    MEM_WB memWb;

    bool check_data_hazard(reg_num reg, Instruction ins);
};


#endif //PROJECT_3_STAGELATCHESS_H
