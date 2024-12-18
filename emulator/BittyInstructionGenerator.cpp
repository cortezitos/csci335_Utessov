#include "BittyInstructionGenerator.h"


BittyInstructionGenerator::BittyInstructionGenerator(){
}


uint16_t BittyInstructionGenerator::Generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist1(0, 7); // for 3-bit ranges
    std::uniform_int_distribution<> dist2(0, 7); // for 3-bit ranges
    std::uniform_int_distribution<> dist3(0, 7); // for 3-bit ranges


    uint16_t instruction = 0;
    instruction |= (dist1(gen) << 13); // bits 15-13
    instruction |= (dist2(gen) << 10); // bits 12-10
    instruction |= (dist3(gen) << 2);  // bits 4-2

    return instruction;
}

int main() {
    std::cout << "how many instructions do you want to generate?" << std::endl;
    int numInstructions;
    std::cin >> numInstructions;

    BittyInstructionGenerator generator;

    std::ofstream outFile("instructions.mem");
    for (int i = 0; i < numInstructions; ++i) {
        uint16_t instruction = generator.Generate();
        outFile << std::hex << instruction << std::endl;
    }
    outFile.close();
}
