//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_MEMORY_H
#define PROJECT_3_MEMORY_H

#include <cstdint>

typedef int32_t addr;
typedef int32_t line;

class Memory {
private:
    line mem[524288]; // 2 kbytes
public:
    line read(addr address);
    void write(addr address, line data);
};


#endif //PROJECT_3_MEMORY_H
