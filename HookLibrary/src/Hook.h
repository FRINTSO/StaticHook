#ifndef STATICHOOK_HOOK_H_
#define STATICHOOK_HOOK_H_

#include "DataTypes.h"

namespace HookLibrary {
	namespace HookUtils {


		struct Hook {
			BYTE* src{ nullptr }; // 0x8
			BYTE* dst{ nullptr }; // 0x8
			BYTE* PtrToGatewayFnPtr{ nullptr }; //0x8
			DWORD length{ 0 }; //0x4

			bool bStatus{ false }; //0x1
			BYTE originalBytes[11]{ 0 }; //0xB

			Hook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, DWORD length);
			Hook(const char* exportName, const char* moduleName, BYTE* dst, BYTE* PtrToGatewayFnPtr, DWORD length);

			void Enable();
			void Disable();
			void Toggle();
		};

	} // namespace HookUtils
} // namespace HookLibrary
#endif // !STATICHOOK_HOOK_H_
