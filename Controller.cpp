//
// Created by 施昊 on 2019-04-17.
//

#include "Controller.h"

reg_dat alu_res_to_dat(alu_res alu_res) {
    return alu_res & 0xFFFFFFFF;
}

void Controller::next_step() {

}

void Controller::proc_EX() {

}

bool Controller::proc_ID() {
    return false;
}

void Controller::proc_IF() {

}

void Controller::proc_WB() {
    auto latch = this->stage_latches.memWb;
    auto ins = latch.getIr();
    auto target = ins.dest_reg();
    switch (ins.op()) {
        case LW:
            this->registerFile.write_reg(target, latch.getLmd());
            break;
        case BEQ:
            // do nothing
            break;
        default:
            alu_res alu_res = latch.getAluOut();
            // extract the least significant 32 bits of the 64 bit ALU result
            reg_dat reg_1_res = alu_res_to_dat(alu_res);
            // assign to the register
            this->registerFile.write_reg(target, reg_1_res);
            if (ins.op() == 0 && ins.funt() == MUL) {
                // handle the nasty MUL result from int64 to 2 int32 regs
                // extract the most significant 32 bits of the 64 bit ALU result
                reg_dat reg_2_res = (alu_res & 0xFFFFFFFF00000000) >> 32;
                this->registerFile.write_reg(target + 1, reg_2_res);
            }
            break;
    }
}

void Controller::proc_MEM() {
    auto latch = this->stage_latches.exMem;
    auto ins = latch.getIr();
    auto alu_res = latch.getAluOut();
    auto alu_res_dat = alu_res_to_dat(alu_res);
    auto mem_res = 0;
    switch (ins.op()) {
        case LW:
            mem_res = this->data_memory.read(alu_res_dat);
            break;
        case SW:
            this->data_memory.write(alu_res_dat, latch.getB());
            break;
        case BEQ:
            this->pc.set(latch.getCond());
            break;
    }
    this->stage_latches.memWb = MEM_WB(mem_res, alu_res, ins);
}
