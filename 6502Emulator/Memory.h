#pragma once
#include <stdexcept>

typedef unsigned char Byte;
typedef unsigned short Word;
typedef unsigned int u32;

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
		return this->Data[offset];
	}
	void SetMem(Byte data, u32 location)
	{
		if (location > MAX_MEM || location < 0)
			throw std::invalid_argument("location must be between 0 and " + MAX_MEM);
		Data[location] = data;
	}
	void WriteWord(Word data, u32 addr, u32& cycles);
};

