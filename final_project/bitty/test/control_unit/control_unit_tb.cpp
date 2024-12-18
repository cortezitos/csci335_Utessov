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
    tb->instruction = 0x4721;
    tb->reset = 0;
    tb->run = 1;

    toggle_clock(tb);
    toggle_clock(tb);
    toggle_clock(tb);

    std::cout << "Test 1: Instruction i = 0\n";
    std::cout << "mux_sel = " << static_cast<int>(tb->mux_sel) << " en_s = " << static_cast<int>(tb->en_s) << " (Expected: 2 1)\n";

    toggle_clock(tb);
    toggle_clock(tb);
    toggle_clock(tb);


    std::cout << "Test 2: Instruction i = 1\n";
    std::cout << "mux_sel = " << static_cast<int>(tb->mux_sel) << " en_c = " << static_cast<int>(tb->en_s) << " alu_sel = " << static_cast<int>(tb->sel) << " (Expected: 1 1 4 0)\n";

    toggle_clock(tb);
    toggle_clock(tb);  
    toggle_clock(tb);

    std::cout << "Test 3: Instruction i = 2\n";
    std::cout << "en_2 = " << static_cast<int>(tb->en_2) << " done = " << static_cast<int>(tb->done) << " (Expected: 1 1)\n";

    tb->final();
    delete tb;

    return 0;
}
