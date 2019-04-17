//
// Created by 施昊 on 2019-04-17.
//

#include "Stages.h"

IF_ID::IF_ID(data npc, data ir) : NPC(npc), IR(ir) {}

data IF_ID::getNpc() const {
    return NPC;
}

data IF_ID::getIr() const {
    return IR;
}

ID_EX::ID_EX(data a, data b, data imm, data npc) : A(a), B(b), IMM(imm), NPC(npc) {}

data ID_EX::getA() const {
    return A;
}

data ID_EX::getB() const {
    return B;
}

data ID_EX::getImm() const {
    return IMM;
}

data ID_EX::getNpc() const {
    return NPC;
}

EX_MEM::EX_MEM(data cond, data aluOut, data ir, data b) : cond(cond), ALUOut(aluOut), IR(ir), B(b) {}

data EX_MEM::getCond() const {
    return cond;
}

data EX_MEM::getAluOut() const {
    return ALUOut;
}

data EX_MEM::getIr() const {
    return IR;
}

data EX_MEM::getB() const {
    return B;
}

MEM_WD::MEM_WD(data lmd, data aluOut, data ir) : LMD(lmd), ALUOut(aluOut), IR(ir) {}

data MEM_WD::getLmd() const {
    return LMD;
}

data MEM_WD::getAluOut() const {
    return ALUOut;
}

data MEM_WD::getIr() const {
    return IR;
}
