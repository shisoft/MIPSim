cmake_minimum_required(VERSION 3.13)
project(Project_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project_3 main.cpp ALU.cpp ALU.h RegisterFile.cpp RegisterFile.h Memory.cpp Memory.h PC.cpp PC.h Control.cpp Control.h CPU.cpp CPU.h SignExt.cpp SignExt.h ALUCtl.cpp ALUCtl.h Instruction.cpp Instruction.h Stages.cpp Stages.h ALUOp.cpp ALUOp.h)