#include <iostream>
#include "Cpu.h"

Cpu::Cpu(Memory* mem) {
	this->mem = mem;
	this->Reset();
}

Cpu::Cpu() {}

void Cpu::Reset() {
	PC = 0xFFFC;
	SP = 0x0100;
	C = Z = I = D = B = V = N = 0;
	A = X = Y = 0;
	mem->Initialize();
}

Byte Cpu::Add(Byte& value1, Byte& value2, s32& cycles) {
	auto result = value1 + value2;
	cycles--;
	return result;
}

void Cpu::And(Byte value) {
	A &= value;
	SetLogicalOperationsStatus(value);
}

void Cpu::OR(Byte value) {
	A |= value;
	SetLogicalOperationsStatus(value);
}

void Cpu::EOR(Byte value) {
	A ^= value;
	SetLogicalOperationsStatus(value);
}

void Cpu::SetLDAStatus(Byte value) {
	A = value;
	Z = (A == 0); // set zero flag
	N = (A & 0b01000000) > 0; // set N if bit 7 of A is set
}

void  Cpu::SetLDXStatus(Byte value) {
	X = value;
	Z = (A == 0); // set zero flag
	N = (A & 0b01000000) > 0; // set N if bit 7 of A is set
}

void  Cpu::SetLDYStatus(Byte value) {
	Y  = value;
	Z = (A == 0); // set zero flag
	N = (A & 0b01000000) > 0; // set N if bit 7 of A is set
}

void Cpu::SetTransferOperationStatus(Byte value) {
	Z = (value == 0);
	N = (A & 0b01000000) > 0;
}

void Cpu::SetPullStackStatus(Byte value) {
	SetTransferOperationStatus(value); // save status set
}

void Cpu::SetLogicalOperationsStatus(Byte value) {
	SetLDXStatus(value); // same bits set
}

Byte Cpu::FetchByte(s32& cycles) {
	Byte data = (*this->mem)[PC];
	this->PC++;
	cycles--;
	return data;
}

Word Cpu::FetchWord(s32& cycles) {
	// 6502 is little endian
	Word data = (*this->mem)[PC++]; // low byte
	data |= ((*this->mem)[PC++] << 8); // high byte
	cycles-=2;
	return data;
}

Byte Cpu::ReadByte(Word addr,s32& cycles) {
	Byte data = (*this->mem)[addr];
	cycles--;
	return data;
}

Word Cpu::ReadWord(Word addr, s32& cycles) {
	auto loByte = ReadByte(addr, cycles);
	auto hiByte = ReadByte(addr + 1, cycles);
	return loByte | (hiByte << 8);
}

Byte Cpu::GetARegistersContent() {
	return A;
}

Byte Cpu::GetXRegistersContent() {
	return X;
}

Byte Cpu::GetYRegisterContent() {
	return Y;
}

void Cpu::SetARegistersContent(Byte value) {
	A = value;
}

void Cpu::SetXRegistersContent(Byte value) {
	X = value;
}

void Cpu::SetYRegistersContent(Byte value) {
	Y = value;
}

void Cpu::PageCrossed(Word startingAddr, Word finalAddr, s32& cycles) {
	if (finalAddr - startingAddr >= 255)
		cycles--;
}

