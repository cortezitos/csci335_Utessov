#include "BittyEmulator.h"

BittyEmulator::BittyEmulator() : registers_(8, 0) {

} 

uint16_t BittyEmulator::Evaluate(uint16_t instruction) {
    uint16_t Rx = (instruction >> 13) & 0x07; 
    uint16_t ALU_sel = (instruction >> 2) & 0x07; 
    uint16_t format = instruction & 0x03;  

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
