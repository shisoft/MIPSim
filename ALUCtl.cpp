//
// Created by 施昊 on 2019-04-17.
//

#include "ALUCtl.h"

Op ALUCtl::decode(Instruction ins) {
    auto op = ins.op();
    auto funct = ins.funt();
    switch (op) {
        case 0:
            switch (funct) {
                case ADD:
                    return ALU_ADD;
                case SUB:
                    return ALU_SUB;
                case MUL:
                    return ALU_MUL;
                case AND:
                    return ALU_AND;
                case OR:
                    return ALU_OR;
                case NOR:
                    return ALU_NOR;
                case SLT:
                    return ALU_SLT;
                case SLL:
                    return ALU_LS;
                case SRL:
                    return ALU_RS;
                default:
                    throw;
            }
            break;
        case ADDI:
        case LW:
        case SW:
            return ALU_ADD;
        case BEQ:
            return ALU_SUB;
        case LUI:
            return ALU_LS;
        case SLTI:
        case SLTIU:
            return ALU_SLT;
        case ANDI:
            return ALU_AND;
        case ORI:
            return ALU_OR;
        default:
            throw;
    }
}
