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



std::string get_binary_alu(std::string command, std::string Rx, std::string Ry) {
    std::string binary_instruction;
    if (command == "add") binary_instruction = "000";
    else if (command == "sub") binary_instruction = "001";
    else if (command == "and") binary_instruction = "010";
    else if (command == "or") binary_instruction = "011";
    else if (command == "xor") binary_instruction = "100";
    else if (command == "shl") binary_instruction = "101";
    else if (command == "shr") binary_instruction = "110";
    else if (command == "cmp") binary_instruction = "111";

    int new_Rx = std::stoi(Rx.substr(1));
    int new_Ry = std::stoi(Ry.substr(1));

    std::string binaryRx = std::bitset<3>(new_Rx).to_string();
    std::string binaryRy = std::bitset<3>(new_Ry).to_string();

    
    return binaryRx + binaryRy + "00000" + binary_instruction + "00";

}

std::string get_binary_branch(std::string command, std::string immediate) {
    std::string binary_instruction;
    if (command == "bie") binary_instruction = "00";
    else if (command == "big") binary_instruction = "01";
    else if (command == "bil") binary_instruction = "10";

    int new_immediate = std::stoi(immediate.substr(1));

    std::string binaryImmediate = std::bitset<12>(new_immediate).to_string();

    return binaryImmediate + binary_instruction + "10";
}

std::string get_binary_immediate(std::string command, std::string Rx, std::string immediate) {
    std::string binary_instruction;
    if (command == "addi") binary_instruction = "000";
    else if (command == "subi") binary_instruction = "001";
    else if (command == "andi") binary_instruction = "010";
    else if (command == "ori") binary_instruction = "011";
    else if (command == "xori") binary_instruction = "100";
    else if (command == "shli") binary_instruction = "101";
    else if (command == "shri") binary_instruction = "110";
    else if (command == "cmpi") binary_instruction = "111";

    int new_Rx = std::stoi(Rx.substr(1));
    int new_immediate = std::stoi(immediate.substr(1));

    std::string binaryRx = std::bitset<3>(new_Rx).to_string();
    std::string binaryImmediate = std::bitset<8>(new_immediate).to_string();

    return binaryRx + binaryImmediate + binary_instruction + "01";
}


std::vector<std::string> assemble(std::vector<std::string> instructions) {
    std::vector<std::string> assembled_instructions;
    for (std::string instruction : instructions) {
        std::istringstream iss(instruction);
        std::string command, operand1, operand2;
        iss >> command >> operand1;

        std::string binary_instruction;

        if (command[0] == 'b') {
            binary_instruction = get_binary_branch(command, operand1);
        } else {
            iss >> operand2;
            if (operand2[0] == '#') {
                binary_instruction = get_binary_immediate(command, operand1, operand2);
            } else {
                binary_instruction = get_binary_alu(command, operand1, operand2);
            }
        }

        uint16_t value = static_cast<uint16_t>(std::stoi(binary_instruction, nullptr, 2));
        std::stringstream ss;
        ss << std::hex << std::setw(4) << std::setfill('0') << value;
        assembled_instructions.push_back(ss.str());
    }
    assembled_instructions.push_back("0020");
    return assembled_instructions;
}


std::string dissasemble_alu(std::string instruction) {
    std::string ALU_sel = instruction.substr(instruction.size() - 5, 3);

    std::string instruction_name;

    if (ALU_sel == "000") instruction_name = "add";
    else if (ALU_sel == "001") instruction_name = "sub";
    else if (ALU_sel == "010") instruction_name = "and";
    else if (ALU_sel == "011") instruction_name = "or";
    else if (ALU_sel == "100") instruction_name = "xor";
    else if (ALU_sel == "101") instruction_name = "shl";
    else if (ALU_sel == "110") instruction_name = "shr";
    else if (ALU_sel == "111") instruction_name = "cmp";
    else instruction_name = "Unknown ALU operation";

    std::string Rx = instruction.substr(0, 3);   
    std::string Ry = instruction.substr(3, 3);    

    int Rx_int = std::stoi(Rx, nullptr, 2);
    int Ry_int = std::stoi(Ry, nullptr, 2);

    return instruction_name + " r" + std::to_string(Rx_int) + " r" + std::to_string(Ry_int);
}


std::string dissasemble_immediate(std::string instruction) {
    std::string ALU_sel = instruction.substr(instruction.size() - 5, 3);

    std::string instruction_name;

    if (ALU_sel == "000") instruction_name = "addi";
    else if (ALU_sel == "001") instruction_name = "subi";
    else if (ALU_sel == "010") instruction_name = "andi";
    else if (ALU_sel == "011") instruction_name = "ori";
    else if (ALU_sel == "100") instruction_name = "xori";
    else if (ALU_sel == "101") instruction_name = "shli";
    else if (ALU_sel == "110") instruction_name = "shri";
    else if (ALU_sel == "111") instruction_name = "cmpi";
    else instruction_name = "Unknown immediate operation";

    std::string Rx = instruction.substr(0, 3);            
    std::string immediate = instruction.substr(3, 8);     

    int Rx_int = std::stoi(Rx, nullptr, 2);
    int immediate_int = std::stoi(immediate, nullptr, 2);

    return instruction_name + " r" + std::to_string(Rx_int) + " #" + std::to_string(immediate_int);
}


std::string dissasemble_branch(std::string instruction) {
    std::string branch_sel = instruction.substr(instruction.size() - 4, 2);

    std::string instruction_name;

    if (branch_sel == "00") instruction_name = "bie";
    else if (branch_sel == "01") instruction_name = "big";
    else if (branch_sel == "10") instruction_name = "bil";
    else instruction_name = "Unknown branch operation";

    std::string immediate = instruction.substr(0, 12);  

    int immediate_int = std::stoi(immediate, nullptr, 2);

    return instruction_name + " #" + std::to_string(immediate_int);
}




std::vector<std::string> disassemble(std::vector<std::string> instructions) {
    std::vector<std::string> disassembled_instructions;

    for (std::string instruction : instructions) {

        uint16_t binary_value = static_cast<uint16_t>(std::stoul(instruction, nullptr, 16));
        std::string binary_instruction = std::bitset<16>(binary_value).to_string();

        std::string last_two_bits = binary_instruction.substr(binary_instruction.size() - 2);

        std::string disassembled_instruction;

        if (last_two_bits == "00") {
            disassembled_instruction = dissasemble_alu(binary_instruction);
        } else if (last_two_bits == "01") {
            disassembled_instruction = dissasemble_immediate(binary_instruction);
        } else if (last_two_bits == "10") {
            disassembled_instruction = dissasemble_branch(binary_instruction);
        } else if (last_two_bits == "11") {
            disassembled_instruction = "Unknown instruction format";
        }

        disassembled_instructions.push_back(disassembled_instruction);
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
