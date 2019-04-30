//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_CONTROLLER_H
#define PROJECT_3_CONTROLLER_H


#include "StageLatchess.h"
#include "PC.h"
#include "Memory.h"
#include "ALUCtl.h"

class Controller {
public:
    void next_step();
private:
    StageLatchess stage_latches;
    PC pc;
    RegisterFile registerFile;
    Memory data_memory;
    ALU alu;
    ALUCtl alu_ctl;
    bool ctlStall; // stall due to control hazard

    void proc_WB();
    void proc_MEM();
    void proc_EX();
    // return false if stall
    bool proc_ID();
    void proc_IF();
};


#endif //PROJECT_3_CONTROLLER_H
