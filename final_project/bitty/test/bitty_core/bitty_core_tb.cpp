#include "Vbitty_core.h"
#include "verilated.h"
#include <iostream>

void toggle_clock(Vbitty_core *tb) {
    tb->clk = !tb->clk;
    tb->eval();
}



int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vbitty_core *tb = new Vbitty_core;

    tb->clk = 0;
    tb->instruction = 0b0010100001100100;
    tb->reset = 0;
    tb->run = 1;

    toggle_clock(tb);
    toggle_clock(tb);
    toggle_clock(tb);

    std::cout << "Test 1: Instruction i = 0\n";

    toggle_clock(tb);
    toggle_clock(tb);
    toggle_clock(tb);


    std::cout << "Test 2: Instruction i = 1\n";
    std::cout << "mux_sel = " << static_cast<int>(tb->reg_c_out) << "\n";

    toggle_clock(tb);
    toggle_clock(tb);  
    toggle_clock(tb);

    std::cout << "Test 3: Instruction i = 2\n";
    std::cout << "en_2 = " << static_cast<int>(tb->reg_0_out);

    tb->final();
    delete tb;

    return 0;
}
