#include "Vregister.h"         // Verilated model header
#include "verilated.h"         // Verilator header for simulation
#include <iostream>

// Function to compute expected output based on inputs, mimicking Verilog behavior
uint16_t computeExpectedOutput(uint16_t d_in, bool reset, bool en, uint16_t prev_output) {
    if (reset) {
        return 0;
    } else if (en) {
        return d_in;
    } else {
        return prev_output;
    }
}

int main(int argc, char** argv) {
    // Initialize Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the Verilated model
    Vregister* top = new Vregister;

    // Simulation inputs
    uint16_t d_in = 10;
    bool reset = true;
    bool en = false;

    // Clock signal
    bool clk = 0;

    // Previous output to track state
    uint16_t expected_output = 0;
    
    // Simulate for 20 clock cycles
    for (int i = 0; i < 20; ++i) {
        // Toggle the clock
        clk = !clk;
        top->clk = clk;

        // Apply reset for the first 2 cycles
        if (i == 0 || i == 1) {
            reset = true;
        } else {
            reset = false;
        }

        // Enable signal active after 5 cycles
        if (i == 5) {
            en = true;
        }

        // Apply inputs to the top module
        top->reset = reset;
        top->en = en;
        top->d_in = d_in;

        // Evaluate the model
        top->eval();

        // Only check output on positive clock edge
        if (clk) {
            // Compute expected output for the current cycle
            uint16_t computed_output = computeExpectedOutput(d_in, reset, en, expected_output);

            // Compare the Verilated model output with computed output
            if (top->d_out != computed_output) {
                std::cerr << "Mismatch at cycle " << i << ": expected " 
                          << computed_output << ", but got " << top->d_out << std::endl;
                return -1; // Exit with error if there's a mismatch
            }

            // Update the expected output state
            expected_output = computed_output;

            // Print the current result
            std::cout << "Cycle " << i << ": d_out = " << top->d_out << std::endl;
        }

        // Increment input for testing
        d_in += 1;
    }

    // Clean up
    top->final();
    delete top;

    std::cout << "Test completed successfully. No mismatches found." << std::endl;
    
    return 0;
}
