#include "Valu.h"
#include "verilated.h"
#include "verilated_vcd_c.h" // Include the VCD trace header
#include <iostream>

int main(int argc, char **argv) {
    // Initialize Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the Verilog module
    Valu *tb = new Valu;

    // Initialize trace
    VerilatedVcdC* tfp = new VerilatedVcdC;   // Create trace object
    Verilated::traceEverOn(true);             // Enable tracing
    tb->trace(tfp, 99);                       // Trace 99 levels of hierarchy
    tfp->open("dump.vcd");                    // Open the VCD file

    // Initialize the clock and reset
    tb->clk = 0;
    tb->rst = 1;  // Assert reset
    
    // Simulate for a few clock cycles
    for (int i = 0; i < 2; i++) {
        // Toggle the clock
        tb->clk = !tb->clk;
        
        // Set inputs on every positive clock edge
        if (tb->clk) {
            tb->rst = 0;   // Deassert reset after the first cycle
            tb->carry_in = 0;
            tb->in_a = 15;
            tb->in_b = 23;
            tb->select = 0;
            tb->mode = 0;
        }

        // Evaluate the model (tick the clock)
        tb->eval();

        // Dump trace at each step
        tfp->dump(i);

        
        std::cout << ": ALU Output = " << tb->alu_out << std::endl;
        std::cout << ": COut = " << tb->carry_out << std::endl;
        std::cout << ": Compare = " << tb->compare << std::endl;

    }

    // Final cleanup
    tfp->close();    // Close the VCD file
    tb->final();
    delete tb;
    delete tfp;

    return 0;
}
