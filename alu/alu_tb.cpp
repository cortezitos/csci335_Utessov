#include "Valu.h"
#include "verilated.h"
#include <iostream>

int main(int argc, char **argv) {
    // Initialize Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the Verilog module
    Valu *tb = new Valu;

    // Test cases array: {in_a, in_b, select, mode}
    int a = 12;
    int b = 13;
    int carry_in = 0;
    int select = 9;
    int mode = 0;
    int out[] = [0, 0, 0];

    tb->carry_in = carry_in;
    tb->in_a = a;
    tb->in_b = b;
    tb->select = select;
    tb->mode = mode;

    alu(a, b, select, mode, carry_in, out);

    // Evaluate the model (tick the clock)
    tb->eval();

std::cout << "Test " << test_number << " A: " << a << " B: " << b << " Select: " << select << " Mode: " << mode
                      << " (carry_in = " << carry_in << ")" << std::endl << "ALU Output = " << tb->alu_out << " " << tb->alu_out == out[0] << std::endl
                      << "COut = " << static_cast<int>(tb->carry_out) << " " << static_cast<int>(tb->carry_out) == out[1] << std::endl
                      << "Compare = " << static_cast<int>(tb->compare) << " " << static_cast<int>(tb->compare) == out[2] << std::endl;


    // Final cleanup
    tb->final();

    // Clean up dynamically allocated memory
    delete tb;

    return 0;
}

void alu(int a, int b, int sel, int mode, int carry_in, int[3] out){
    out[1] = 0;
    out[2] = (a == b);
    switch(mode){
    case 0:
        switch (sel){
            case 0: out[0] = a;
            case 1: out[0] = a | b;
            case 2: out[0] = a | ~b;
            case 3: out[0] = -1;
            case 4: out[0] = a | a & ~b;
            case 5: out[0] = (a | b) + a & ~b;
            case 6: out[0] = a - b - 1;
            case 7: out[0] = a & ~b - 1;
            case 8: out[0] = a + a & b;
            case 9: out[0] = a + b;
            case 10: out[0] = (a | ~b) + a & b;
            case 11: out[0] = a & b - 1;
            case 12: out[0] = a + a;
            case 13: out[0] = (a | b) + a;
            case 14: out[0] = (a | ~b) + a;
            case 15: out[0] = a - 1;
        }
    case 1:
        switch (sel){
            case 0: out[0] = ~a;
            case 1: out[0] = ~(a | b);
            case 2: out[0] = ~a | b;
            case 3: out[0] = 0;
            case 4: out[0] = ~(a & b);
            case 5: out[0] = ~b;
            case 6: out[0] = a ^ b;
            case 7: out[0] = a & ~b;
            case 8: out[0] = ~a | b;
            case 9: out[0] = ~(a ^ b);
            case 10: out[0] = b;
            case 11: out[0] = a & b;
            case 12: out[0] = 1;
            case 13: out[0] = a | ~b;
            case 14: out[0] = a | b;
            case 15: out[0] = a;
            }
    }
}