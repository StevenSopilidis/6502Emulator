#pragma once
#include "Memory.h"
#include "Instructions.h"

class Cpu
{
private:
    //memory to use to execute instrutions
    Memory* mem;

    Word PC; // program counter
    Byte SP; // stack  pointer

    // CPU registers
    Byte A, X, Y;

    // Bit fields for cpu flags
    Byte C : 1; // carry flag
    Byte Z : 1; // zero flag
    Byte I : 1; // interupt disabled
    Byte D : 1; // decimal mode
    Byte B : 1; // break command
    Byte V : 1; // overflow flag
    Byte N : 1; // negative flag
    void Reset();
    // decrements program counter
    // fetches byte based on pc
    Byte FetchByte(u32& cycles);
    // does not decrements program counter
    Byte ReadByte(Byte& addr,u32& cycles);
    void SetLDAStatus(Byte& value);
    Byte Add(Byte& value1, Byte& value2, u32& cycles);
    Word FetchWord(u32& cycles);

public:
    Cpu(Memory* mem);
    /// <summary>
    /// Method for execetuting an instruction
    /// </summary>
    /// <param name="cycles">Number of clock cycles to execute instruction</param>
    /// <param name="mem">mem to access data from </param>
    void Execute(u32 cycles);
};

