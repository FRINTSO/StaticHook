#ifndef STATICHOOK_SWAPPEDBYTES_H_
#define STATICHOOK_SWAPPEDBYTES_H_

#include <Windows.h>

#include "DataTypes.h"
#include "HookUtils.h"

namespace HookLibrary {
	namespace HookUtils {

		template<size_t S>
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

			template<size_t S1> friend SwappedBytes<S1> Detour(BYTE* dst, BYTE* function);
			template<size_t S1> friend SwappedBytes<S1> TrampHook(BYTE* src, BYTE* dst);
			template<size_t S1> friend SwappedBytes<S1> WriteBytes(BYTE* dst, const char* bytes);
			template<size_t S1> friend SwappedBytes<S1> Nop(BYTE* dst);
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

		template<size_t S>
		SwappedBytes<S> Detour(BYTE* dst, BYTE* function) {
			if (S < 5) {
				return SwappedBytes<NULL>();
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

		template<size_t S>
		SwappedBytes<S> TrampHook(BYTE* src, BYTE* dst) {
			if (S < 5) {
				return SwappedBytes<NULL>();
			}

			BYTE* gateway = (BYTE*)VirtualAlloc(0, S, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

			memcpy(gateway, src, S);

			uintptr_t gatewayRelativeAddress = src - gateway - 5;

			*(gateway + S) = 0xE9;

			*(uintptr_t*)((uintptr_t)gateway + S + 1) = gatewayRelativeAddress;

			return Detour(src, dst, S);
		}

		template<size_t S>
		SwappedBytes<S> WriteBytes(BYTE* dst, const char* bytes) {
			SwappedBytes<S> sb(dst);

			DWORD currentProtection;

			VirtualProtect(dst, S, PAGE_EXECUTE_READWRITE, &currentProtection);

			for (DWORD x = 0; x < S; x++)
			{
				*(dst + x) = *(bytes + x);
			}

			VirtualProtect(dst, S, currentProtection, &currentProtection);

			return sb;
		}

		template<size_t S>
		SwappedBytes<S> Nop(BYTE* dst) {
			SwappedBytes<S> sb(dst);

			DWORD currentProtection;

			VirtualProtect(dst, S, PAGE_EXECUTE_READWRITE, &currentProtection);

			for (DWORD x = 0; x < S; x++)
			{
				*(dst + x) = 0x90;
			}

			VirtualProtect(dst, S, currentProtection, &currentProtection);

			return sb;
		}

	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_SWAPPEDBYTES_H_