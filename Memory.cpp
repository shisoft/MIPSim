//
// Created by 施昊 on 2019-04-17.
//

#include "Memory.h"

line Memory::read(addr address) {
    return this->mem[address];
}

void Memory::write(addr address, line data) {
    this->mem[address] = data;
}