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
    Byte FetchByte(s32& cycles);
    // does not decrements program counter
    Byte ReadByte(Word addr, s32& cycles);
    // does not decrements program counter
    Word ReadWord(Word addr, s32& cycles);
    void SetLDAStatus(Byte value);
    void SetLDXStatus(Byte value);
    void SetLDYStatus(Byte value);
    void SetLogicalOperationsStatus(Byte value);
    /// <summary>
    /// operation for activating the correct flags when
    /// executing transfer operations
    /// </summary>
    /// <param name="value">Value that we transfered </param>
    void SetTransferOperationStatus(Byte value);
    void SetPullStackStatus(Byte value);
    Byte Add(Byte& value1, Byte& value2, s32& cycles);
    /// <summary>
    /// logical and between value and accumulator
    /// </summary>
    /// <param name="value">value to perform and with</param>
    void And(Byte value);
    /// <summary>
    /// logical or between value and accumulator
    /// </summary>
    /// <param name="value">value to perform or with</param>
    void OR(Byte value);
    /// <summary>
    /// exclusive or between value and accumulator
    /// </summary>
    /// <param name="value">value to perform eor with</param>
    void EOR(Byte value);
    Word FetchWord(s32& cycles);

public:
    Cpu(Memory* mem);
    Cpu();
    /// <summary>
    /// method for executing commands
    /// </summary>
    /// <param name="cycles">Number of cycles to execute</param>
    /// <returns> the number of cycles remaining </returns>
    s32 Execute(s32 cycles);
    Byte GetARegistersContent();
    Byte GetXRegistersContent();
    Byte GetYRegisterContent();
    void  SetARegistersContent(Byte value);
    void  SetXRegistersContent(Byte value);
    void  SetYRegistersContent(Byte value);
    /// <summary>
    /// method for checking if page crossed, and if so remove one cycle
    /// </summary>
    /// <param name="startingAddr">Starting Address</param>
    /// <param name="finalAddr">final addr after addition </param>
    /// <param name="cycles">number of cycles remainign </param>
    void PageCrossed(Word startingAddr, Word finalAddr, s32& cycles);

};

