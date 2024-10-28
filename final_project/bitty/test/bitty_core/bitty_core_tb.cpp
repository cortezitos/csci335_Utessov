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
    tb->instruction = 0b0000010001001000;
    tb->reset = 0;
    tb->run = 1;

    toggle_clock(tb);
    toggle_clock(tb);


    std::cout << "reg_0_out = " << static_cast<int>(tb->reg_0_out) << "\n";
    std::cout << "reg_1_out = " << static_cast<int>(tb->reg_1_out) << "\n";
    std::cout << "reg_s_out = " << static_cast<int>(tb->reg_s_out) << "\n";


    toggle_clock(tb);
    toggle_clock(tb);
    toggle_clock(tb);
    toggle_clock(tb);
    toggle_clock(tb);
    toggle_clock(tb);


    std::cout << "Test 3: Instruction i = 2\n";
    std::cout << "reg_c_out = " << static_cast<int>(tb->reg_c_out) << "\n";
    std::cout << "reg_0_out = " << static_cast<int>(tb->reg_0_out);
    std::cout << "reg_1_out = " << static_cast<int>(tb->reg_1_out) << "\n";

    tb->final();
    delete tb;

    return 0;
}
