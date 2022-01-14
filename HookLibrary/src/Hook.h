#ifndef STATICHOOK_HOOK_H_
#define STATICHOOK_HOOK_H_

#include <Windows.h>

#include "DataTypes.h"

namespace HookLibrary {
	namespace HookUtils {


		struct Hook {
			bool bStatus{ false };

			BYTE* src{ nullptr };
			BYTE* dst{ nullptr };
			BYTE* PtrToGatewayFnPtr{ nullptr };
			SIZE_T length{ 0 };

			BYTE originalBytes[10]{ 0 };

			Hook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, SIZE_T length);
			Hook(PCSTR exportName, PCSTR moduleName, BYTE* dst, BYTE* PtrToGatewayFnPtr, SIZE_T length);

			void Enable();
			void Disable();
			void Toggle();
		};

	} // namespace HookUtils
} // namespace HookLibrary
#endif // !STATICHOOK_HOOK_H_
