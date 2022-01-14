#ifndef ABSOLUTE_FAR_JMP_H_
#define ABSOLUTE_FAR_JMP_H_

#include <Windows.h>

struct AbsoluteFarJmp {
	BYTE opcode[2]{ 0xFF, 0x25 };
	BYTE absoluteAddressSpecifier[4]{ 0x0, 0x0, 0x0, 0x0 };
	BYTE absoluteMemoryAddress[8]{ 0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0 };

	AbsoluteFarJmp() = default;
	AbsoluteFarJmp(void* memoryAddress) {
		memcpy(absoluteMemoryAddress, &memoryAddress, 0x8);
	}
}; // size: 0x14

#endif // !ABSOLUTE_FAR_JMP_H_
