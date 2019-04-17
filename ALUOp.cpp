//
// Created by Shi Hao on 2019-04-18.
//

#include "ALUOp.h"

Op ALUOp::op(field op, field funct) {
    switch (op) {
        case 0:
            switch (funct) {
                case 0b100000u:
                    return ADD;
                case 0b100010u:
                    return SUB;
                case 0b011000u:
                    return MUL;
                case 0b100100u:
                    return AND;
                case 0b100101u:
                    return OR;
                case 0b100111u:
                    return NOR;
                case 0b101010u:
                    return SLT;
                default:
                    throw;
            }
            break;
        case ADDI:
        case LW:
        case SW:
            return ADD;
        case BEQ:
            return SUB;
        case LUI:
            return LS;
        case SLTI:
        case SLTIU:
            return SLT;
        case ANDI:
            return AND;
        case ORI:
            return OR;
        default:
            throw;
    }
}
