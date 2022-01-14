#include "Hook.h"

#include <Windows.h>

#include "HookUtils.h"

namespace HookLibrary {
	namespace HookUtils {

		Hook::Hook(BYTE* src, BYTE* dst, BYTE* PtrToGatewayFnPtr, SIZE_T length) {
			this->src = src;
			this->dst = dst;
			this->length = length;
			this->PtrToGatewayFnPtr = PtrToGatewayFnPtr;
		}

		Hook::Hook(PCSTR exportName, PCSTR moduleName, BYTE* dst, BYTE* PtrToGatewayFnPtr, SIZE_T length) {
			HMODULE hModule = GetModuleHandleA(moduleName);
			
			if (hModule == 0) {
				throw "module name could not be found";
			}

			this->src = (BYTE*)GetProcAddress(hModule, exportName);
			this->dst = dst;
			this->length = length;
			this->PtrToGatewayFnPtr = PtrToGatewayFnPtr;
		}

		void Hook::Enable() {
			memcpy(originalBytes, src, length);
			*(uintptr_t*)PtrToGatewayFnPtr = (uintptr_t)Memory::TrampHook32(src, dst, length);
			bStatus = true;
		}

		void Hook::Disable() {
			Memory::Patch(src, originalBytes, length);
			bStatus = false;
		}

		void Hook::Toggle() {
			if (!bStatus) Enable();
			else Disable();
		}

	} // namespace HookUtils
} // namespace HookLibrary