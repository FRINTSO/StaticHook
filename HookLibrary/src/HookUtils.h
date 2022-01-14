#ifndef STATICHOOK_HOOKUTILS_H_
#define STATICHOOK_HOOKUTILS_H_

#include <windows.h>

#include <vector>

#include "DataTypes.h"

namespace HookLibrary {
	namespace HookUtils {
		namespace Memory {

			VOID Patch(BYTE* dst, BYTE* src, SIZE_T size);
			VOID PatchEx(BYTE* dst, BYTE* src, SIZE_T size, HANDLE hProcess);
			VOID Nop(BYTE* dst, SIZE_T size);
			VOID NopEx(BYTE* dst, SIZE_T size, HANDLE hProcess);
			ULONG_PTR FindDMAAddy(ULONG_PTR ptr, std::vector<DWORD> offsets);

			BOOL Detour32(BYTE* src, BYTE* dst, CONST SIZE_T length);
			BYTE* TrampHook32(BYTE* src, BYTE* dst, CONST SIZE_T length);

		} // namespace Memory
	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_HOOKUTILS_H_
