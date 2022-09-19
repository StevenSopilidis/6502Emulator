#include <iostream>
#include "Cpu.h";
#include "Memory.h";
#include "Instructions.h"; 

int main()
{
	auto mem = new Memory();
	auto cpu = new Cpu(mem);
	cpu->Execute(2);
}