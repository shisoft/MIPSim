//
// Created by 施昊 on 2019-04-17.
//

#include "ALU.h"

alu_res ALU::compute(reg_dat a, reg_dat b, Op op) {
    switch (op) {
        case ALU_AND:
            return a & b;
        case ALU_OR:
            return a | b;
        case ALU_ADD:
            return a + b;
        case ALU_SUB:
            return a - b;
        case ALU_MUL:
            return (uint64_t) a * (uint64_t) b;
        case ALU_SLT:
            return a < b;
        case ALU_NOR:
            return !(a | b);
        case ALU_LS:
            return a << b;
        case ALU_RS:
            return a >> b;
        case ALU_NOP:
            return 0;
    }
}
