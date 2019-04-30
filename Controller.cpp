//
// Created by 施昊 on 2019-04-17.
//

#include "Controller.h"
#include "SignExt.h"

reg_dat alu_res_to_dat(alu_res alu_res) {
    return alu_res & 0xFFFFFFFF;
}

void Controller::next_step() {
    // increase the clock cycle
    this->clock++;
    // process the pipeline, from the last to the first
    this->proc_WB();
    this->proc_MEM();
    this->proc_EX();
    if (this->proc_ID()) return;
    this->proc_IF();
}

bool Controller::has_data_hazard(reg_num reg) {
    auto latches = this->stage_latches;
    return latches.check_reg_data_hazard(reg, latches.memWb.getIr()) ||
           latches.check_reg_data_hazard(reg, latches.exMem.getIr()) ||
           latches.check_reg_data_hazard(reg, latches.idEx.getIr());
}

void Controller::proc_WB() {
    auto latch = this->stage_latches.memWb;
    auto ins = latch.getIr();
    if (ins.is_nop()) return;
    auto target = ins.dest_reg();
    auto dat_write = 0;
    switch (ins.op()) {
        case BEQ:
            // do nothing
            return;
        case LW:
            dat_write = latch.getLmd();
            break;
        default:
            alu_res alu_res = latch.getAluOut();
            // extract the least significant 32 bits of the 64 bit ALU result
            reg_dat reg_1_res = alu_res_to_dat(alu_res);
            // assign to the register
            dat_write = reg_1_res;
            if (ins.op() == 0 && ins.funt() == MUL) {
                // handle the nasty MUL result from int64 to 2 int32 regs
                // extract the most significant 32 bits of the 64 bit ALU result
                reg_dat reg_2_res = (alu_res & 0xFFFFFFFF00000000) >> 32;
                this->registerFile.write_reg(target + 1, reg_2_res);
            }
            break;
    }
    this->registerFile.write_reg(target, dat_write);
    latch.set_nop();
}

void Controller::proc_MEM() {
    auto latch = this->stage_latches.exMem;
    auto ins = latch.getIr();
    if (ins.is_nop()) return;
    auto alu_res = latch.getAluOut();
    auto alu_res_dat = alu_res_to_dat(alu_res);
    auto mem_res = 0;
    switch (ins.op()) {
        case LW:
            // Load Word, should load data into the latch
            mem_res = this->data_memory.read(alu_res_dat);
            break;
        case SW:
            // Save Word, should write data into memory
            this->data_memory.write(alu_res_dat, latch.getB());
            break;
        case BEQ:
            // Branch EQual, should set program counter to cond in latch
            this->pc.set(latch.getCond());
            // unset the control stall flag, so the IF stage will be enabled in next cycle
            this->ctl_stall = false;
            break;
    }
    this->stage_latches.memWb = MEM_WB(mem_res, alu_res, ins);
    latch.set_nop();
}

void Controller::proc_EX() {
    auto latch = this->stage_latches.idEx;
    auto ins = latch.getIr();
    if (ins.is_nop()) return;
    auto ins_op = ins.op();
    auto latch_a = latch.getA();
    auto latch_b = latch.getB();
    auto alu_a = latch_a;
    auto alu_b = 0;
    // determinate ALU B by instructions
    if (ins_op == BEQ) {
        // rt is originally reserved for result in immediate instructions
        // in branching will be used for comparison
        alu_b = ins.rt();
    } else if (ins.is_imm()) {
        alu_b = latch.getImm();
    } else {
        alu_b = latch_b;
    }
    auto alu_op = this->alu_ctl.decode(ins);
    auto alu_out = this->alu.compute(alu_a, alu_b, alu_op);
    auto cond = alu_out == 0 ? ins.imme() + latch.getNpc() : latch.getNpc();
    // special case for branch, we don't multiply the imm by 4 because the
    // instruction memory line is exactly 32 bit, 4 bytes
    this->stage_latches.exMem = EX_MEM(cond, alu_out, latch.getB(), ins);
    latch.set_nop();
}

bool Controller::proc_ID() {
    if (this->ctl_stall) return false;
    auto latch = this->stage_latches.ifId;
    auto ins = latch.getIr();
    auto reg_a = ins.rs();
    if (this->has_data_hazard(reg_a)) return false;
    auto dat_a = this->registerFile.read_reg(reg_a);
    auto dat_b = 0;
    auto dat_imm = SignExt().extend(ins.imme());
    if (!ins.is_imm()) {
        auto reg_b = ins.rt();
        if (this->has_data_hazard(reg_b)) return false;
        dat_b = this->registerFile.read_reg(reg_b);
    }
    this->stage_latches.idEx = ID_EX(dat_a, dat_b, dat_imm, latch.getNpc(), ins);
    if (ins.op() == BEQ) {
        this->ctl_stall = true;
    }
    latch.set_nop();
    return true;
}

void Controller::proc_IF() {
    if (this->ctl_stall) return;
    auto npc = this->pc.get();
    auto ins = this->inst_memory.read(npc);
    this->stage_latches.ifId = IF_ID(npc, ins);
    // plus one for the memory is 32 bit 4 byte each line
    npc++;
    this->pc.set(npc);
}

cycles Controller::clock_cycles() {
    return this->clock;
}

bool Controller::ended() {
    auto latches = this->stage_latches;
    return latches.ifId.getIr().is_nop() &&
           latches.idEx.getIr().is_nop() &&
           latches.exMem.getIr().is_nop() &&
           latches.memWb.getIr().is_nop() &&
           this->pc.get() >= this->inst_length;
}
