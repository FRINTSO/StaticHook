#ifndef STATICHOOK_HOOKUTILS_H_
#define STATICHOOK_HOOKUTILS_H_

namespace HookLibrary {
	namespace HookUtils {
		bool Detour(unsigned char* src, unsigned char* dst, unsigned long length);
		unsigned char* TrampHook(unsigned char* src, unsigned char* dst, unsigned long length);
		void RestoreJMP(unsigned char* src, const char* bytes, unsigned long length);
		void WriteBytes(unsigned char* src, const char* bytes, unsigned long length);
	}
}

#endif // !STATICHOOK_HOOKUTILS_H_