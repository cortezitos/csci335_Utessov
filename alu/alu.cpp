#include "Valu.h"
#include "verilated.h"
#include <iostream>

int main(int argc, char **argv) {
    // Initialize Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the Verilog module
    Valu *tb = new Valu;

    // Test cases array: {in_a, in_b, select, mode}
    int test_cases[80][4] = {
        // 0000 - A' (Logic), A (Arithmetic)
        {15, 23, 0, 1}, {8, 5, 0, 1}, {1, 0, 0, 1}, {0, 1, 0, 1}, {7, 3, 0, 1},  // Logic mode (A')
        {15, 23, 0, 0}, {8, 5, 0, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {7, 3, 0, 0},  // Arithmetic mode (A)

        // 0001 - (A + B)' (Logic), A + B (Arithmetic)
        {15, 23, 1, 1}, {8, 5, 1, 1}, {1, 0, 1, 1}, {0, 1, 1, 1}, {7, 3, 1, 1},  // Logic mode
        {15, 23, 1, 0}, {8, 5, 1, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {7, 3, 1, 0},  // Arithmetic mode

        // 0010 - A'B (Logic), A + B' (Arithmetic)
        {15, 23, 2, 1}, {8, 5, 2, 1}, {1, 0, 2, 1}, {0, 1, 2, 1}, {7, 3, 2, 1},  // Logic mode
        {15, 23, 2, 0}, {8, 5, 2, 0}, {1, 0, 2, 0}, {0, 1, 2, 0}, {7, 3, 2, 0},  // Arithmetic mode

        // 0011 - Logical 0 (Logic), Minus 1 (Arithmetic)
        {15, 23, 3, 1}, {8, 5, 3, 1}, {1, 0, 3, 1}, {0, 1, 3, 1}, {7, 3, 3, 1},  // Logic mode
        {15, 23, 3, 0}, {8, 5, 3, 0}, {1, 0, 3, 0}, {0, 1, 3, 0}, {7, 3, 3, 0},  // Arithmetic mode

        // 0100 - (AB)' (Logic), A + AB' (Arithmetic)
        {15, 23, 4, 1}, {8, 5, 4, 1}, {1, 0, 4, 1}, {0, 1, 4, 1}, {7, 3, 4, 1},  // Logic mode
        {15, 23, 4, 0}, {8, 5, 4, 0}, {1, 0, 4, 0}, {0, 1, 4, 0}, {7, 3, 4, 0},  // Arithmetic mode

        // ... Continue with the remaining operations ...
    };

    for (int i = 0; i < 80; i++) {
        for(int j = 0; j < 2; j++){
            tb->carry_in = j;
            tb->in_a = test_cases[i][0];
            tb->in_b = test_cases[i][1];
            tb->select = test_cases[i][2];
            tb->mode = test_cases[i][3];

            // Evaluate the model (tick the clock)
            tb->eval();
    
            std::cout << "Test " << i + 1 << "A: " << test_cases[i][0] << "B: " << test_cases[i][1] << "Select: " << test_cases[i][2] << "Mode: " << test_cases[i][3]
                    << ": ALU Output = " << tb->alu_out << std::endl
                    << ", COut = " << static_cast<int>(tb->carry_out) << std::endl
                    << ", Compare = " << static_cast<int>(tb->compare) << std::endl;
        }
    }

    // Final cleanup
    tb->final();

    return 0;
}