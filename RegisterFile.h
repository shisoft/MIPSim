//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_REGISTERFILE_H
#define PROJECT_3_REGISTERFILE_H


#include <cstdint>
#include <tuple>

typedef int_fast32_t reg_dat;
typedef int8_t reg_num;

class RegisterFile {
private:
     reg_dat cells[32];
public:
    std::tuple<reg_dat, reg_dat> read_reg(reg_num reg1, reg_num reg2);
    void write_reg(reg_num reg_n, reg_dat data);
};


#endif //PROJECT_3_REGISTERFILE_H