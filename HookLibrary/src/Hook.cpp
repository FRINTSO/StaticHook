#include "Hook.h"

#include <Windows.h>

#include "HookUtils.h"

namespace HookLibrary {
	namespace HookUtils {

		Hook::Hook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, DWORD length) {
			this->src = src;
			this->dst = dst;
			this->length = length;
			this->PtrToGatewayFnPtr = PtrToGatewayFnPtr;
		}

		Hook::Hook(const char* exportName, const char* moduleName, BYTE* dst, BYTE* PtrToGatewayFnPtr, DWORD length) {
			HMODULE hModule = GetModuleHandleA(moduleName);

			this->src = (BYTE*)GetProcAddress(hModule, exportName);
			this->dst = dst;
			this->length = length;
			this->PtrToGatewayFnPtr = PtrToGatewayFnPtr;
		}

		void Hook::Enable() {
			memcpy(originalBytes, src, length);
			*(uintptr_t*)PtrToGatewayFnPtr = (uintptr_t)TrampHook32(src, dst, length);
			bStatus = true;
		}

		void Hook::Disable() {
			Patch(src, originalBytes, length);
			bStatus = false;
		}

		void Hook::Toggle() {
			if (!bStatus) Enable();
			else Disable();
		}

	} // namespace HookUtils
} // namespace HookLibrary