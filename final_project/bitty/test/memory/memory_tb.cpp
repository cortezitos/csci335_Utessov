#include "Vmemory.h"
#include "verilated.h"
#include <iostream>

void toggle_clock(Vmemory *tb) {
    tb->clk = !tb->clk;
    tb->eval();
}



int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vmemory *tb = new Vmemory;

    tb->clk = 0;
    tb->reset = 1;
    toggle_clock(tb);
    toggle_clock(tb);

    tb->reset = 0;
    tb->done = 1;

    toggle_clock(tb);
    toggle_clock(tb);

    std::cout << "out = " << std::hex <<static_cast<int>(tb->out) << "\n";


    toggle_clock(tb);
    toggle_clock(tb);

    std::cout << "out = " << std::hex <<static_cast<int>(tb->out) << "\n";


    toggle_clock(tb);
    toggle_clock(tb);

    std::cout << "out = " << std::hex << static_cast<int>(tb->out) << "\n";

    tb->final();
    delete tb;

    return 0;
}
