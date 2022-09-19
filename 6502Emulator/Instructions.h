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
	// ldax in zero page mode instruction
	static constexpr Byte LDA_ZPX = 0xB5;
	// JSR (jump in subroutine) instruction
	static constexpr Byte JSR = 0x20;
};