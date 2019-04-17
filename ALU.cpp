//
// Created by 施昊 on 2019-04-17.
//

#include "ALU.h"

data ALU::compute(data a, data b, Op op) {
    switch (op) {
        case AND:
            return a & b;
        case OR:
            return a | b;
        case ADD:
            return a + b;
        case SUB:
            return a - b;
        case MUL:
            return a * b;
        case SLT:
            return a < b;
        case NOR:
            return !(a | b);
    }
}