s32 Cpu::Execute(s32 cycles) {
	auto cyclesPassed = cycles;
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
			} case Instructions::LDA_ZP: {
				// in LDA_ZP the next byte is the address of mem from which we are gonna fetch the data
				auto addr = FetchByte(cycles);
				auto value = ReadByte(addr, cycles);
				SetLDAStatus(value);
				break;
			} case Instructions::LDA_ZP_X: {
				auto addr = FetchByte(cycles);
				addr = Add(X, addr, cycles);
				auto value = ReadByte(addr, cycles);
				SetLDAStatus(value);
				break;
			} case Instructions::JSR: {
				auto subroutinAddr = FetchWord(cycles);
				this->mem->WriteWord(SP, PC - 1, cycles);
				SP++;
				PC = subroutinAddr;
				cycles--;
				break;
			} case Instructions::LDA_ABS: {
				auto addr = FetchWord(cycles);
				auto data = ReadByte(addr, cycles);
				SetLDAStatus(data);
			} case Instructions::LDA_ABS_X: {
				auto addr = FetchWord(cycles);
				auto finalAddr = addr + X;
				PageCrossed(addr, finalAddr, cycles);
				auto data = ReadByte(finalAddr, cycles);
				SetLDAStatus(data);
			} case Instructions::LDA_ABS_Y: {
				auto addr = FetchWord(cycles);
				auto finalAddr = addr + Y;
				PageCrossed(addr, finalAddr, cycles);
				auto data = ReadByte(finalAddr, cycles);
				SetLDAStatus(data);
			} case Instructions::LDA_IND_X: {
				auto addr = FetchByte(cycles);
				addr = Add(X, addr, cycles);
				Word finalAddr = ReadWord(addr, cycles);
				auto data = ReadByte(finalAddr, cycles);
				SetLDAStatus(data);
			} case Instructions::LDA_IND_Y: {
				auto addr = FetchByte(cycles);
				PageCrossed(addr, addr + Y, cycles);
				addr = addr + Y;
				Word finalAddr = ReadWord(addr, cycles);
				auto data = ReadByte(finalAddr, cycles);
				SetLDAStatus(data);
			} case Instructions::LDX_IM: {
				auto value = FetchByte(cycles);
				SetLDXStatus(value);
				break;
			} case Instructions::LDX_ZP: {
				auto addr = FetchByte(cycles);
				auto value = ReadByte(addr, cycles);
				SetLDXStatus(value);
				break;
			} case Instructions::LDX_ZP_Y: {
				auto addr = FetchByte(cycles);
				addr = Add(addr, Y, cycles);
				auto value = ReadByte(addr, cycles);
				SetLDXStatus(value);
			} case Instructions::LDX_ABS: {
				auto addr = FetchWord(cycles);
				auto value = ReadByte(addr, cycles);
				SetLDXStatus(value);
				break;
			} case Instructions::LDX_ABS_Y: {
				auto addr = FetchWord(cycles);
				PageCrossed(addr, addr + Y, cycles);
				addr += Y;
				auto value = ReadByte(addr, cycles);
				SetLDXStatus(value);
				break;
			} case Instructions::LDY_IM: {
				auto value = FetchByte(cycles);
				SetLDYStatus(value);
				break;
			} case Instructions::LDY_ZP: {
				auto addr = FetchByte(cycles);
				auto value = ReadByte(addr, cycles);
				SetLDYStatus(value);
				break;
			} case Instructions::LDY_ZP_X: {
				auto addr = FetchByte(cycles);
				addr = Add(addr, X, cycles);
				auto value = ReadByte(addr, cycles);
				SetLDYStatus(value);
			} case Instructions::LDY_ABS: {
				auto addr = FetchWord(cycles);
				auto value = ReadByte(addr, cycles);
				SetLDYStatus(value);
				break;
			} case Instructions::LDY_ABS_X: {
				auto addr = FetchWord(cycles);
				PageCrossed(addr, addr + X, cycles);
				addr += Y;
				auto value = ReadByte(addr, cycles);
				SetLDYStatus(value);
				break;
			} case Instructions::TAX: {
				auto value = A;
				X = value;
				cycles--;
				SetTransferOperationStatus(value);
				break;
			} case Instructions::TAY: {
				auto value = A;
				Y = value;
				cycles--;
				SetTransferOperationStatus(value);
				break;
			} case Instructions::TXA: {
				auto value = X;
				A = value;
				cycles--;
				SetTransferOperationStatus(value);
				break;
			} case Instructions::TYA: {
				auto value = Y;
				A = value;
				cycles--;
				SetTransferOperationStatus(value);
				break;
			} case Instructions::TSX: {
				auto value = SP;
				X = value;
				cycles--;
				SetTransferOperationStatus(value);
				break;
			} case Instructions::TXS: {
				auto value = X;
				SP = value;
				cycles--;
				SetTransferOperationStatus(value);
				break;
			} case Instructions::PHA: {
				auto value = A;
				cycles--;
				mem->SetMem(value, SP);
				SP++;
				cycles--;
				break;
			} case Instructions::PHP: {
				Byte value = 0;
				// construct status register from bit fields
				value = value | C;
				value = value | (Z << 2);
				value = value | (I << 3);
				value = value | (D << 4);
				value = value | (B << 5);
				value = value | (V << 6);
				value = value | (N << 7);
				cycles--;
				mem->SetMem(value, SP);
				SP++;
				cycles--;
				break;
			} case Instructions::PLA: {
				auto value = ReadByte(SP, cycles);
				SP--;
				A = value;
				cycles--;
				SetPullStackStatus(value);
				break;
			} case Instructions::PLP: {
				// TODO
				break;
			} case Instructions::AND_IMM: {
				And(FetchByte(cycles));
				break;
			} case Instructions::AND_ZP: {
				auto addr = FetchByte(cycles);
				And(ReadByte(addr, cycles));
				break;
			} case Instructions::AND_ZP_X: {
				auto addr = FetchByte(cycles);
				auto value = ReadByte(addr, cycles);
				value = Add(addr, value, cycles);
				And(value);
				break;
			} case Instructions::AND_ABS: {
				auto addr = FetchWord(cycles);
				And(ReadByte(addr, cycles));
				break;
			} case Instructions::AND_ABS_X: {
				auto addr = FetchWord(cycles);
				PageCrossed(addr, addr + X, cycles);
				addr = addr + X;
				And(ReadByte(addr, cycles));
				break;
			} case Instructions::AND_ABS_Y: {
				auto addr = FetchWord(cycles);
				PageCrossed(addr, addr + Y, cycles);
				addr = addr + Y;
				And(ReadByte(addr, cycles));
				break;
			} case Instructions::AND_IND_X: {
				auto addr = FetchByte(cycles);
				addr = Add(addr, X, cycles);
				auto finalAddr = ReadWord(addr, cycles);
				auto value = ReadByte(finalAddr, cycles);
				And(value);
				break;
			} case  Instructions::AND_IND_Y: {
				auto addr = FetchByte(cycles);
				PageCrossed(addr, addr + Y, cycles);
				addr += Y;
				auto finalAddr = ReadWord(addr, cycles);
				auto value = ReadByte(finalAddr, cycles);
				And(value);
				break;
			} case Instructions::ORA_IMM: {
				OR(FetchByte(cycles));
				break;
			} case Instructions::ORA_ZP: {
				auto addr = FetchByte(cycles);
				OR(ReadByte(addr, cycles));
				break;
			} case Instructions::ORA_ZP_X: {
				auto addr = FetchByte(cycles);
				auto value = ReadByte(addr, cycles);
				value = Add(addr, value, cycles);
				OR(value);
				break;
			} case Instructions::ORA_ABS: {
				auto addr = FetchWord(cycles);
				OR(ReadByte(addr, cycles));
				break;
			} case Instructions::ORA_ABS_X: {
				auto addr = FetchWord(cycles);
				PageCrossed(addr, addr + X, cycles);
				addr = addr + X;
				OR(ReadByte(addr, cycles));
				break;
			} case Instructions::ORA_ABS_Y: {
				auto addr = FetchWord(cycles);
				PageCrossed(addr, addr + Y, cycles);
				addr = addr + Y;
				OR(ReadByte(addr, cycles));
				break;
			} case Instructions::ORA_IND_X: {
				auto addr = FetchByte(cycles);
				addr = Add(addr, X, cycles);
				auto finalAddr = ReadWord(addr, cycles);
				auto value = ReadByte(finalAddr, cycles);
				OR(value);
				break;
			} case  Instructions::ORA_IND_Y: {
				auto addr = FetchByte(cycles);
				PageCrossed(addr, addr + Y, cycles);
				addr += Y;
				auto finalAddr = ReadWord(addr, cycles);
				auto value = ReadByte(finalAddr, cycles);
				OR(value);
				break;
			} case Instructions::EOR_IMM: {
				EOR(FetchByte(cycles));
				break;
			} case Instructions::EOR_ZP: {
				auto addr = FetchByte(cycles);
				EOR(ReadByte(addr, cycles));
				break;
			} case Instructions::EOR_ZP_X: {
				auto addr = FetchByte(cycles);
				auto value = ReadByte(addr, cycles);
				value = Add(addr, value, cycles);
				EOR(value);
				break;
			} case Instructions::EOR_ABS: {
				auto addr = FetchWord(cycles);
				EOR(ReadByte(addr, cycles));
				break;
			} case Instructions::EOR_ABS_X: {
				auto addr = FetchWord(cycles);
				PageCrossed(addr, addr + X, cycles);
				addr = addr + X;
				EOR(ReadByte(addr, cycles));
				break;
			} case Instructions::EOR_ABS_Y: {
				auto addr = FetchWord(cycles);
				PageCrossed(addr, addr + Y, cycles);
				addr = addr + Y;
				EOR(ReadByte(addr, cycles));
				break;
			} case Instructions::EOR_IND_X: {
				auto addr = FetchByte(cycles);
				addr = Add(addr, X, cycles);
				auto finalAddr = ReadWord(addr, cycles);
				auto value = ReadByte(finalAddr, cycles);
				EOR(value);
				break;
			} case  Instructions::EOR_IND_Y: {
				auto addr = FetchByte(cycles);
				PageCrossed(addr, addr + Y, cycles);
				addr += Y;
				auto finalAddr = ReadWord(addr, cycles);
				auto value = ReadByte(finalAddr, cycles);
				EOR(value);
				break;
			}
			default: {
				std::cout << "Instruction not handled" << instruction << std::endl;
				cycles--; 
				break;
			}
		}
	}
	return cyclesPassed - cycles;
}