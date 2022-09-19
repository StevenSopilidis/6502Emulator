#include <iostream>
#include "Cpu.h"

Cpu::Cpu(Memory* mem) {
	this->mem = mem;
	this->Reset();
}

void Cpu::Reset() {
	PC = 0xFFFC;
	SP = 0x0100;
	C = Z = I = D = B = V = N = 0;
	A = X = Y = 0;
	mem->Initialize();
}

Byte Cpu::FetchByte(u32& cycles) {
	Byte data = (*mem)[PC];
	this->PC++;
	cycles--;
	return data;
}

void Cpu::Execute(u32 cycles) {
	while (cycles > 0)
	{
		auto instruction = FetchByte(cycles);
		switch (instruction)
		{
			case Instructions::LDA_IM: {
				// in LDA_IM the next byte after the instruction is the value to load
				auto value = FetchByte(cycles);
				A = value;
				Z = (A == 0); // set zero flag
				N = (A & 0b01000000) > 0; // set N if bit 7 of A is set
				break;
			}
			default: {
				std::cout << "Instruction not handled" << instruction << std::endl;
				break;
			}
		}
	}
}