//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_ALUCTL_H
#define PROJECT_3_ALUCTL_H

#include "ALU.h"

class ALUCtl {
public:
    Op decode(field op, field funct);
};


#endif //PROJECT_3_ALUCTL_H
