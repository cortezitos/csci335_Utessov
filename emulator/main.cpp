#include "BittyEmulator.h"
#include "BittyInstructionGenerator.h"
#include <bitset>
#include <fstream>


int main() {
    BittyEmulator emulator;

    std::cout << "Register 0 value: " << emulator.GetRegisterValue(0) << std::endl;
    std::cout << "Register 1 value: " << emulator.GetRegisterValue(1) << std::endl;
    std::cout << "Register 2 value: " << emulator.GetRegisterValue(2) << std::endl;
    std::cout << "Register 3 value: " << emulator.GetRegisterValue(3) << std::endl;
    std::cout << "Register 4 value: " << emulator.GetRegisterValue(4) << std::endl;
    std::cout << "Register 5 value: " << emulator.GetRegisterValue(5) << std::endl;
    std::cout << "Register 6 value: " << emulator.GetRegisterValue(6) << std::endl;
    std::cout << "Register 7 value: " << emulator.GetRegisterValue(7) << std::endl;

    std::cout << std::endl;

    std::ifstream inFile("instructions.txt");
    while(!inFile.eof()) {
        uint16_t instruction;
        inFile >> std::hex >> instruction;
        std::cout << "Instruction: " << std::bitset<16>(instruction) << std::endl;

        uint16_t Rx = (instruction >> 13) & 0x07; 
        uint16_t Ry = (instruction >> 10) & 0x07;
        uint16_t ALU_sel = (instruction >> 2) & 0x07;

        std::cout << "Rx: " << Rx << std::endl;
        std::cout << "Ry: " << Ry << std::endl;
        std::cout << "ALU_sel: " << ALU_sel << std::endl;

        emulator.Evaluate(instruction);


        uint16_t regValue = emulator.GetRegisterValue(Rx);

        std::cout << "Register Rx value: " << regValue << std::endl;
        std::cout << std::endl;
    }




    return 0;
}
