#include "Valu.h"
#include "verilated.h"
#include <iostream>
#include <array> 

int alu(int a, int b, int sel);

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Valu *tb = new Valu;

    int a = 3;
    int b = 4;
    int select = 0;

    for (select = 0; select < 8; select++){

    tb->in_a = a;
    tb->in_b = b;
    tb->select = select;

    int out = alu(a, b, select);

    tb->eval();

    std::cout << " A: " << a << " B: " << b 
              << " Select: " << select << std::endl

              << "ALU Output = " << static_cast<int16_t>(tb->alu_out)
              << " (Expected = " << out << ") "
              << (static_cast<int16_t>(tb->alu_out) == out ? "PASS" : "FAIL")
              << std::endl;}
    
    tb->final();
    delete tb;

    return 0;
}


int alu(int a, int b, int sel) {

    int out = 0;

    switch (sel) {
        case 0:  out = a + b; break;
        case 1:  out = a - b; break;
        case 2:  out = a & b; break;
        case 3:  out = a | b; break;
        case 4:  out = a ^ b; break;
        case 5:  out = a << b; break;
        case 6:  out = a >> b ; break;
        case 7:  out = (a == b) ? 0 : (a > b) ? 1 : 2; break;
        default: out = 0; break;
    }
    return out;
}
