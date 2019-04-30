//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_STAGELATCHESS_H
#define PROJECT_3_STAGELATCHESS_H


#include <cstdint>
#include "Instruction.h"
#include "RegisterFile.h"
#include "ALU.h"

enum Stage {
    IF, ID, EX, MEM, WB
};

class IF_ID {
private:
    p_count NPC;
    Instruction IR;
public:
    IF_ID(reg_dat npc, const Instruction &ir);

    reg_dat getNpc() const;

    const Instruction &getIr() const;
};

class ID_EX {
private:
    reg_dat A;
    reg_dat B;
    reg_dat IMM;
    p_count NPC;
    Instruction IR;
public:
    ID_EX(reg_dat a, reg_dat b, reg_dat imm, p_count npc, const Instruction &ir);

    reg_dat getA() const;

    reg_dat getB() const;

    reg_dat getImm() const;

    p_count getNpc() const;

    const Instruction &getIr() const;
};

class EX_MEM {
private:
    reg_dat cond;
    alu_res ALUOut;
    reg_dat B;
    Instruction IR;
public:
    EX_MEM(reg_dat cond, alu_res aluOut, reg_dat b, const Instruction &ir);

    reg_dat getCond() const;

    alu_res getAluOut() const;

    reg_dat getB() const;

    Instruction getIr() const;
};

class MEM_WB {
private:
    reg_dat LMD;
    alu_res ALUOut;
    Instruction IR;
public:
    MEM_WB(reg_dat lmd, alu_res aluOut, const Instruction &ir);

    reg_dat getLmd() const;

    alu_res getAluOut() const;

    const Instruction &getIr() const;
};

class StageLatchess {
public:
    // define stage latches
    IF_ID ifId;
    ID_EX idEx;
    EX_MEM exMem;
    MEM_WB memWb;

    bool check_reg_data_hazard(reg_num reg, Instruction ins);
};


#endif //PROJECT_3_STAGELATCHESS_H
