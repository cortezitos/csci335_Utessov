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


    
    // Simulate for a few clock cycles
    for (int i = 0; i < 5; i++) {
        

            tb->carry_in = 1;
            tb->in_a = 15;
            tb->in_b = 15;
            tb->select = 15;
            tb->mode = 1;


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
