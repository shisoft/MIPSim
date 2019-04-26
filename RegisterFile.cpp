//
// Created by 施昊 on 2019-04-17.
//

#include "RegisterFile.h"

void RegisterFile::write_reg(reg_num reg_n, reg_dat data) {
    this->cells[reg_n] = data;
}

reg_dat RegisterFile::read_reg(reg_num reg1) {
    return this->cells[reg1];
}
