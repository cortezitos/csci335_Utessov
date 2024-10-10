#include "Vcontrol_unit.h"
#include "verilated.h"
#include <iostream>

void toggle_clock(Vcontrol_unit *tb) {
    tb->clk = !tb->clk;
    tb->eval();
}



int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vcontrol_unit *tb = new Vcontrol_unit;

    tb->clk = 0;
    toggle_clock(tb);
    toggle_clock(tb);

    tb->instruction = 0x4721;
    tb->reset = 0;

    toggle_clock(tb);

    std::cout << "Test 1: Instruction i = 0\n";
    std::cout << "mux_sel = " << static_cast<int>(tb->mux_sel) << " en_s = " << static_cast<int>(tb->en_s) << " (Expected: 2 1)\n";

    toggle_clock(tb);
    toggle_clock(tb);

    std::cout << "Test 2: Instruction i = 1\n";
    std::cout << "mux_sel = " << static_cast<int>(tb->mux_sel) << " en_c = " << static_cast<int>(tb->en_s) << " alu_sel = " << static_cast<int>(tb->sel) << " alu_mode = " << static_cast<int>(tb->mode) << " (Expected: 1 1 4 0)\n";

    toggle_clock(tb);
    toggle_clock(tb);  

    std::cout << "Test 3: Instruction i = 2\n";
    control_unit_test(tb, 0xC123, true, false);
    std::cout << "en_1 = " << static_cast<int>(tb->mux_sel) << " done = " << static_cast<int>(tb->done) << " (Expected: 1 1)\n";

    toggle_clock(tb);  

    tb->final();
    delete tb;

    return 0;
}
