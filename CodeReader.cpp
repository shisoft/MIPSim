//
// Created by Shi Hao on 2019-05-02.
//

#include "CodeReader.h"

CodeMemory read_code(std::string &file) {
    size_t index = 0;
    Memory memory = Memory();
    std::ifstream infile(file);
    std::string line;
    while (getline(infile, line)) {
        if (line.length() < 4) continue;
        std::cout << "IN  < " << line << std::endl;
        auto ins_raw = to_instruction(line);
        auto ins = Instruction(ins_raw);
        std::cout << "HEX > " << ins.as_hex() << std::endl;
        std::cout << "BIN > " << ins.as_bin() << std::endl;
        std::cout << "ASM > " << ins.as_asm() << std::endl << std::endl;
        memory.write(index, ins_raw);
        index++;
    }
    if (index == 0) {
        std::cout << "<NOTHING TO READ>" << std::endl;
    }
    return CodeMemory{memory, index};
}
