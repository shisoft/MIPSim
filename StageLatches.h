//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_STAGELATCHES_H
#define PROJECT_3_STAGELATCHES_H


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

    void set_nop();
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

    void set_nop();
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

    void set_nop();
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

    void set_nop();
};

class StageLatches {
public:
    // define stage latches
    IF_ID ifId = IF_ID(0, Instruction(NOP_INST));
    ID_EX idEx = ID_EX(0, 0, 0, 0, Instruction(NOP_INST));
    EX_MEM exMem = EX_MEM(0, 0, 0, Instruction(NOP_INST));
    MEM_WB memWb = MEM_WB(0, 0, Instruction(NOP_INST));

    bool check_reg_data_hazard(reg_num reg, Instruction ins);

    StageLatches();
};


#endif //PROJECT_3_STAGELATCHES_H
