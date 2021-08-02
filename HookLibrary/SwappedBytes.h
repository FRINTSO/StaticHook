#ifndef STATICHOOK_SWAPPEDBYTES_H_
#define STATICHOOK_SWAPPEDBYTES_H_

#include "DataTypes.h"

namespace HookLibrary {
	namespace HookUtils {

		class SwappedBytes {
		public:
			void Restore();

			~SwappedBytes();
		private:
			SwappedBytes();
			SwappedBytes(BYTE* src, DWORD length);

			BYTE* src;
			BYTE* bytes;
			DWORD length;
			
			friend SwappedBytes Detour(BYTE* dst, BYTE* function, DWORD length);
			friend SwappedBytes WriteBytes(BYTE* dst, const char* bytes, DWORD length);
			friend SwappedBytes Nop(BYTE* dst, DWORD length);
		};

		SwappedBytes Detour(BYTE* dst, BYTE* function, DWORD length);
		SwappedBytes WriteBytes(BYTE* dst, const char* bytes, DWORD length);
		SwappedBytes Nop(BYTE* dst, DWORD length);

	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_SWAPPEDBYTES_H_