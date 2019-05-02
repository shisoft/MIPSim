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
    std::cout << "Code read and assemble completed, total " << code_mem.bound << " instructions" << std::endl;
    while (true) {
        std::cout << "Select mode: 1 - Instruction, 2 - Cycle: ";
        int mode;
        std::cin >> mode;

        switch (mode) {
            case 1:
                std::cout << "Running in Instruction mode" << std::endl;

                break;
            case 2:
                std::cout << "Running in Cycle mode" << std::endl;
                break;
            default:
                std::cout << "Cannot understand mode " << mode << "..." << std::endl;
                exit(2);
        }

        std::cout << "Do you wish to run another round of this simulation? yN: ";
        char rerun;
        std::cin >> rerun;
        if (std::tolower(rerun) != 'y') {
            std::cout << "Good bye!" << std::endl;
            break;
        }
    }
    return 0;
}