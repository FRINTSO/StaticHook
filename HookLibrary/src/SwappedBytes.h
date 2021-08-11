#ifndef STATICHOOK_SWAPPEDBYTES_H_
#define STATICHOOK_SWAPPEDBYTES_H_

#include "DataTypes.h"

namespace HookLibrary {
	namespace HookUtils {

		template<DWORD S>
		class SwappedBytes {
		public:
			SwappedBytes(SwappedBytes&& other) noexcept
				: src(other.src) {
				memcpy(originalBytes, other.originalBytes, S);
				other.src = nullptr;
			}
			~SwappedBytes() {
				src = nullptr;
			}

			void Restore() {
				Memory::Patch(src, originalBytes, S);
			}

			template<DWORD S1> friend SwappedBytes<S1> Detour(BYTE* dst, BYTE* function);
			template<DWORD S1> friend SwappedBytes<S1> TrampHook(BYTE* src, BYTE* dst);
			template<DWORD S1> friend SwappedBytes<S1> WriteBytes(BYTE* dst, const char* bytes);
			template<DWORD S1> friend SwappedBytes<S1> Nop(BYTE* dst);
		private:
			SwappedBytes() = default;
			SwappedBytes(BYTE* src)
				: src(src) {
				memcpy(originalBytes, src, S);
			}
			SwappedBytes(const SwappedBytes&) = delete;

			BYTE* src{ nullptr };
			BYTE originalBytes[S]{0};
		};

#ifdef _WIN64
		template<DWORD S>
		SwappedBytes<S> Detour(BYTE* dst, BYTE* function) {
			if (S < 14) {
				return SwappedBytes<S>();
			}

			SwappedBytes<S> sb(dst);

			DWORD currentProtection;

			VirtualProtect(dst, S, PAGE_EXECUTE_READWRITE, &currentProtection);

			*(HookLibrary::WORD*)dst = 0x25FF;

			memset((dst + 2), 0x0, 0x4);

			*(QWORD*)(dst + 0x6) = (QWORD)function;
			memset((dst + 14), 0x90, (S - 14));

			VirtualProtect(dst, S, currentProtection, &currentProtection);

			return sb;
		}
#else
		template<DWORD S>
		SwappedBytes<S> Detour(BYTE* dst, BYTE* function) {
			if (S < 5) {
				return SwappedBytes<S>();
			}

			SwappedBytes<S> sb(dst);

			DWORD currentProtection;

			VirtualProtect(dst, S, PAGE_EXECUTE_READWRITE, &currentProtection);

			DWORD relativeAddress = function - dst - 5;

			*dst = 0xE9;

			*(DWORD*)(dst + 1) = relativeAddress;

			for (DWORD x = 0x5; x < S; x++) {
				*(dst + x) = 0x90;
			}

			VirtualProtect(dst, S, currentProtection, &currentProtection);

			return sb;
		}
#endif

#ifdef _WIN64
		template<DWORD S>
		SwappedBytes<S> TrampHook(BYTE* src, BYTE* dst) {
			if (S < 14) {
				return SwappedBytes<S>();
			}

			BYTE* gateway = (BYTE*)VirtualAlloc(0, S, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

			memcpy(gateway, src, S);

			uintptr_t gatewayRelativeAddress = src - gateway - 5;

			*((HookLibrary::WORD*)(gateway + S)) = 0xFF25;

			*(uintptr_t*)((uintptr_t)gateway + S + 1) = gatewayRelativeAddress;

			return Detour(src, dst, S);
		}
#else
		template<DWORD S>
		SwappedBytes<S> TrampHook(BYTE* src, BYTE* dst) {
			if (S < 5) {
				return SwappedBytes<S>();
			}

			BYTE* gateway = (BYTE*)VirtualAlloc(0, S, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

			memcpy(gateway, src, S);

			uintptr_t gatewayRelativeAddress = src - gateway - 5;

			*(gateway + S) = 0xE9;

			*(uintptr_t*)((uintptr_t)gateway + S + 1) = gatewayRelativeAddress;

			return Detour(src, dst, S);
		}
#endif

		template<DWORD S>
		SwappedBytes<S> WriteBytes(BYTE* dst, const char* bytes) {
			SwappedBytes<S> sb(dst);

			DWORD currentProtection;

			VirtualProtect(dst, S, PAGE_EXECUTE_READWRITE, &currentProtection);

			memcpy(dst, bytes, S);
			VirtualProtect(dst, S, currentProtection, &currentProtection);

			return sb;
		}

		template<DWORD S>
		SwappedBytes<S> Nop(BYTE* dst) {
			SwappedBytes<S> sb(dst);
			DWORD currentProtection;

			VirtualProtect(dst, S, PAGE_EXECUTE_READWRITE, &currentProtection);

			memset(dst, 0x90, S);
			VirtualProtect(dst, S, currentProtection, &currentProtection);

			return sb;
		}

	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_SWAPPEDBYTES_H_