#include "SwappedBytes.h"

#include <Windows.h>

#include <utility>

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
			delete src;
			delete[] bytes;

			src = nullptr;
			bytes = nullptr;
			length = NULL;
		}

#if _WIN64
		SwappedBytes Detour(BYTE* src, BYTE* dst, DWORD length) {
			/*if (length < 14) {
				return false;
			}

			DWORD currentProtection;

			VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

			*src = 0xFF;
			*(src + 0x1) = 0x25;

			for (DWORD x = 2; x < 7; x++)
			{
				*(src + x) = 0x00;
			}

			*(QWORD*)(src + 0x6) = (QWORD)dst;
			for (DWORD x = 14; x < length; x++)
			{
				*(src + x) = 0x90;
			}

			VirtualProtect(src, length, currentProtection, &currentProtection);

			return true;*/
		}
#else
		SwappedBytes&& Detour(BYTE* src, BYTE* dst, DWORD length) {

			if (length < 5) {
				return SwappedBytes();
			}

			SwappedBytes sb(src, length);

			DWORD currentProtection;

			VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

			DWORD relativeAddress = dst - src - 5;

			*src = 0xE9;

			*(DWORD*)(src + 1) = relativeAddress;

			for (DWORD x = 0x5; x < length; x++)
			{
				*(src + x) = 0x90;
			}

			VirtualProtect(src, length, currentProtection, &currentProtection);

			return std::move(sb);
		}
#endif

		SwappedBytes WriteBytes(BYTE* src, const char* bytes, DWORD length) {
			SwappedBytes sb(src, length);

			DWORD currentProtection;

			VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

			for (DWORD x = 0; x < length; x++)
			{
				*(src + x) = *(bytes + x);
			}

			VirtualProtect(src, length, currentProtection, &currentProtection);

			return sb;
		}

		void SwappedBytes::Restore() {
			DWORD currentProtection;

			VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

			if (src && bytes) {
				memcpy_s(src, length, bytes, length);
			}

			VirtualProtect(src, length, currentProtection, &currentProtection);
		}

	} // namespace HookUtils
} // namespace HookLibrary