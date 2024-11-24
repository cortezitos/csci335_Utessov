#include "BittyInstructionGenerator.h"

BittyInstructionGenerator::BittyInstructionGenerator() {
}

uint16_t BittyInstructionGenerator::Generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist1(0, 7); // for 3-bit ranges
    std::uniform_int_distribution<> dist2(0, 7); // for 3-bit ranges
    std::uniform_int_distribution<> dist3(0, 7); // for 3-bit ranges
    std::uniform_int_distribution<> dist4(0, 255); // for 8-bit immediate values
    std::uniform_int_distribution<> format_dist(0, 1); // to choose between formats

    uint16_t instruction = 0;
    uint16_t format = format_dist(gen);

    instruction |= (dist1(gen) << 13); // bits 15-13 for Rx

    if (format == 0) {
        // Standard format: reg1 reg2 alu
        instruction |= (dist2(gen) << 10); // bits 12-10 for Ry
    } else {
        // Immediate format: reg1 immediate alu
        instruction |= (dist4(gen) << 5); // bits 12-5 for immediate value
    }

    instruction |= (dist3(gen) << 2);  // bits 4-2 for ALU operation
    instruction |= format; // bits 1-0 for format

    return instruction;
}
