#include "Vkeylock.h"
#include "verilated.h"
#include "verilated_vcd_c.h"  
#include <iostream>

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    Vkeylock *tb = new Vkeylock;

    Verilated::traceEverOn(true);  
    VerilatedVcdC* vcd_trace = new VerilatedVcdC;  
    tb->trace(vcd_trace, 99);  
    vcd_trace->open("keylock_trace.vcd");  

    tb->clk = 0;
    tb->reset = 1;  
    tb->eval();    
    vcd_trace->dump(0);  
    tb->reset = 0;  

    tb->clk = !tb->clk;
    tb->eval();
    tb->clk = !tb->clk;
    tb->eval();
    int code[6] = {3, 3, 5, 2, 5, 6};
    for (int i = 0; i < 6; i++) {
        tb->clk = !tb->clk;
        tb->key = code[i];  
        tb->eval();        
        vcd_trace->dump(i * 10);  
        tb->clk = !tb->clk;
        tb->eval();
        std::cout << "Key entered: " << code[i] << ", Locked state: " << static_cast<int>(tb->locked) << std::endl;

    }
    tb->clk = !tb->clk;
    tb->eval();
    vcd_trace->dump(60);

    if (tb->locked == 0) {
        std::cout << "Unlocked successfully!" << std::endl;
    } else {
        std::cout << "Failed to unlock." << std::endl;
    }

    vcd_trace->close();  
    tb->final();  

    return 0;
}
