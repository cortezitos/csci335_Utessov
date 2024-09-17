#include "Valu.h"
#include "verilated.h"
#include <iostream>

int main(int argc, char **argv) {
    // Initialize Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the Verilog module
    Valu *tb = new Valu;

    // Simulation setup
    vluint64_t sim_time = 0;  // Simulation time
    const vluint64_t max_sim_time = 1000;  // Maximum simulation time

    // Initialize the clock and reset
    tb->clk = 0;
    tb->rst = 1;  // Assert reset

    // Start the simulation loop
        // Toggle the clock
        tb->clk = !tb->clk;

        // Deassert reset after a few clock cycles
        if (sim_time == 10) {
            tb->rst = 0;  // Deassert reset
        }

        // Evaluate the model (tick the clock)
        tb->eval();

        tb->carry_in = 0;
        tb->in_a = 15;
        tb->in_b = 23;
        tb->select= 9;
        tb->mode = 0;

        std::cout << ": Fibonacci number = " << tb->alu_out << std::endl;

        // Increment simulation time
        sim_time++;

    // Final cleanup
    tb->final();
    delete tb;

    return 0;
}