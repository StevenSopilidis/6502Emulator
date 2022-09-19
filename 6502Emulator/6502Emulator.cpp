#include <iostream>
#include "Cpu.h";
#include "Memory.h";
#include "Instructions.h"; 

int main()
{
	auto mem = new Memory();
	auto cpu = new Cpu(mem);
	// start of test instruction
	mem->SetMem(Instructions::LDA_IM, 0xFFFC);
	mem->SetMem(0x42, 0xFFFD);
	// end of test instruction
	cpu->Execute(2);
}