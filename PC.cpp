//
// Created by 施昊 on 2019-04-17.
//

#include "PC.h"

count PC::get() {
    return this->counter;
}

void PC::set(count c) {
    this->counter = c;
}

void PC::next() {
    this->counter ++; // for 32 bit int should increase 1 not 4
    // If we use int8 instead, we should increase 4
}
