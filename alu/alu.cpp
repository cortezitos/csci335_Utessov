#include "Valu.h"
#include "verilated.h"
#include "verilated_vcd_c.h" // Include the VCD trace header
#include <iostream>

int main(int argc, char **argv) {
    // Initialize Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the Verilog module
    Valu *tb = new Valu;


    // Initialize the clock and reset
    tb->clk = 0;
    tb->rst = 1;  // Assert reset
    
    // Simulate for a few clock cycles
        // Toggle the clock
        
        // Set inputs on every positive clock edge
            tb->rst = 0;   // Deassert reset after the first cycle
            tb->carry_in = 0;
            tb->in_a = 15;
            tb->in_b = 23;
            tb->select = 0;
            tb->mode = 0;

        // Evaluate the model (tick the clock)
        tb->eval();

        std::cout << ": ALU Output = " << tb->alu_out << std::endl;

    // Final cleanup
    tb->final();

    return 0;
}
