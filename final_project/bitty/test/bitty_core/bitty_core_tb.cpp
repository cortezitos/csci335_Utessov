#include "Vbitty_core.h"
#include "verilated.h"
#include <iostream>
#include <bitset>
#include <fstream>
#include "BittyEmulator/BittyEmulator.h"
#include "BittyInstructionGenerator/BittyInstructionGenerator.h"
#include <iomanip>

// this is for guthub -- everything works well lab 11
void toggle_clock(Vbitty_core *tb) {
    tb->clk = !tb->clk;
    tb->eval();
    tb->clk = !tb->clk;
    tb->eval();
}

// extern "C" void notify_reached_done() {
//     std::cout << "Counter reached done!" << std::endl;
// }

void generate_instructions() {
    BittyInstructionGenerator generator;
    std::ofstream outFile("instructions.mem");
    
    int num_instructions;
    std::cout << "How many instructions do you want to generate? ";
    std::cin >> num_instructions;
    
    for (int i = 0; i < num_instructions; i++) {
        uint16_t instruction = generator.Generate();
        outFile << std::hex << std::setw(4) << std::setfill('0') << instruction << std::endl;
    }
    // Add halt instruction
    outFile << "0001" << std::endl;
    outFile.close();
}

int main(int argc, char **argv) {
    // Generate instructions first
    generate_instructions();
    
    Verilated::commandArgs(argc, argv);
    Vbitty_core *tb = new Vbitty_core;
    BittyEmulator emulator;
    
    int passed_instructions = 0;
    int total_instructions = 0;

    tb->clk = 0;
    tb->reset = 1;
    toggle_clock(tb);
    tb->reset = 0;

    // Set initial register values to match emulator
    tb->reg_0_out = emulator.GetRegisterValue(0);
    tb->reg_1_out = emulator.GetRegisterValue(1);
    tb->reg_2_out = emulator.GetRegisterValue(2);
    tb->reg_3_out = emulator.GetRegisterValue(3);
    tb->reg_4_out = emulator.GetRegisterValue(4);
    tb->reg_5_out = emulator.GetRegisterValue(5);
    tb->reg_6_out = emulator.GetRegisterValue(6);
    tb->reg_7_out = emulator.GetRegisterValue(7);
    toggle_clock(tb);

    tb->run = 1;

    std::cout << "Initial register values:" << std::endl;
    for (int i = 0; i < 8; i++) {
        uint16_t hw_val = (i == 0) ? tb->reg_0_out :
                         (i == 1) ? tb->reg_1_out :
                         (i == 2) ? tb->reg_2_out :
                         (i == 3) ? tb->reg_3_out :
                         (i == 4) ? tb->reg_4_out :
                         (i == 5) ? tb->reg_5_out :
                         (i == 6) ? tb->reg_6_out : tb->reg_7_out;
        
        std::cout << "reg_" << i << ": Hardware " << static_cast<int>(hw_val) 
                 << " Emulator " << emulator.GetRegisterValue(i) 
                 << (hw_val == emulator.GetRegisterValue(i) ? " PASS" : " FAIL") 
                 << std::endl;
    }
    std::cout << std::endl;

    do {
        toggle_clock(tb);
        uint16_t current_instruction = tb->instruction;
        if (current_instruction == 0x0000) break;
        
        total_instructions++;
        std::cout << "\nInstruction " << total_instructions << ": " 
                 << std::bitset<16>(current_instruction) << "\n";

        // Run the same instruction through emulator
        uint16_t emulator_result = emulator.Evaluate(current_instruction);

        toggle_clock(tb);
        toggle_clock(tb);
        toggle_clock(tb);

        // Compare results
        bool instruction_passed = true;
        for (int i = 0; i < 8; i++) {
            uint16_t hw_val = (i == 0) ? tb->reg_0_out :
                             (i == 1) ? tb->reg_1_out :
                             (i == 2) ? tb->reg_2_out :
                             (i == 3) ? tb->reg_3_out :
                             (i == 4) ? tb->reg_4_out :
                             (i == 5) ? tb->reg_5_out :
                             (i == 6) ? tb->reg_6_out : tb->reg_7_out;
            
            uint16_t em_val = emulator.GetRegisterValue(i);
            bool reg_match = (hw_val == em_val);
            instruction_passed &= reg_match;
            
            std::cout << "reg_" << i << ": Hardware " << static_cast<int>(hw_val) 
                     << " Emulator " << em_val 
                     << (reg_match ? " PASS" : " FAIL") << std::endl;
        }
        
        if (instruction_passed) {
            passed_instructions++;
        }
        
        std::cout << "\nInstruction Result: " 
                 << (instruction_passed ? "PASS" : "FAIL") << std::endl;

    } while (tb->instruction != 0x0001);

    std::cout << "\nFinal Results:" << std::endl;
    std::cout << "Total Instructions: " << total_instructions << std::endl;
    std::cout << "Passed Instructions: " << passed_instructions << std::endl;
    std::cout << "Failed Instructions: " << (total_instructions - passed_instructions) << std::endl;
    std::cout << "Success Rate: " 
              << (total_instructions > 0 ? (passed_instructions * 100.0 / total_instructions) : 0) 
              << "%" << std::endl;

    tb->final();
    delete tb;
    return 0;
}
