//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_PC_H
#define PROJECT_3_PC_H


#include <cstdint>
#include "wires.h"

class PC {
private:
    p_count counter;
public:
    p_count get();

    void set(p_count c);

    void next();
};


#endif //PROJECT_3_PC_H
