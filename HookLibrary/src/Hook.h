#ifndef STATICHOOK_HOOK_H_
#define STATICHOOK_HOOK_H_

#include "DataTypes.h"

namespace HookLibrary {
	namespace HookUtils {


		struct Hook {
			bool bStatus{ false };

			BYTE* src{ nullptr };
			BYTE* dst{ nullptr };
			BYTE* PtrToGatewayFnPtr{ nullptr };
			DWORD length{ 0 };

			BYTE originalBytes[10]{ 0 };

			Hook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, DWORD length);
			Hook(const char* exportName, const char* moduleName, BYTE* dst, BYTE* PtrToGatewayFnPtr, DWORD length);

			void Enable();
			void Disable();
			void Toggle();
		};

	} // namespace HookUtils
} // namespace HookLibrary
#endif // !STATICHOOK_HOOK_H_
