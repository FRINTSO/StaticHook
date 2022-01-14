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

			friend SwappedBytes Detour32(BYTE* dst, PVOID lpFunction, SIZE_T size);
			friend SwappedBytes Nop(BYTE* dst, SIZE_T size);
			friend SwappedBytes WriteBytes(BYTE* dst, PCSTR pattern, SIZE_T size);
		private:
			SwappedBytes() = default;
			SwappedBytes(BYTE* src, SIZE_T bytes);
			SwappedBytes(PULONG_PTR src, PVOID function);
			SwappedBytes(const SwappedBytes&) = delete;

		public:
			friend class ModuleJumpTable;

			ULONG_PTR src;
			BYTE* originalBytes;
			SIZE_T bytesSize;
			PVOID lpFunction;
		};
		
		SwappedBytes Detour32(BYTE* dst, PVOID lpFunction, SIZE_T size);
		SwappedBytes Nop(BYTE* dst, SIZE_T size);
		SwappedBytes WriteBytes(BYTE* dst, PCSTR pattern, SIZE_T size);

	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_SWAPPEDBYTES_H_
