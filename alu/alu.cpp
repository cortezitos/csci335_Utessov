#include "Valu.h"
#include "verilated.h"
#include <iostream>

int main(int argc, char **argv) {
    // Initialize Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the Verilog module
    Valu *tb = new Valu;

    // Initialize the clock and reset
    tb->clk = 0;
    tb->rst = 1;  // Assert reset

   // Start the simulation loop
        // Toggle the clock
        tb->clk = !tb->clk;

 

        // Evaluate the model (tick the clock)
        tb->eval();

        tb->carry_in = 0;
        tb->in_a = 15;
        tb->in_b = 23;
        tb->select= 0;
        tb->mode = 0;

        std::cout << ": Fibonacci number = " << tb->alu_out << std::endl;


    // Final cleanup
    tb->final();
    delete tb;

    return 0;
}