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

void Memory::SetMem(Byte data, u32 location)
{
	if (location > MAX_MEM || location < 0)
		throw std::invalid_argument("location must be between 0 and " + MAX_MEM);
	Data[location] = data;
}
void Memory::WriteWord(Word data, u32 addr, s32& cycles) {
	Data[addr] = data & 0xFF;
	Data[addr + 1] = (data >> 8);
	cycles--;
}