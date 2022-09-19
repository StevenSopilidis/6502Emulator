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