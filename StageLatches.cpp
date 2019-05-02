//
// Created by 施昊 on 2019-04-17.
//

#include "StageLatches.h"

IF_ID::IF_ID(p_count npc, const Instruction &ir) : NPC(npc), IR(ir) {}

p_count IF_ID::getNpc() const {
    return NPC;
}

const Instruction &IF_ID::getIr() const {
    return IR;
}

void IF_ID::set_nop() {
    this->IR.set_nop();
}

ID_EX::ID_EX(reg_dat a, reg_dat b, reg_dat imm, p_count npc, const Instruction &ir) : A(a), B(b), IMM(imm), NPC(npc),
                                                                                      IR(ir) {}

reg_dat ID_EX::getA() const {
    return A;
}

reg_dat ID_EX::getB() const {
    return B;
}

reg_dat ID_EX::getImm() const {
    return IMM;
}

p_count ID_EX::getNpc() const {
    return NPC;
}

const Instruction &ID_EX::getIr() const {
    return IR;
}

void ID_EX::set_nop() {
    this->IR.set_nop();
}

EX_MEM::EX_MEM(reg_dat cond, alu_res aluOut, reg_dat b, const Instruction &ir) : cond(cond), ALUOut(aluOut), B(b),
                                                                                 IR(ir) {}

reg_dat EX_MEM::getCond() const {
    return cond;
}

alu_res EX_MEM::getAluOut() const {
    return ALUOut;
}

reg_dat EX_MEM::getB() const {
    return B;
}

Instruction EX_MEM::getIr() const {
    return IR;
}

void EX_MEM::set_nop() {
    this->IR.set_nop();
}

MEM_WB::MEM_WB(reg_dat lmd, alu_res aluOut, const Instruction &ir) : LMD(lmd), ALUOut(aluOut), IR(ir) {}

reg_dat MEM_WB::getLmd() const {
    return LMD;
}

alu_res MEM_WB::getAluOut() const {
    return ALUOut;
}

const Instruction &MEM_WB::getIr() const {
    return IR;
}

void MEM_WB::set_nop() {
    this->IR.set_nop();
}

bool StageLatches::check_reg_data_hazard(reg_num reg, Instruction ins) {
    if (ins.op() == BEQ) return false;
    auto target = ins.dest_reg();
    return target != 0 && target == reg;
}

StageLatches::StageLatches() {}
