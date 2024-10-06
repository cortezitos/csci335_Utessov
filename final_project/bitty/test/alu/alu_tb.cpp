#include "Valu.h"
#include "verilated.h"
#include <iostream>
#include <array> 

void alu(int a, int b, int sel, int mode, int out[]);

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Valu *tb = new Valu;

    int a = 47;
    int b = 59;
    int select = 4;
    int mode = 1;

    int out[3] = {0, 0, 0};

    tb->in_a = a;
    tb->in_b = b;
    tb->select = select;
    tb->mode = mode;

    alu(a, b, select, mode, out);

    tb->eval();

    std::cout << " A: " << a << " B: " << b 
              << " Select: " << select << " Mode: " << mode
              << std::endl 
              << "ALU Output = " << static_cast<int16_t>(tb->alu_out)
              << " (Expected = " << out[0] << ") "
              << (static_cast<int16_t>(tb->alu_out) == out[0] ? "PASS" : "FAIL")
              << std::endl
              << "Carry Out = " << static_cast<int>(tb->carry_out) 
              << " (Expected = " << out[1] << ") "
              << (static_cast<int>(tb->carry_out) == out[1] ? "PASS" : "FAIL")
              << std::endl
              << "Compare = " << static_cast<int>(tb->compare) 
              << " (Expected = " << out[2] << ") "
              << (static_cast<int>(tb->compare) == out[2] ? "PASS" : "FAIL")
              << std::endl;

    
    tb->final();
    delete tb;

    return 0;
}


void alu(int a, int b, int sel, int mode, int out[]) {
    out[1] = 0;          
    out[2] = (a == b);   

    switch (mode) {
    case 0: // Arithmetic mode
        switch (sel) {
            case 0:  out[0] = a; break;
            case 1:  out[0] = a | b; break;
            case 2:  out[0] = a | ~b; break;
            case 3:  out[0] = -1; break;
            case 4:  out[0] = a | (a & ~b); break;
            case 5:  out[0] = (a | b) + (a & ~b); break;
            case 6:  out[0] = a - b - 1; break;
            case 7:  out[0] = (a & ~b) - 1; break;
            case 8:  out[0] = a + (a & b); break;
            case 9:  out[0] = a + b; break;
            case 10: out[0] = (a | ~b) + (a & b); break;
            case 11: out[0] = (a & b) - 1; break;
            case 12: out[0] = a + a; break;
            case 13: out[0] = (a | b) + a; break;
            case 14: out[0] = (a | ~b) + a; break;
            case 15: out[0] = a - 1; break;
            default: out[0] = 0; break;
        }
        break;
    case 1: // Logic mode
        switch (sel) {
            case 0:  out[0] = ~a; break;
            case 1:  out[0] = ~(a | b); break;
            case 2:  out[0] = ~a | b; break;
            case 3:  out[0] = 0; break;
            case 4:  out[0] = ~(a & b); break;
            case 5:  out[0] = ~b; break;
            case 6:  out[0] = a ^ b; break;
            case 7:  out[0] = a & ~b; break;
            case 8:  out[0] = ~a | b; break;
            case 9:  out[0] = ~(a ^ b); break;
            case 10: out[0] = b; break;
            case 11: out[0] = a & b; break;
            case 12: out[0] = 1; break;
            case 13: out[0] = a | ~b; break;
            case 14: out[0] = a | b; break;
            case 15: out[0] = a; break;
            default: out[0] = 0; break;
        }
        break;
    default:
        out[0] = 0;
        break;
    }
}
