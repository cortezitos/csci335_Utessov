#include <iostream>
#include <bitset>

#define BIT_16(x) (x & 0xFFFF) // To simulate 16-bit behavior

class BittyCore {
public:
    uint16_t registers[8];
    uint16_t reg_s;
    uint16_t reg_c;
    uint16_t alu_out;
    uint8_t carry_out;
    uint8_t compare;
    
    BittyCore() {
        reset();
    }

    void reset() {
        for (int i = 0; i < 8; i++) {
            registers[i] = 0;
        }
        reg_s = 0;
        reg_c = 0;
        alu_out = 0;
        carry_out = 0;
        compare = 0;
    }

    void runInstruction(uint16_t instruction) {
        // Decode the instruction based on the provided scheme
        uint8_t mux_sel = (instruction >> 13) & 0x07;  // Top 3 bits for mux_sel
        uint8_t reg_c_sel = (instruction >> 10) & 0x07; // Next 3 bits for reg_c_sel
        uint8_t alu_sel = (instruction >> 6) & 0x0F;   // ALU select bits
        uint8_t mode = (instruction >> 2) & 0x01;      // Mode bit (logic/arithmetic)
        
        // Simulate mux selecting
        uint16_t mux_out = muxSelect(mux_sel);
        
        // Perform ALU operation
        alu(reg_s, mux_out, alu_sel, mode);
        
        // Store result in reg_c if the control unit enables it
        reg_c = alu_out;
        
        // Optionally store the result in one of the registers
        storeResult(reg_c_sel, alu_out);
    }

    void printState() {
        std::cout << "Register states:\n";
        for (int i = 0; i < 8; i++) {
            std::cout << "Reg[" << i << "] = " << std::bitset<16>(registers[i]) << "\n";
        }
        std::cout << "Reg S = " << std::bitset<16>(reg_s) << "\n";
        std::cout << "Reg C = " << std::bitset<16>(reg_c) << "\n";
        std::cout << "ALU Out = " << std::bitset<16>(alu_out) << "\n";
        std::cout << "Carry Out = " << std::bitset<1>(carry_out) << "\n";
        std::cout << "Compare = " << std::bitset<1>(compare) << "\n";
    }

private:
    uint16_t muxSelect(uint8_t mux_sel) {
        // Select between registers and return the result
        if (mux_sel < 8) {
            return registers[mux_sel];
        }
        return reg_s;
    }

    void alu(uint16_t in_a, uint16_t in_b, uint8_t sel, uint8_t mode) {
        // Perform ALU operation
        if (mode == 1) { // Logic mode
            switch (sel) {
                case 0x0: alu_out = ~in_a; break;
                case 0x1: alu_out = ~(in_a | in_b); break;
                case 0x2: alu_out = ~in_a & in_b; break;
                // Add more logic cases as needed
                default: alu_out = 0;
            }
        } else { // Arithmetic mode
            switch (sel) {
                case 0x0: alu_out = in_a + in_b; break;
                case 0x1: alu_out = in_a - in_b; break;
                // Add more arithmetic cases as needed
                default: alu_out = 0;
            }
        }
        
        // Set carry and compare
        carry_out = (alu_out > 0xFFFF);  // Simplified carry logic
        compare = (in_a == in_b);
        
        // Ensure ALU result is 16-bit
        alu_out = BIT_16(alu_out);
    }

    void storeResult(uint8_t reg_sel, uint16_t value) {
        // Store result in the corresponding register based on reg_sel
        if (reg_sel < 8) {
            registers[reg_sel] = value;
        }
    }
};

int main() {
    BittyCore core;

    // Test: Load value into Reg S and perform an ALU addition
    core.reg_s = 0x0A0A;  // Load a value into Reg S

    // Test instruction: Load from Reg 1, add it with Reg S
    uint16_t instruction = 0b0000000001100101;  // Example instruction
    core.runInstruction(instruction);

    core.printState();

    return 0;
}
