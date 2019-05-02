//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_CONTROLLER_H
#define PROJECT_3_CONTROLLER_H


#include "StageLatches.h"
#include "PC.h"
#include "Memory.h"
#include "ALUCtl.h"

typedef uint64_t cycles;
typedef uint32_t inst_len;

class Controller {
public:
    void next_step();

    bool ended();

    bool has_data_hazard(reg_num reg);

    explicit Controller(const Memory &instMemory, inst_len len);

private:
    StageLatches stage_latches;
    PC pc;
    RegisterFile registerFile;
    Memory data_memory;
    Memory inst_memory;
    ALU alu;
    ALUCtl alu_ctl;
    cycles clock;
    inst_len inst_length;
    bool ctl_stall; // stall due to control hazard

    void proc_WB();

    void proc_MEM();

    void proc_EX();

    // return false if stall
    bool proc_ID();

    void proc_IF();

    cycles clock_cycles();
};


#endif //PROJECT_3_CONTROLLER_H
