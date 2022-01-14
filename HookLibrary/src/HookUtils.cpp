#include "HookUtils.h"

#include "proc.h"

namespace HookLibrary  {
	namespace HookUtils  {
		namespace Memory {

			VOID Patch(BYTE* dst, BYTE* src, SIZE_T size) {
				DWORD currentProtection;
				VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &currentProtection);

				memcpy(dst, src, size);
				VirtualProtect(dst, size, currentProtection, &currentProtection);
			}

			VOID PatchEx(BYTE* dst, BYTE* src, SIZE_T size, HANDLE hProcess) {
				DWORD currentProtection;
				VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &currentProtection);
				WriteProcessMemory(hProcess, dst, src, size, nullptr);
				VirtualProtectEx(hProcess, dst, size, currentProtection, &currentProtection);
			}

			VOID Nop(BYTE* dst, SIZE_T size) {
				DWORD currentProtection;
				VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &currentProtection);
				memset(dst, 0x90, size);
				VirtualProtect(dst, size, currentProtection, &currentProtection);
			}

			VOID NopEx(BYTE* dst, SIZE_T size, HANDLE hProcess) {
				BYTE* nopArray = new BYTE[size];
				memset(nopArray, 0x90, size);

				PatchEx(dst, nopArray, size, hProcess);
				delete[] nopArray;
			}

			ULONG_PTR FindDMAAddy(ULONG_PTR ptr, std::vector<DWORD> offsets) {
				ULONG_PTR address = ptr;
				for (DWORD i = 0; i < offsets.size(); i++) {
					address = *(ULONG_PTR*)address;
					address += offsets[i];
				}
				return address;
			}


			BOOL Detour32(BYTE* src, BYTE* dst, CONST SIZE_T length) {
				if (length < 5) return FALSE;
				
				DWORD currentProtection;
				VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

				ULONG_PTR relativeAddress = dst - src - 5;

				*src = 0xE9;
				*(ULONG_PTR*)(src + 1) = relativeAddress;

				VirtualProtect(src, length, currentProtection, &currentProtection);
				return TRUE;
			}

			BYTE* TrampHook32(BYTE* src, BYTE* dst, CONST SIZE_T length) {
				if (length < 5) return 0;

				BYTE* gateway = (BYTE*)VirtualAlloc(0, length, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

				memcpy_s(gateway, length, src, length);

				ULONG_PTR gatewayRelativeAddress = src - gateway - 5;
				
				*(gateway + length) = 0xE9;

				*(ULONG_PTR*)((ULONG_PTR)gateway + length + 1) = gatewayRelativeAddress;

				Detour32(src, dst, length);

				return gateway;
			}

		} // namespace Memory
	} // namespace HookUtils
} // namespace HookLibrary