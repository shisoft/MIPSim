//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_MEMORY_H
#define PROJECT_3_MEMORY_H

#include <cstdint>
#include <cstdio>
#include "wires.h"

const size_t MEM_BYTES = 512;

class Memory {
private:
    line mem[MEM_BYTES] = {0}; // 2 kbytes
public:
    line read(addr address);

    void write(addr address, line data);
};


#endif //PROJECT_3_MEMORY_H
