#include <cstdint>
#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <fstream>
class BittyEmulator
{
public:
	BittyEmulator();
	uint16_t Evaluate(uint16_t instruction);
	uint16_t GetRegisterValue(uint16_t reg_num);
	void SetRegisterValue(uint16_t reg_num, uint16_t value);

private:
	std::vector<uint16_t> registers_;
};
