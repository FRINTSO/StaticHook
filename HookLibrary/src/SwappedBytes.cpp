#include "SwappedBytes.h"

#include "proc.h"
#include "ModuleJumpTable.h"

namespace HookLibrary {
	namespace HookUtils {

		SwappedBytes::SwappedBytes(SwappedBytes&& other) noexcept
			: src(other.src), originalBytes(other.originalBytes), bytesSize(other.bytesSize), lpFunction(other.lpFunction) {
			other.src = NULL;
			other.originalBytes = nullptr;
			other.bytesSize = NULL;
			other.lpFunction = NULL;
		}

		SwappedBytes::~SwappedBytes() {
			this->Restore();
			src = NULL;
			delete[] originalBytes;
			originalBytes = nullptr;
			bytesSize = NULL;
			lpFunction = NULL;
		}

		bool SwappedBytes::operator==(const SwappedBytes& other) {
			return src == other.src && lpFunction == other.lpFunction && bytesSize == other.bytesSize && memcmp(originalBytes, other.originalBytes, bytesSize);
		}

		void SwappedBytes::Restore() {
			if (!this->src) return; // Source or target function is empty

			HookLibrary::HookUtils::Memory::Patch((BYTE*)this->src, (BYTE*)this->originalBytes, this->bytesSize);

			// Only detour32 can assign lpfunction, meaning if it is null this swappedbytes object was not a detour
			if (this->lpFunction == nullptr) return;

			// find jump table that hold the swapped bytes object

			DWORD dwProcessId = GetCurrentProcessId();
			ULONG_PTR baseAddress = (ULONG_PTR)GetModuleBaseOfAddress(dwProcessId, (PVOID)this->src);

			if (baseAddress == NULL) {
				throw "Base address of swappedbytes injection was NULL";
			}

			auto got = Memory::ModuleJumpTable::jumpTables.find(baseAddress);
			if (got != Memory::ModuleJumpTable::jumpTables.end()) {
				got->second.UnregisterSwappedBytes(this);
			}

			this->src = NULL;
			delete[] this->originalBytes;
			this->originalBytes = nullptr;
			this->bytesSize = NULL;
			this->lpFunction = nullptr;
		}

		SwappedBytes Detour32(BYTE* dst, LPVOID lpFunction, SIZE_T size) {
			if (size < 5) throw "Size of bytes to be replaced with a jump-instruction must be atleast 5";

			Memory::ModuleJumpTable* jumpTable = Memory::ModuleJumpTable::FetchModuleJumpTable(dst);

			if (!jumpTable) {
				return SwappedBytes();
			}
			
			SwappedBytes swappedBytes = SwappedBytes((PULONG_PTR)dst, lpFunction);
			PVOID jumpTableAddress = jumpTable->RegisterSwappedBytes(&swappedBytes);

			if (!jumpTableAddress) {
				return SwappedBytes();
			}

			// Write hook
			DWORD currentProtection;

			VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &currentProtection);
			
			ULONG_PTR relativeAddress = (ULONG_PTR)jumpTableAddress - (ULONG_PTR)dst - 5;

			*dst = 0xE9;

			*(ULONG_PTR*)(dst + 1) = relativeAddress;

			for (DWORD x = 0x5; x < size; x++)
				*(dst + x) = 0x90;

			VirtualProtect(dst, size, currentProtection, &currentProtection);

			return swappedBytes;
		}

		SwappedBytes Nop(BYTE* dst, SIZE_T size) {
			SwappedBytes swappedBytes(dst, size);
			Memory::Nop(dst, size);
			return swappedBytes;
		}

		SwappedBytes WriteBytes(BYTE* dst, LPCSTR pattern, SIZE_T size) {
			SwappedBytes swappedBytes(dst, size);
			DWORD currentProtection;

			VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &currentProtection);

			memcpy(dst, pattern, size);
			VirtualProtect(dst, size, currentProtection, &currentProtection);

			return swappedBytes;
		}

		SwappedBytes::SwappedBytes(BYTE* src, SIZE_T bytes)
			: src((ULONG_PTR)src), bytesSize(bytes), lpFunction(nullptr) {
			originalBytes = new BYTE[bytes];
			memcpy(originalBytes, src, bytes);
		}

		SwappedBytes::SwappedBytes(PULONG_PTR src, PVOID function)
			: src((ULONG_PTR)src), bytesSize(sizeof(AbsoluteFarJmp)), lpFunction(function) {
			originalBytes = new BYTE[sizeof(AbsoluteFarJmp)];
			memcpy(originalBytes, src, sizeof(AbsoluteFarJmp));
		}

	} // namespace HookUtils
} // namespace HookLibrary
