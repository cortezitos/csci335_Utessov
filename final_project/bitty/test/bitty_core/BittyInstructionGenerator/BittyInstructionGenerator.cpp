#include "BittyInstructionGenerator.h"

BittyInstructionGenerator::BittyInstructionGenerator() {
}

uint16_t BittyInstructionGenerator::Generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist1(0, 7);  
    std::uniform_int_distribution<> dist2(0, 7); 
    std::uniform_int_distribution<> dist3(0, 7); 
    std::uniform_int_distribution<> dist4(0, 255);  
    std::uniform_int_distribution<> format_dist(0, 2);  
    std::uniform_int_distribution<> branch_cond(0, 2);  
    std::uniform_int_distribution<> branch_addr(0, 255);  

    uint16_t instruction = 0;
    uint16_t format = format_dist(gen);

    if (format == 0 || format == 1) {
        instruction |= (dist1(gen) << 13);  

        if (format == 0) {
            instruction |= (dist2(gen) << 10);  
        } else {
            instruction |= (dist4(gen) << 5);  
        }

        instruction |= (dist3(gen) << 2);  
        instruction |= format;  
    }
    // i hate this
    
    // if (format == 2) {
    //     instruction |= (branch_addr(gen) << 4);  
    //     instruction |= (branch_cond(gen) << 2);  
    //     instruction |= 0b10;  
    // } 

    return instruction;
}
