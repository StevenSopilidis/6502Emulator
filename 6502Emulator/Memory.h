#pragma once
#include <stdexcept>

typedef unsigned char Byte;
typedef unsigned short Word;
typedef unsigned int u32;
typedef int s32;

class Memory
{
private:
	static constexpr u32 MAX_MEM = 1024 * 64;
	Byte* Data = new Byte[MAX_MEM];
public:
	Byte* GetMem();
	void Initialize();
	Byte operator[](u32 offset) const {
		if (offset > MAX_MEM || offset < 0)
			throw std::invalid_argument("offset must be between 0 and " + MAX_MEM);
		return Data[offset];
	}
	void SetMem(Byte data, u32 location);
	void WriteWord(Word data, u32 addr, s32& cycles);
};

