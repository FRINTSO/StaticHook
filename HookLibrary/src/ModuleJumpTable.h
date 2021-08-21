#ifndef STATICHOOK_MODULEJUMPTABLE_H_
#define STATICHOOK_MODULEJUMPTABLE_H_

#include <Windows.h>

namespace HookLibrary {
	namespace HookUtils {
		namespace Memory {

			class AbsoluteFarJmp {
				BYTE opcode[2]{ 0xFF, 0x25 };
				BYTE absoluteAddressSpecifier[4]{0x0, 0x0, 0x0, 0x0};
				BYTE absoluteMemoryAddress[8]{ 0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0 };
			public:
			}; // size: 0x14

			class ModuleJumpTable {
			public:
				ModuleJumpTable
			};

		} // namespace Memory
	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_MODULEJUMPTABLE_H_