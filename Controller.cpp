//
// Created by 施昊 on 2019-04-17.
//

#include <iostream>
#include "Controller.h"
#include "SignExt.h"

reg_dat alu_res_to_dat(alu_res alu_res) {
    return alu_res & 0xFFFFFFFF;
}

Instruction Controller::next_step() {
    // increase the clock cycle
    this->clock++;
    // process the pipeline, from the last to the first
    auto inst_completed = this->proc_WB();
    this->proc_MEM();
    this->proc_EX();
    if (!this->proc_ID()) return inst_completed;
    this->proc_IF();
    return inst_completed;
}

bool Controller::has_data_hazard(reg_num reg) {
    auto latches = this->stage_latches;
    return latches.check_reg_data_hazard(reg, latches.memWb.getIr()) ||
           latches.check_reg_data_hazard(reg, latches.exMem.getIr()) ||
           latches.check_reg_data_hazard(reg, latches.idEx.getIr());
}

Instruction Controller::proc_WB() {
    auto latch = this->stage_latches.memWb;
    auto ins = latch.getIr();
    if (ins.is_nop()) return {NOP_INST};
    auto target = ins.dest_reg();
    auto dat_write = 0;
    switch (ins.op()) {
        case BEQ:
            // do nothing
            return ins;
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
    return ins;
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
            // Branch EQual, when ALU result == 0 which indicates equal, should set program counter to cond in latch
            if (alu_res == 0) this->pc.set(latch.getCond());
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
    if (ins_op == LUI) {
        alu_a = latch.getImm();
        alu_b = 16;
    } else if (ins.is_imm()) {
        alu_b = latch.getImm();
    } else {
        alu_b = latch_b;
    }
    auto alu_op = this->alu_ctl.decode(ins);
    auto alu_out = this->alu.compute(alu_a, alu_b, alu_op);
    auto cond = latch.getNpc() + latch.getImm();
    // special case for branch, we don't multiply the imm by 4 because the
    // instruction memory line is exactly 32 bit, 4 bytes
    this->stage_latches.exMem = EX_MEM(cond, alu_out, latch.getB(), ins);
    latch.set_nop();
}

bool Controller::proc_ID() {
    if (this->ctl_stall) return false;
    auto latch = this->stage_latches.ifId;
    auto ins = latch.getIr();
    // return true when nop, this will force PC to increase in IF stage and reach inst_len sooner or later
    if (ins.is_nop()) return true;
    auto reg_a = ins.rs();
    auto reg_b = 0;
    auto dat_b = 0;
    auto dat_imm = SignExt().extend(ins.imme());
    if (!ins.is_imm()) {
        if (ins.funt() == SLL || ins.funt() == SRL) {
            reg_a = ins.rt();
            dat_b = ins.shamt();
        } else {
            reg_b = ins.rt();
        }
    } else if (ins.op() == BEQ) {
        // rt is originally reserved for result in immediate instructions
        // in branching will be used for comparison
        reg_b = ins.rt();
    }
    if (reg_b != 0) {
        if (this->has_data_hazard(reg_b)) return false;
        dat_b = this->registerFile.read_reg(reg_b);
    }
    if (reg_a != 0 && this->has_data_hazard(reg_a)) return false;
    auto dat_a = this->registerFile.read_reg(reg_a);
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
    this->pc.next();
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

Controller::Controller(const Memory &instMemory, inst_len len) {
    this->pc = PC{};
    this->registerFile = RegisterFile{};
    this->data_memory = Memory{};
    this->inst_memory = instMemory;
    this->clock = 0;
    this->inst_length = len;
    this->ctl_stall = false;
    this->stage_latches = StageLatches{};
}

void Controller::run_inst_mode() {
    while (!this->ended()) {
        while (true) {
            auto wb_ins = this->next_step();
            if (!wb_ins.is_nop()) {
                std::cout << "Run: " << wb_ins.as_asm() << std::endl;
                this->Inspect();
                break;
            }
        }
    }
    std::cout << "All available instructions have been run" << std::endl;
}

void Controller::run_cycle_mode() {

}

bool Controller::Inspect() {
    std::cout << "======================================" << std::endl;
    std::cout << "Program Counter: " << this->pc.get() << std::endl;
    std::cout << "Control Stall: " << this->ctl_stall << std::endl;
    std::cout << "Clock Cycle:" << this->clock << std::endl;
    std::cout << "------------------IF-ID---------------" << std::endl;
    auto if_id = this->stage_latches.ifId;
    std::cout << "Ins:" << if_id.getIr().as_asm() << std::endl;
    std::cout << "NPC:" << if_id.getNpc() << std::endl;
    std::cout << "------------------ID-EX---------------" << std::endl;
    auto id_ex = this->stage_latches.idEx;
    std::cout << "Ins:" << id_ex.getIr().as_asm() << std::endl;
    std::cout << "NPC:" << id_ex.getNpc() << std::endl;
    std::cout << "A: 0x" << std::hex << id_ex.getA() << std::endl;
    std::cout << "B: 0x" << std::hex << id_ex.getB() << std::endl;
    std::cout << "I: 0x" << std::hex << id_ex.getImm() << std::endl;
    std::cout << "-----------------EX-MEM---------------" << std::endl;
    auto ex_mem = this->stage_latches.exMem;
    std::cout << "Ins:" << ex_mem.getIr().as_asm() << std::endl;
    std::cout << "ALU: 0x" << std::hex << ex_mem.getAluOut() << std::endl;
    std::cout << "COND 0x:" << std::hex << ex_mem.getCond() << std::endl;
    std::cout << "B: 0x" << std::hex << ex_mem.getB() << std::endl;
    std::cout << "----------------MEM-WB---------------" << std::endl;
    auto mem_wb = this->stage_latches.memWb;
    std::cout << "Ins:" << mem_wb.getIr().as_asm() << std::endl;
    std::cout << "ALU: 0x" << std::hex << mem_wb.getAluOut() << std::endl;
    std::cout << "LMD: 0x" << std::hex << mem_wb.getLmd() << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "PRESS ANY TO CONTINUE OR 'R' FOR REGISTERS..." << std::endl;
    if (std::tolower(std::cin.get()) == 'r') {
        for (field i = 0; i < 32; i++) {
            std::cout << reg_name(i) << ": 0x" << std::hex << this->registerFile.read_reg(i) << std::endl;
        }
        return true;
    }
    return false;
}

