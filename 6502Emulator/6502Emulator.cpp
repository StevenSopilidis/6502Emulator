#include <iostream>
#include "Cpu.h";
#include "Memory.h";
#include "Instructions.h"; 

int main()
{
	auto mem = new Memory();
	auto cpu = new Cpu(mem);
	mem->SetMem(Instructions::LDX_ABS, 0xFFFC);
	mem->SetMem(0x40, 0xFFFD);
	mem->SetMem(0x41, 0xFFFE); // 0x4140
	mem->SetMem(0x12, 0x4140);
	auto executedCycles = cpu->Execute(4);
	std::cout << cpu->GetXRegistersContent()  << std::endl;
}