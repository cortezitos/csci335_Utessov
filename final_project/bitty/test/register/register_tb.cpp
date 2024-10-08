#include "Vregister.h"
#include "verilated.h"
#include <iostream>

void toggle_clock(Vregister *tb) {
    tb->clk = !tb->clk;
    tb->eval();
}

void register_load(Vregister *tb, int data_in, bool enable, bool reset) {
        toggle_clock(tb);

    tb->d_in = data_in;
    tb->en = enable;
    tb->reset = reset;
    toggle_clock(tb);

}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vregister *tb = new Vregister;

    tb->clk = 0;
    toggle_clock(tb);

    std::cout << "Test 1: Reset the register\n";
    register_load(tb, 0, false, true);
    std::cout << "d_out = " << tb->d_out << " (Expected = 0)\n";

    std::cout << "Test 2: Load value into register when enabled\n";
    register_load(tb, 10, true, false);
    std::cout << "d_out = " << tb->d_out << " (Expected = 10)\n";

    std::cout << "Test 3: No change when enable is off\n";
    register_load(tb, 35, false, false);
    std::cout << "d_out = " << tb->d_out << " (Expected = 10)\n";

    std::cout << "Test 4: Reset the register again\n";
    register_load(tb, 0, false, true);
    std::cout << "d_out = " << tb->d_out << " (Expected = 0)\n";

    tb->final();
    delete tb;

    return 0;
}
