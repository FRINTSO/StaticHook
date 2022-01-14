#ifndef STATICHOOK_SWAPPEDBYTES_H_
#define STATICHOOK_SWAPPEDBYTES_H_

#include "DataTypes.h"
#include "HookUtils.h"
#include "AbsoluteFarJmp.h"

namespace HookLibrary {
	namespace HookUtils {

		class SwappedBytes {
		public:
			SwappedBytes(SwappedBytes&& other) noexcept;
			~SwappedBytes();

			bool operator==(const SwappedBytes& other);

			void Restore();

			friend SwappedBytes Detour32(BYTE* dst, LPVOID lpFunction, size_t size);
			friend SwappedBytes Nop(BYTE* dst, size_t size);
			friend SwappedBytes WriteBytes(BYTE* dst, LPCSTR pattern, size_t size);
		private:
			SwappedBytes() = default;
			SwappedBytes(BYTE* src, size_t bytes);
			SwappedBytes(PULONG_PTR src, void* function);
			SwappedBytes(const SwappedBytes&) = delete;

		public:
			friend class ModuleJumpTable;

			ULONG64 src;
			BYTE* originalBytes;
			size_t bytesSize;
			LPVOID lpFunction;
		};

		SwappedBytes Detour32(BYTE* dst, LPVOID lpFunction, size_t size);
		SwappedBytes Nop(BYTE* dst, size_t size);
		SwappedBytes WriteBytes(BYTE* dst, LPCSTR pattern, size_t size);

	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_SWAPPEDBYTES_H_
