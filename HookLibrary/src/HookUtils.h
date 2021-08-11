#ifndef STATICHOOK_HOOKUTILS_H_
#define STATICHOOK_HOOKUTILS_H_

#include <windows.h>

#include <vector>

#include "DataTypes.h"

namespace HookLibrary {
	namespace HookUtils {

		void Patch(BYTE* dst, BYTE* src, DWORD size);
		void PatchEx(BYTE* dst, BYTE* src, DWORD size, HANDLE hProcess);
		void Nop(BYTE* dst, DWORD size);
		void NopEx(BYTE* dst, DWORD size, HANDLE hProcess);
		uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<DWORD> offsets);

		bool Detour32(BYTE* src, BYTE* dst, const DWORD length);
		BYTE* TrampHook32(BYTE* src, BYTE* dst, const DWORD length);

			BYTE* HookAllocator();

		} // namespace Memory
	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_HOOKUTILS_H_
