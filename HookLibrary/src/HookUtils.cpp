#include "HookUtils.h"

#include "proc.h"

namespace HookLibrary {
	namespace HookUtils {
		namespace Memory {

			void Patch(BYTE* dst, BYTE* src, DWORD size) {
				DWORD currentProtection;
				VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &currentProtection);

				memcpy(dst, src, size);
				VirtualProtect(dst, size, currentProtection, &currentProtection);
			}

			void PatchEx(BYTE* dst, BYTE* src, DWORD size, HANDLE hProcess) {
				DWORD currentProtection;
				VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &currentProtection);
				WriteProcessMemory(hProcess, dst, src, size, nullptr);
				VirtualProtectEx(hProcess, dst, size, currentProtection, &currentProtection);
			}

			void Nop(BYTE* dst, DWORD size) {
				DWORD currentProtection;
				VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &currentProtection);
				memset(dst, 0x90, size);
				VirtualProtect(dst, size, currentProtection, &currentProtection);
			}

			void NopEx(BYTE* dst, DWORD size, HANDLE hProcess) {
				BYTE* nopArray = new BYTE[size];
				memset(nopArray, 0x90, size);

				PatchEx(dst, nopArray, size, hProcess);
				delete[] nopArray;
			}

			uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<DWORD> offsets) {
				uintptr_t address = ptr;
				for (DWORD i = 0; i < offsets.size(); i++) {
					address = *(uintptr_t*)address;
					address += offsets[i];
				}
				return address;
			}


			bool Detour32(BYTE* src, BYTE* dst, const DWORD length) {
				if (length < 5) return false;

				DWORD currentProtection;
				VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

				uintptr_t relativeAddress = (uintptr_t)(dst - src) - 5;

				*src = 0xE9;
				*(uintptr_t*)(src + 1) = relativeAddress;

				VirtualProtect(src, length, currentProtection, &currentProtection);
				return true;
			}

			BYTE* TrampHook32(BYTE* src, BYTE* dst, const DWORD length) {
				if (length < 5) return 0;

				BYTE* gateway = (BYTE*)VirtualAlloc(0, length, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

				memcpy_s(gateway, length, src, length);

				uintptr_t gatewayRelativeAddress = (uintptr_t)(src - gateway) - 5;

				*(gateway + length) = 0xE9;

				*(uintptr_t*)((uintptr_t)gateway + length + 1) = gatewayRelativeAddress;

				Detour32(src, dst, length);

				return gateway;
			}


			BYTE* HookAllocator() {

				/*
				Information about making an allocation:
				Follow Cheat Engines standard to begin with.
				Allocate below entry for targeted module

				*/

				//GetProcId(L"")

				//VirtualAllocEx()

				return 0;
			}

		} // namespace Memory
	} // namespace HookUtils
} // namespace HookLibrary