#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <bitset>

std::vector<std::string> read_file(std::string file_path) {
    std::ifstream file(file_path);
    std::string line;
    std::vector<std::string> instructions;
    while (std::getline(file, line)) {
        instructions.push_back(line);
    }
    return instructions;
}

void write_file(std::vector<std::string> instructions, std::string file_path) {
    std::ofstream file(file_path);
    for (std::string instruction : instructions) {
        file << instruction << std::endl;
    }
}

std::string get_instruction_name(uint16_t Rx, uint16_t Ry, uint16_t ALU_sel) {
    std::string instruction_name;
    switch (ALU_sel) {
        case 0b000:  instruction_name = "ADD"; break;
        case 0b001:  instruction_name = "SUB"; break;
        case 0b010:  instruction_name = "AND"; break;
        case 0b011:  instruction_name = "OR"; break;
        case 0b100:  instruction_name = "XOR"; break;
        case 0b101:  instruction_name = "SHL"; break;
        case 0b110:  instruction_name = "SHR"; break;
        case 0b111:  instruction_name = "CMP"; break;
    }
    return instruction_name + " " + std::to_string(Rx) + " " +std::to_string(Ry);
}

std::string get_binary_instruction(int Rx, int Ry, std::string ALU_sel) {
    std::string binary_instruction;
    if (ALU_sel == "ADD") binary_instruction = "000";
    else if (ALU_sel == "SUB") binary_instruction = "001";
    else if (ALU_sel == "AND") binary_instruction = "010";
    else if (ALU_sel == "OR") binary_instruction = "011";
    else if (ALU_sel == "XOR") binary_instruction = "100";
    else if (ALU_sel == "SHL") binary_instruction = "101";
    else if (ALU_sel == "SHR") binary_instruction = "110";
    else if (ALU_sel == "CMP") binary_instruction = "111";

    std::string Rx_bin = std::bitset<3>(Rx).to_string();
    std::string Ry_bin = std::bitset<3>(Ry).to_string();

    return Rx_bin + Ry_bin + "00000" + binary_instruction + "00";
}

std::vector<std::string> assemble(std::vector<std::string> instructions) {
    std::vector<std::string> assembled_instructions;
    for (std::string instruction : instructions) {
        int Rx = std::stoi(instruction.substr(4));
        int Ry = std::stoi(instruction.substr(6));
        std::string ALU_sel = instruction.substr(0, 3);
        assembled_instructions.push_back(get_binary_instruction(Rx, Ry, ALU_sel));
    }
    return assembled_instructions;
}

std::vector<std::string> disassemble(std::vector<std::string> instructions) {
    std::vector<std::string> disassembled_instructions;

    for (std::string instruction : instructions) {
        uint16_t binary = std::stoul(instruction, nullptr, 16); 
        uint16_t Rx = (binary >> 13) & 0x07; 
        uint16_t Ry = (binary >> 10) & 0x07;
        uint16_t ALU_sel = (binary >> 2) & 0x07; 
        disassembled_instructions.push_back(get_instruction_name(Rx, Ry, ALU_sel));
    }
    return disassembled_instructions;
}



int main(int argc, char* argv[]) {
    if (argc > 3) {  
        
        std::string input_file;

        if (std::string(argv[1]) == "-i") {
            std::cout << "Interactive mode" << std::endl;
            input_file = argv[2];
            std::cout << "Input file: " << input_file << std::endl;
        } else {
            std::cerr << "Invalid argument for input (-i)!" << std::endl;
            return 1;
        }

        std::string output_file;
        bool output_to_file = false;
        for (int i = 3; i < argc; ++i) {
            if (std::string(argv[i]) == "-o" && i + 1 < argc) {
                output_to_file = true;
                output_file = argv[i + 1];
            }
        }

        if (output_to_file) {
            std::cout << "Output will be written to file: " << output_file << std::endl;
        } else {
            std::cout << "No output file specified. Output will be displayed on the terminal." << std::endl;
        }

        bool assemble_flag;

        if (argc > 3 && std::string(argv[argc - 1]) == "-a") {
            std::cout << "Assemble mode" << std::endl;
            assemble_flag = true;
        } else if (argc > 3 && std::string(argv[argc - 1]) == "-d") {
            std::cout << "Disassemble mode" << std::endl;
            assemble_flag = false;
        } else {
            std::cerr << "Invalid argument for mode (-a or -d)!" << std::endl;
            return 1;
        }

        std::vector<std::string> instructions = read_file(input_file);


        std::vector<std::string> func_instructions;

        if (assemble_flag) {
            func_instructions = assemble(instructions);
        } else {
            func_instructions = disassemble(instructions);
        }

        if (output_to_file) {
            write_file(func_instructions, output_file);
        } else {
            for (std::string instruction : func_instructions) {
                std::cout << instruction << std::endl;
            }
        }
    } else {
        std::cerr << "Insufficient arguments provided!" << std::endl;
        std::cerr << "Usage: ./ass -i <input_file> [-o <output_file>] <-a|-d>" << std::endl;
        return 1;
    }

    return 0;
}
