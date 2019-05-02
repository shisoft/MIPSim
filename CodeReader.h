//
// Created by Shi Hao on 2019-05-02.
//

#ifndef PROJECT_3_CODEREADER_H
#define PROJECT_3_CODEREADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Memory.h"
#include "Assembler.h"

struct CodeMemory {
    Memory memory;
    size_t bound;
};

CodeMemory read_code(std::string &file);


#endif //PROJECT_3_CODEREADER_H
