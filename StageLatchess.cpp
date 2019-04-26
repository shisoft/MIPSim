//
// Created by 施昊 on 2019-04-17.
//

#include "StageLatchess.h"

IF_ID::IF_ID(data npc, const Instruction &ir) : NPC(npc), IR(ir) {}

data IF_ID::getNpc() const {
    return NPC;
}

const Instruction &IF_ID::getIr() const {
    return IR;
}

ID_EX::ID_EX(data a, data b, data imm, data npc, const Instruction &ir) : A(a), B(b), IMM(imm), NPC(npc), IR(ir) {}

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

const Instruction &ID_EX::getIr() const {
    return IR;
}

EX_MEM::EX_MEM(data cond, data aluOut, data b, const Instruction &ir) : cond(cond), ALUOut(aluOut), B(b), IR(ir) {}

data EX_MEM::getCond() const {
    return cond;
}

data EX_MEM::getAluOut() const {
    return ALUOut;
}

data EX_MEM::getB() const {
    return B;
}

const Instruction &EX_MEM::getIr() const {
    return IR;
}

MEM_WB::MEM_WB(data lmd, data aluOut, const Instruction &ir) : LMD(lmd), ALUOut(aluOut), IR(ir) {}

data MEM_WB::getLmd() const {
    return LMD;
}

data MEM_WB::getAluOut() const {
    return ALUOut;
}

const Instruction &MEM_WB::getIr() const {
    return IR;
}

bool StageLatchess::check_data_hazard(reg_num reg, Instruction ins) {
    switch (ins.op()) {
        case 0:
            return reg == ins.rd();
        case ADDI:
        case LW:
        case LUI:
        case ANDI:
        case ORI:
        case SLTI:
        case SLTIU:
            return reg == ins.rt();
        default:
            return false;
    }
}
