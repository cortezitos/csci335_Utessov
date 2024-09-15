#include "Vkeylock.h"
#include "verilated.h"
#include <iostream>

int main(int argc, char **argv) {
    // Initialize Verilator
    Verilated::commandArgs(argc, argv);

    // Instantiate the Verilog module
    Vkeylock *tb = new Vkeylock;

    tb->reset = 1;  // Assert reset for initialization
    tb->eval();     // Evaluate model

    tb->reset = 0;  // Deassert reset

    // Simulate the key sequence 335256
    int code[6] = {3, 3, 5, 2, 5, 6};
    for (int i = 0; i < 6; i++) {
        tb->key = code[i];  // Send each digit
        tb->eval();         // Evaluate after each input
        std::cout << "Key entered: " << code[i] << ", Locked state: " << tb->locked << std::endl;
    }

    if (tb->locked == 0) {
        std::cout << "Unlocked successfully!" << std::endl;
    } else {
        std::cout << "Failed to unlock." << std::endl;
    }

    // Final cleanup
    tb->final();
    delete tb;

    return 0;
}
