#include "Vkeylock.h"
#include "verilated.h"
#include "verilated_vcd_c.h"  // Include for VCD tracing
#include <iostream>

int main(int argc, char **argv) {
    // Initialize Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the Verilog module
    Vkeylock *tb = new Vkeylock;

    // Enable waveform tracing
    Verilated::traceEverOn(true);  // Enable tracing
    VerilatedVcdC* vcd_trace = new VerilatedVcdC;  // Create trace object
    tb->trace(vcd_trace, 99);  // Trace 99 levels of hierarchy
    vcd_trace->open("keylock_trace.vcd");  // Open the VCD file

    // Simulate the reset signal
    tb->clk = 0;
    tb->reset = 1;  // Assert reset for initialization
    tb->eval();     // Evaluate model
    vcd_trace->dump(0);  // Dump state to the VCD at time 0
    tb->reset = 0;  // Deassert reset

    tb->clk = !tb->clk;

    // Simulate the key sequence 335256
    int code[6] = {3, 3, 5, 2, 5, 6};
    for (int i = 0; i < 6; i++) {
        tb->clk = !tb->clk;
        tb->key = code[i];  // Send each digit
        tb->eval();         // Evaluate after each input
        vcd_trace->dump(i * 10);  // Dump the simulation state after every step (adjust timing as needed)
        std::cout << "Key entered: " << code[i] << ", Locked state: " << tb->locked << std::endl;
    }
    tb->clk = !tb->clk;
    tb-eval();
    vcd_trace->dump(60);

    if (tb->locked == 0) {
        std::cout << "Unlocked successfully!" << std::endl;
    } else {
        std::cout << "Failed to unlock." << std::endl;
    }

    // Final cleanup
    vcd_trace->close();  // Close the VCD file
    tb->final();  // Finish simulation
    delete tb;
    delete vcd_trace;  // Clean up the trace object

    return 0;
}
