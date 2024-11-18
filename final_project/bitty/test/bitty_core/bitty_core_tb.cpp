#include "Vbitty_core.h"
#include "verilated.h"
#include <iostream>
#include <bitset>
//#include "Bittyinstruction.h"

// this is for guthub -- everything works well lab 11
void toggle_clock(Vbitty_core *tb) {
    tb->clk = !tb->clk;
    tb->eval();
    tb->clk = !tb->clk;
    tb->eval();
}

extern "C" void notify_reached_done() {
    std::cout << "Counter reached done!" << std::endl;
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vbitty_core *tb = new Vbitty_core;

    tb->clk = 0;
    tb->reset = 0;

    tb->reg_0_out = 40;
    tb->reg_1_out = 30;
    tb->reg_2_out = 20;
    tb->reg_3_out = 10;
    toggle_clock(tb);


    tb->run = 1;

    std::cout << "reg_0_out = " << static_cast<int>(tb->reg_0_out) << "\n";
    std::cout << "reg_1_out = " << static_cast<int>(tb->reg_1_out) << "\n";
    std::cout << "reg_2_out = " << static_cast<int>(tb->reg_2_out) << "\n";
    std::cout << "reg_3_out = " << static_cast<int>(tb->reg_3_out) << "\n";
    std::cout << std::endl;


    do {
        toggle_clock(tb);
        std::cout << "instruction = " << std::bitset<16>(tb->instruction) << "\n";

        toggle_clock(tb);
        toggle_clock(tb);
        toggle_clock(tb);


        std::cout << "reg_0_out = " << std::dec<< static_cast<int>(tb->reg_0_out) << "\n";
        std::cout << "reg_1_out = " << static_cast<int>(tb->reg_1_out) << "\n";
        std::cout << "reg_2_out = " << static_cast<int>(tb->reg_2_out) << "\n";
        std::cout << "reg_3_out = " << static_cast<int>(tb->reg_3_out) << "\n";
        std::cout << std::endl;

    } while (tb->instruction != 0x0000);



    tb->final();
    delete tb;

    return 0;
}
