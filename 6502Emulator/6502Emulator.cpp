#include <iostream>
#include "Cpu.h";
#include "Memory.h";
#include "Instructions.h"; 

int main()
{
	auto mem = new Memory();
	auto cpu = new Cpu(mem);
	cpu->SetARegistersContent(100);
	mem->SetMem(0xAA, 0xFFFC);
	cpu->Execute(2);
	std::cout << cpu->GetXRegistersContent()  << std::endl;
}