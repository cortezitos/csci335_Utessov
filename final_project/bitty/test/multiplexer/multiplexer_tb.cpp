#include "Vmultiplexer.h"
#include "verilated.h"
#include <iostream>

void multiplexer_select(Vmultiplexer *tb, int reg_0, int reg_1, int reg_2, int reg_3, int reg_4, int reg_5, int reg_6, int reg_7, uint8_t mux_sel) {
    tb->reg_0 = reg_0;
    tb->reg_1 = reg_1;
    tb->reg_2 = reg_2;
    tb->reg_3 = reg_3;
    tb->reg_4 = reg_4;
    tb->reg_5 = reg_5;
    tb->reg_6 = reg_6;
    tb->reg_7 = reg_7;
    tb->mux_sel = mux_sel;
    tb->eval();
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vmultiplexer *tb = new Vmultiplexer;

    std::cout << "Test 1: Select d_in (mux_sel = 0)\n";
    multiplexer_select(tb, 0, 1, 2, 3, 4, 5, 6, 7, 0);
    std::cout << "d_out = " << tb->d_out << " (Expected = 25)\n";

    std::cout << "Test 2: Select reg_3 (mux_sel = 3)\n";
    multiplexer_select(tb, 0, 1, 2, 3, 4, 5, 6, 7, 3);
    std::cout << "d_out = " << tb->d_out << " (Expected = 2)\n";

    tb->final();
    delete tb;

    return 0;
}
