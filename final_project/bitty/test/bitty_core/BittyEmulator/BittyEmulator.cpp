#include "BittyEmulator.h"

BittyEmulator::BittyEmulator() : registers_(8, 0), memory_(256, 0), pc_(0) {
    std::ifstream file("instructions.mem");
    std::string line;
    uint16_t address = 0;
    while (std::getline(file, line)) {
        memory_[address++] = std::stoul(line, nullptr, 16);
    }

    pc_ = 0;
} 

uint16_t BittyEmulator::Evaluate() {
    uint16_t instruction = memory_[pc_];
    pc_++;
    uint16_t format = instruction & 0x03;

    if (format == 0b10) {
        uint16_t immediate = (instruction >> 4) & 0x0FFF;  
        uint16_t condition = (instruction >> 2) & 0x03;    
        
        uint16_t comp_result = prev_result_;
        
        bool should_branch = false;
        switch (condition) {
            case 0b00:  // BIE 
                should_branch = (comp_result == 0);
                break;
            case 0b01:  // BIG 
                should_branch = (comp_result == 1);
                break;
            case 0b10:  // BIL 
                should_branch = (comp_result == 2);
                break;
        }

        if (should_branch) {
            pc_ = immediate;
        }
        
        return pc_;
    }

    uint16_t Rx = (instruction >> 13) & 0x07;
    uint16_t ALU_sel = (instruction >> 2) & 0x07;

    uint16_t value_x = registers_[Rx];
    uint16_t value_y = 0;

    if (format == 0b00) {
        uint16_t Ry = (instruction >> 10) & 0x07;
        value_y = registers_[Ry];
    } else if (format == 0b01) {
        value_y = (instruction >> 5) & 0xFF; 
    }

    uint16_t result = 0;

    switch (ALU_sel) {
        case 0b000: // add
            result = value_x + value_y;
            break;
        case 0b001: // sub
            result = value_x - value_y;
            break;
        case 0b010: // and
            result = value_x & value_y;
            break;
        case 0b011: // or
            result = value_x | value_y;
            break;
        case 0b100: // xor
            result = value_x ^ value_y;
            break;
        case 0b101: // shl
            if (value_y >= 16) {
                result = 0;
            } else {
                result = value_x << value_y;
            }
            break;
        case 0b110: // shr
            if (value_y >= 16){
                result = 0;
            } else {
                result = value_x >> value_y;
            }
            break;
        case 0b111: // cmp
            if (value_x == value_y)
                result = 0;
            else if (value_x > value_y)
                result = 1;
            else
                result = 2;
            break;
        default:
            std::cerr << "Invalid ALU operation" << std::endl;
            return 0;
    }

    registers_[Rx] = result;
    prev_result_ = result;
    return result;
}

uint16_t BittyEmulator::GetRegisterValue(uint16_t reg_num) {
    if (reg_num < registers_.size()) {
        return registers_[reg_num];
    } else {
        std::cerr << "Invalid register number" << std::endl;
        return 0;
    }
}

void BittyEmulator::SetRegisterValue(uint16_t reg_num, uint16_t value) {
    if (reg_num < registers_.size()) {
        registers_[reg_num] = value;
    }
}
