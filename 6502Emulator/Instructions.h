#pragma once
#include "Memory.h"

/// <summary>
/// class for representingn instructions
/// </summary>
class Instructions {
public:
	// lda in immediate mode instruction
	static constexpr Byte LDA_IM = 0xA9;
	// lda in zero page mode instructionsn
	static constexpr Byte LDA_ZP = 0xA5;
	// lda x in zero page mode instruction
	static constexpr Byte LDA_ZP_X = 0xB5;
	// JSR (jump in subroutine) instruction
	static constexpr Byte JSR = 0x20;
	// lda in absolute mode instruction
	static constexpr Byte LDA_ABS = 0xAD;
	// lda x in absolute mode instruction
	static constexpr Byte LDA_ABS_X = 0xBD;
	// lda x in absolute mode instruction
	static constexpr Byte LDA_ABS_Y = 0xB9;
	// lda x in indirect mode intruction
	static constexpr Byte LDA_IND_X = 0xA1;
	// lda y in indirect mode instructionn
	static constexpr Byte LDA_IND_Y = 0xB1;
	// ldx in immediate mode
	static constexpr Byte LDX_IM = 0xA2;
	// ldx in zero page mode
	static constexpr Byte LDX_ZP = 0xA6;
	// ldx y in zero page mode
	static constexpr Byte LDX_ZP_Y = 0xB6;
	// ldx in abs mode
	static constexpr Byte LDX_ABS = 0xAE;
	// ldx y in abs mode
	static constexpr Byte LDX_ABS_Y = 0xBE;
	// ldy in immediate mode
	static constexpr Byte LDY_IM = 0xA0;
	// ldy in zero page mode
	static constexpr Byte LDY_ZP = 0xA4;
	// ldy x in zero page mode
	static constexpr Byte LDY_ZP_X = 0xB4;
	// ldy in abs mode
	static constexpr Byte LDY_ABS = 0xAC;
	// ldy x in abs mode
	static constexpr Byte LDY_ABS_X = 0xBC;
	// tax instruction
	static constexpr Byte TAX = 0xAA;
	// tay instruction
	static constexpr Byte TAY = 0xA8;
	// txa instruction
	static constexpr Byte TXA = 0x8A;
	// tya instruction
	static constexpr Byte TYA = 0x98;
	// tsx instruction
	static constexpr Byte TSX = 0xBA;
	// txs instruction
	static constexpr Byte TXS = 0x9A;
	// pha instruction
	static constexpr Byte PHA = 0x48;
	// php instruction
	static constexpr Byte PHP = 0x08;
	// pla insturction
	static constexpr Byte PLA = 0x68;
	// plp instruction
	static constexpr Byte PLP = 0x28;
	// and in immediate mode instruction
	static constexpr Byte AND_IMM = 0x29;
	// and in zero page mode
	static constexpr Byte AND_ZP = 0x25;
	// and in zero page x mode
	static constexpr Byte AND_ZP_X = 0x35;
	// and in absolute mode
	static constexpr Byte AND_ABS = 0x2D;
	// and in zero page x mode
	static constexpr Byte AND_ABS_X = 0x3D;
	// and in zero page y mode
	static constexpr Byte AND_ABS_Y = 0x39;
	// and in indirect x mode
	static constexpr Byte AND_IND_X = 0x21;
	// and in inderect y mode
	static constexpr Byte AND_IND_Y = 0x31;
	// or in immediate mode instruction
	static constexpr Byte ORA_IMM = 0x09;
	// or in zero page mode
	static constexpr Byte ORA_ZP = 0x05;
	// or in zero page x mode
	static constexpr Byte ORA_ZP_X = 0x15;
	// or in absolute mode
	static constexpr Byte ORA_ABS = 0x0D;
	// or in zero page x mode
	static constexpr Byte ORA_ABS_X = 0x1D;
	// or in zero page y mode
	static constexpr Byte ORA_ABS_Y = 0x19;
	// or in indirect x mode
	static constexpr Byte ORA_IND_X = 0x01;
	// or in inderect y mode
	static constexpr Byte ORA_IND_Y = 0x11;
	// eor in immediate mode instruction
	static constexpr Byte EOR_IMM = 0x49;
	// eor in zero page mode
	static constexpr Byte EOR_ZP = 0x45;
	// eor in zero page x mode
	static constexpr Byte EOR_ZP_X = 0x55;
	// eor in absolute mode
	static constexpr Byte EOR_ABS = 0x4D;
	//eor in zero page x mode
	static constexpr Byte EOR_ABS_X = 0x5D;
	// eor in zero page y mode
	static constexpr Byte EOR_ABS_Y = 0x59;
	// eor in indirect x mode
	static constexpr Byte EOR_IND_X = 0x41;
	// eor in inderect y mode
	static constexpr Byte EOR_IND_Y = 0x51;
};