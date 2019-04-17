//
// Created by 施昊 on 2019-04-17.
//

#include "RegisterFile.h"

std::tuple<reg_dat, reg_dat> RegisterFile::read_reg(reg_num reg1, reg_num reg2) {
    return std::make_tuple(this->cells[reg1], this->cells[reg2]);
}

void RegisterFile::write_reg(reg_num reg_n, reg_dat data) {
    this->cells[reg_n] = data;
}
