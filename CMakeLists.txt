cmake_minimum_required(VERSION 3.13)
project(Project_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_3 main.cpp ALU.cpp ALU.h RegisterFile.cpp RegisterFile.h Memory.cpp Memory.h PC.cpp PC.h Controller.cpp Controller.h CPU.cpp CPU.h SignExt.cpp SignExt.h ALUCtl.cpp ALUCtl.h Instruction.cpp Instruction.h StageLatches.cpp StageLatches.h wires.h format.h Assembler.cpp Assembler.h CodeReader.cpp CodeReader.h)