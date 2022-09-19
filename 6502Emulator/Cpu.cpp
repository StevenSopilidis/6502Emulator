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

Byte Cpu::Add(Byte& value1, Byte& value2, u32& cycles) {
	auto result = value1 + value2;
	cycles--;
	return result;
}


void Cpu::SetLDAStatus(Byte& value) {
	A = value;
	Z = (A == 0); // set zero flag
	N = (A & 0b01000000) > 0; // set N if bit 7 of A is set
}

Byte Cpu::FetchByte(u32& cycles) {
	Byte data = (*mem)[PC];
	this->PC++;
	cycles--;
	return data;
}

Word Cpu::FetchWord(u32& cycles) {
	// 6502 is little endian
	Word data = (*mem)[PC++]; // low byte
	data |= ((*mem)[PC++] << 8); // high byte
	cycles-=2;
	return data;
}

Byte Cpu::ReadByte(Byte& addr,u32& cycles) {
	Byte data = (*mem)[addr];
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
				SetLDAStatus(value);
				break;
			}
			case Instructions::LDA_ZP: {
				// in LDA_ZP the next byte is the address of mem from which we are gonna fetch the data
				auto addr = FetchByte(cycles);
				auto value = ReadByte(addr, cycles);
				SetLDAStatus(value);
				break;
			}
			case Instructions::LDA_ZPX: {
				auto addr = FetchByte(cycles);
				addr = Add(X, addr, cycles);
				auto value = ReadByte(addr, cycles);
				SetLDAStatus(value);
				break;
			} 
			case Instructions::JSR: {
				auto subroutinAddr = FetchWord(cycles);
				mem->WriteWord(SP, PC - 1, cycles);
				SP++;
				PC = subroutinAddr;
				cycles--;
				break;
			}
			default: {
				std::cout << "Instruction not handled" << instruction << std::endl;
				break;
			}
		}
	}
}