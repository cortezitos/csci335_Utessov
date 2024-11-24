#include "Vmemory.h"
#include "verilated.h"
#include <iostream>

// void toggle_clock(Vmemory *tb) {
//     tb->clk = !tb->clk;
//     tb->eval();
// }



int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vmemory *tb = new Vmemory;

    std::cout << "out = " << std::hex << static_cast<int>(tb->out) << "\n";

    tb->final();
    delete tb;

    return 0;
}
