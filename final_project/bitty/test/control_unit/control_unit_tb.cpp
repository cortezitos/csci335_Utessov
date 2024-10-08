#include "Vcontrol_unit.h"
#include "verilated.h"
#include <iostream>

void toggle_clock(Vcontrol_unit *tb) {
    tb->clk = !tb->clk;
    tb->eval();
}

void control_unit_test(Vcontrol_unit *tb, uint16_t instruction, bool run, bool reset) {
    toggle_clock(tb);
    tb->instruction = instruction;
    tb->run = run;
    tb->reset = reset;
    toggle_clock(tb);
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vcontrol_unit *tb = new Vcontrol_unit;

    tb->clk = 0;
    toggle_clock(tb);

    std::cout << "Test 1: Reset\n";
    control_unit_test(tb, 0, false, true);
    std::cout << "en_s = " << tb->en_s << " en_c = " << tb->en_c << " (Expected: 0 0)\n";

    std::cout << "Test 2: Run with instruction\n";
    control_unit_test(tb, 0xC123, true, false);
    std::cout << "mux_sel = " << tb->mux_sel << " en_s = " << tb->en_s << " (Expected: 6 1)\n";

    std::cout << "Test 3: Continue run\n";
    control_unit_test(tb, 0xC123, true, false);
    std::cout << "mux_sel = " << tb->mux_sel << " en_c = " << tb->en_c << " sel = " << tb->sel << " mode = " << tb->mode << " (Expected: 1 1 2 1)\n";

    tb->final();
    delete tb;

    return 0;
}
