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
	
};