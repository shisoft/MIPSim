//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_REGISTERFILE_H
#define PROJECT_3_REGISTERFILE_H


#include <cstdint>
#include <tuple>
#include "wires.h"

class RegisterFile {
private:
     reg_dat cells[32];
public:
    reg_dat read_reg(reg_num reg1);
    void write_reg(reg_num reg_n, reg_dat data);
};


#endif //PROJECT_3_REGISTERFILE_H
