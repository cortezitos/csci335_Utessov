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

     // Simulation setup
    vluint64_t sim_time = 0;  // Simulation time
    const vluint64_t max_sim_time = 1000;  // Maximum simulation time
    tb->clk = 0;

    // Simulate the reset signal
    tb->reset = 1;  // Assert reset for initialization
    tb->eval();     // Evaluate model
    vcd_trace->dump(0);  // Dump state to the VCD at time 0
    tb->reset = 0;  // Deassert reset

     while (sim_time < max_sim_time) {
        // Toggle the clock
        tb->clk = !tb->clk;

        // Deassert reset after a few clock cycles
        if (sim_time == 10) {
            tb->rst = 0;  // Deassert reset
        }

        // Apply the enable signal
        tb->enable = enable;

        // Evaluate the model (tick the clock)
        tb->eval();

        // Simulate the key sequence 335256
        int code[6] = {3, 3, 5, 2, 5, 6};
        for (int i = 0; i < 6; i++) {
            tb->key = code[i];  // Send each digit
            tb->eval();         // Evaluate after each input
            vcd_trace->dump(i * 10);  // Dump the simulation state after every step (adjust timing as needed)
            std::cout << "Key entered: " << code[i] << ", Locked state: " << tb->locked << std::endl;
        }

        if (tb->locked == 0) {
            std::cout << "Unlocked successfully!" << std::endl;
        } else {
            std::cout << "Failed to unlock." << std::endl;
        }

        // Increment simulation time
        sim_time++;
    }



    // Final cleanup
    vcd_trace->close();  // Close the VCD file
    tb->final();  // Finish simulation
    delete tb;
    delete vcd_trace;  // Clean up the trace object

    return 0;
}
