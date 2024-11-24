#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <bitset>
#include <sstream>
#include <iomanip>

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

std::string get_instruction_name(uint16_t Rx, uint16_t Ry, uint16_t ALU_sel, uint16_t format, uint16_t immediate = 0) {
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
    if (format == 0b00) {
        return instruction_name + " r" + std::to_string(Rx) + " r" + std::to_string(Ry);
    } else {
        return instruction_name + " r" + std::to_string(Rx) + " #" + std::to_string(immediate);
    }
}

std::string get_binary_instruction(int Rx, int Ry, std::string ALU_sel, bool is_immediate = false, int immediate = 0) {
    std::string binary_instruction;
    if (ALU_sel == "ADD" || ALU_sel == "ADDI") binary_instruction = "000";
    else if (ALU_sel == "SUB" || ALU_sel == "SUBI") binary_instruction = "001";
    else if (ALU_sel == "AND" || ALU_sel == "ANDI") binary_instruction = "010";
    else if (ALU_sel == "OR" || ALU_sel == "ORI") binary_instruction = "011";
    else if (ALU_sel == "XOR" || ALU_sel == "XORI") binary_instruction = "100";
    else if (ALU_sel == "SHL" || ALU_sel == "SHLI") binary_instruction = "101";
    else if (ALU_sel == "SHR" || ALU_sel == "SHRI") binary_instruction = "110";
    else if (ALU_sel == "CMP" || ALU_sel == "CMPI") binary_instruction = "111";

    std::string Rx_bin = std::bitset<3>(Rx).to_string();
    std::string Ry_bin = is_immediate ? std::bitset<8>(immediate).to_string() : std::bitset<3>(Ry).to_string();

    if (is_immediate) {
        return Rx_bin + Ry_bin + binary_instruction + "01";
    } else {
        return Rx_bin + Ry_bin + "00000" + binary_instruction + "00";
    }
}

std::vector<std::string> assemble(std::vector<std::string> instructions) {
    std::vector<std::string> assembled_instructions;
    for (std::string instruction : instructions) {
        std::istringstream iss(instruction);
        std::string ALU_sel, Rx_str, Ry_or_imm_str;
        iss >> ALU_sel >> Rx_str >> Ry_or_imm_str;

        int Rx = std::stoi(Rx_str.substr(1));
        bool is_immediate = (ALU_sel.back() == 'I');
        int Ry_or_imm = std::stoi(Ry_or_imm_str.substr(1));

        std::string binary_instruction = get_binary_instruction(Rx, Ry_or_imm, ALU_sel, is_immediate, Ry_or_imm);
        std::uint16_t hex_instruction = std::stoul(binary_instruction, nullptr, 2);
        std::stringstream ss;
        ss << std::hex << std::setw(4) << std::setfill('0') << hex_instruction;
        assembled_instructions.push_back(ss.str());
    }
    assembled_instructions.push_back("0020");
    return assembled_instructions;
}

std::vector<std::string> disassemble(std::vector<std::string> instructions) {
    std::vector<std::string> disassembled_instructions;

    for (std::string instruction : instructions) {
        uint16_t binary = std::stoul(instruction, nullptr, 16); 
        uint16_t Rx = (binary >> 13) & 0x07; 
        uint16_t format = binary & 0x03;
        uint16_t ALU_sel = (binary >> 2) & 0x07; 

        if (format == 0b00) {
            uint16_t Ry = (binary >> 10) & 0x07;
            disassembled_instructions.push_back(get_instruction_name(Rx, Ry, ALU_sel, format));
        } else {
            uint16_t immediate = (binary >> 5) & 0xFF;
            disassembled_instructions.push_back(get_instruction_name(Rx, 0, ALU_sel, format, immediate));
        }
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
