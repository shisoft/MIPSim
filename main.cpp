#include <iostream>
#include "CodeReader.h"

int main(int argc, char* argv[]) {
    std::cout << "UMass Amherst ECE 697CE Project 3" << std::endl;
    if (argc < 1) {
        std::cout << "Usage:" << argv[0] << " <Code File Name>" << std::endl;
        exit(1);
    }
    std::string code_path(argv[1]);
    std::cout << "Reading MIPS code file " << code_path << std::endl;
    auto code_mem = read_code(code_path);
    return 0;
}