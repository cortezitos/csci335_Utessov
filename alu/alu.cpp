#include "Valu.h"
#include "verilated.h"
#include <iostream>

int main(int argc, char **argv) {
    // Initialize Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the Verilog module
    Valu *tb = new Valu;

    // Test cases array: {in_a, in_b, select, mode}
    int test_cases[160][5] = {
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

        // 0101 - B' (Logic), (A + B') plus AB' (Arithmetic)
        {15, 23, 5, 1}, {8, 5, 5, 1}, {1, 0, 5, 1}, {0, 1, 5, 1}, {7, 3, 5, 1},  // Logic mode
        {15, 23, 5, 0}, {8, 5, 5, 0}, {1, 0, 5, 0}, {0, 1, 5, 0}, {7, 3, 5, 0},  // Arithmetic mode

        // 0110 - A XOR B (Logic), A minus B minus 1 (Arithmetic)
        {15, 23, 6, 1}, {8, 5, 6, 1}, {1, 0, 6, 1}, {0, 1, 6, 1}, {7, 3, 6, 1},  // Logic mode
        {15, 23, 6, 0}, {8, 5, 6, 0}, {1, 0, 6, 0}, {0, 1, 6, 0}, {7, 3, 6, 0},  // Arithmetic mode

        // 0111 - AB' (Logic), AB' minus 1 (Arithmetic)
        {15, 23, 7, 1}, {8, 5, 7, 1}, {1, 0, 7, 1}, {0, 1, 7, 1}, {7, 3, 7, 1},  // Logic mode
        {15, 23, 7, 0}, {8, 5, 7, 0}, {1, 0, 7, 0}, {0, 1, 7, 0}, {7, 3, 7, 0},  // Arithmetic mode

        // 1000 - A' + B' (Logic), A plus AB (Arithmetic)
        {15, 23, 8, 1}, {8, 5, 8, 1}, {1, 0, 8, 1}, {0, 1, 8, 1}, {7, 3, 8, 1},  // Logic mode
        {15, 23, 8, 0}, {8, 5, 8, 0}, {1, 0, 8, 0}, {0, 1, 8, 0}, {7, 3, 8, 0},  // Arithmetic mode

        // 1001 - (A XOR B)' (Logic), (A + B) plus AB (Arithmetic)
        {15, 23, 9, 1}, {8, 5, 9, 1}, {1, 0, 9, 1}, {0, 1, 9, 1}, {7, 3, 9, 1},  // Logic mode
        {15, 23, 9, 0}, {8, 5, 9, 0}, {1, 0, 9, 0}, {0, 1, 9, 0}, {7, 3, 9, 0},  // Arithmetic mode

        // 1010 - B (Logic), (A + B') plus AB (Arithmetic)
        {15, 23, 10, 1}, {8, 5, 10, 1}, {1, 0, 10, 1}, {0, 1, 10, 1}, {7, 3, 10, 1},  // Logic mode
        {15, 23, 10, 0}, {8, 5, 10, 0}, {1, 0, 10, 0}, {0, 1, 10, 0}, {7, 3, 10, 0},  // Arithmetic mode

        // 1011 - AB (Logic), AB minus 1 (Arithmetic)
        {15, 23, 11, 1}, {8, 5, 11, 1}, {1, 0, 11, 1}, {0, 1, 11, 1}, {7, 3, 11, 1},  // Logic mode
        {15, 23, 11, 0}, {8, 5, 11, 0}, {1, 0, 11, 0}, {0, 1, 11, 0}, {7, 3, 11, 0},  // Arithmetic mode

        // 1100 - Logical 1 (Logic), A plus A (Arithmetic)
        {15, 23, 12, 1}, {8, 5, 12, 1}, {1, 0, 12, 1}, {0, 1, 12, 1}, {7, 3, 12, 1},  // Logic mode
        {15, 23, 12, 0}, {8, 5, 12, 0}, {1, 0, 12, 0}, {0, 1, 12, 0}, {7, 3, 12, 0},  // Arithmetic mode

        // 1101 - A + B' (Logic), (A + B') plus A (Arithmetic)
        {15, 23, 13, 1}, {8, 5, 13, 1}, {1, 0, 13, 1}, {0, 1, 13, 1}, {7, 3, 13, 1},  // Logic mode
        {15, 23, 13, 0}, {8, 5, 13, 0}, {1, 0, 13, 0}, {0, 1, 13, 0}, {7, 3, 13, 0},  // Arithmetic mode

        // 1110 - (A + B)' (Logic), (A + B') plus A (Arithmetic)
        {15, 23, 14, 1}, {8, 5, 14, 1}, {1, 0, 14, 1}, {0, 1, 14, 1}, {7, 3, 14, 1},  // Logic mode
        {15, 23, 14, 0}, {8, 5, 14, 0}, {1, 0, 14, 0}, {0, 1, 14, 0}, {7, 3, 14, 0},  // Arithmetic mode

        // 1111 - A (Logic), A minus 1 (Arithmetic)
        {15, 23, 15, 1}, {8, 5, 15, 1}, {1, 0, 15, 1}, {0, 1, 15, 1}, {7, 3, 15, 1},  // Logic mode
        {15, 23, 15, 0}, {8, 5, 15, 0}, {1, 0, 15, 0}, {0, 1, 15, 0}, {7, 3, 15, 0}   // Arithmetic mode
    };

    int total_test_cases = 160; // Original number of test cases
    int carry_values[2] = {0, 1}; // Possible carry_in values

    for (int i = 0; i < total_test_cases; i++) {
        for (int carry_idx = 0; carry_idx < 2; carry_idx++) {
            int carry_in = carry_values[carry_idx];
            tb->carry_in = carry_in;
            tb->in_a = test_cases[i][0];
            tb->in_b = test_cases[i][1];
            tb->select = test_cases[i][2];
            tb->mode = test_cases[i][3];

            // Evaluate the model (tick the clock)
            tb->eval();

            // Calculate a unique test number considering carry_in
            int test_number = i * 2 + carry_idx + 1;

std::cout << "Test " << test_number << " A: " << test_cases[i][0] << " B: " << test_cases[i][1] << " Select: " << test_cases[i][2] << " Mode: " << test_cases[i][3]
                      << " (carry_in = " << carry_in << ")" << std::endl << "ALU Output = " << tb->alu_out << std::endl
                      << ", COut = " << static_cast<int>(tb->carry_out) << std::endl
                      << ", Compare = " << static_cast<int>(tb->compare) << std::endl;
        }
    }

    // Final cleanup
    tb->final();

    // Clean up dynamically allocated memory
    delete tb;

    return 0;
}
