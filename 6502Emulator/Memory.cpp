#include "Memory.h"

void  Memory::Initialize() {
	for (size_t i = 0; i < MAX_MEM; i++)
	{
		Data[i] = 0;
	}
}

Byte* Memory::GetMem() {
	return Data;
}

void Memory::WriteWord(Word data, u32 addr, u32& cycles) {
	Data[addr] = data & 0xFF;
	Data[addr + 1] = (data >> 8);
	cycles--;
}