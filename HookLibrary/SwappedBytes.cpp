#include "SwappedBytes.h"

#include <Windows.h>

#include <utility>

// Destination: skriver data till
// Source: läser data från

namespace HookLibrary {
	namespace HookUtils {

		SwappedBytes::SwappedBytes()
			: src(nullptr), bytes(nullptr), length(NULL)
		{}

		SwappedBytes::SwappedBytes(BYTE* src, DWORD length)
			: src(src), bytes(new BYTE[length]), length(length)
		{
			memcpy_s(bytes, length, src, length);
		}

		SwappedBytes::~SwappedBytes() {
			delete[] bytes;

			src = nullptr;
			bytes = nullptr;
			length = NULL;
		}

#if _WIN64
		SwappedBytes Detour(BYTE* dst, BYTE* function, DWORD length) {
			if (length < 14) {
				return SwappedBytes();
			}

			SwappedBytes sb(dst, length);

			DWORD currentProtection;

			VirtualProtect(dst, length, PAGE_EXECUTE_READWRITE, &currentProtection);

			*dst = 0xFF;
			*(dst + 0x1) = 0x25;

			for (DWORD x = 2; x < 7; x++)
			{
				*(dst + x) = 0x00;
			}

			*(QWORD*)(dst + 0x6) = (QWORD)function;
			for (DWORD x = 14; x < length; x++)
			{
				*(dst + x) = 0x90;
			}

			VirtualProtect(dst, length, currentProtection, &currentProtection);

			return sb;
		}
#else
		SwappedBytes Detour(BYTE* dst, BYTE* function, DWORD length) {

			if (length < 5) {
				return SwappedBytes();
			}

			SwappedBytes sb(dst, length);

			DWORD currentProtection;

			VirtualProtect(dst, length, PAGE_EXECUTE_READWRITE, &currentProtection);

			DWORD relativeAddress = function - dst - 5;

			*dst = 0xE9;

			*(DWORD*)(dst + 1) = relativeAddress;

			for (DWORD x = 0x5; x < length; x++)
			{
				*(dst + x) = 0x90;
			}

			VirtualProtect(dst, length, currentProtection, &currentProtection);

			return sb;
		}
#endif

		SwappedBytes WriteBytes(BYTE* dst, const char* bytes, DWORD length) {
			SwappedBytes sb(dst, length);

			DWORD currentProtection;

			VirtualProtect(dst, length, PAGE_EXECUTE_READWRITE, &currentProtection);

			for (DWORD x = 0; x < length; x++)
			{
				*(dst + x) = *(bytes + x);
			}

			VirtualProtect(dst, length, currentProtection, &currentProtection);

			return sb;
		}

		SwappedBytes Nop(BYTE* dst, DWORD length) {
			SwappedBytes sb(dst, length);

			DWORD currentProtection;

			VirtualProtect(dst, length, PAGE_EXECUTE_READWRITE, &currentProtection);

			for (DWORD x = 0; x < length; x++)
			{
				*(dst + x) = 0x90;
			}

			VirtualProtect(dst, length, currentProtection, &currentProtection);

			return sb;
		}

		void SwappedBytes::Restore() {
			DWORD currentProtection;

			VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

			if (src && bytes) {
				for (DWORD x = 0; x < length; x++)
				{
					*(src + x) = *(bytes + x);
				}
			}

			VirtualProtect(src, length, currentProtection, &currentProtection);
		}

	} // namespace HookUtils
} // namespace HookLibrary