#include "HookUtils.h"
#include <Windows.h>

#if _WIN64
bool HookLibrary::HookUtils::Detour(unsigned char* src, unsigned char* dst, unsigned long length = 14) {
	if (length < 14) {
		return false;
	}

	unsigned long currentProtection;

	VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

	*src = 0xFF;
	*(src + 0x1) = 0x25;

	for (unsigned long x = 2; x < 7; x++)
	{
		*(src + x) = 0x00;
	}

	*(uintptr_t*)(src + 0x6) = (uintptr_t)dst;
	for (unsigned long x = 14; x < length; x++)
	{
		*(src + x) = 0x90;
	}

	VirtualProtect(src, length, currentProtection, &currentProtection);

	return true;
}
#else
bool HookLibrary::HookUtils::Detour(unsigned char* src, unsigned char* dst, unsigned long length = 5) {
	if (length < 5) {
		return false;
	}

	unsigned long currentProtection;
	VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

	unsigned long relativeAddress = dst - src - 5;

	*src = 0xE9;

	*(unsigned long*)(src + 1) = relativeAddress;

	for (unsigned long x = 0x5; x < length; x++)
	{
		*(src + x) = 0x90;
	}

	VirtualProtect(src, length, currentProtection, &currentProtection);
	return true;
}
#endif

/*#if _WIN64
unsigned char* HookLibrary::HookUtils::TrampHook(unsigned char* src, unsigned char* dst, unsigned long length) {
		
}
#else*/
unsigned char* HookLibrary::HookUtils::TrampHook(unsigned char* src, unsigned char* dst, unsigned long length) {
	if (length < 5) {
		return 0;
	}

	unsigned char* gateway = (unsigned char*)VirtualAlloc(0, length, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	memcpy_s(gateway, length, src, length);

	unsigned long gatewayRelativeAddress = src - gateway - 5;

	*(gateway + length) = 0xE9;

	*(unsigned long*)((unsigned long)gateway + length + 1) = gatewayRelativeAddress;

	HookLibrary::HookUtils::Detour(src, dst, length);

	return gateway;
}
//#endif

void HookLibrary::HookUtils::RestoreJMP(unsigned char* src, const char* bytes, unsigned long length) {
	unsigned long currentProtection;

	VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

	for (unsigned long x = 0; x < length; x++)
	{
		*(src + x) = *(bytes + x);
	}

	VirtualProtect(src, length, currentProtection, &currentProtection);
}

void HookLibrary::HookUtils::WriteBytes(unsigned char* src, const char* bytes, unsigned long length) {
	unsigned long currentProtection;

	VirtualProtect(src, length, PAGE_EXECUTE_READWRITE, &currentProtection);

	for (unsigned long x = 0; x < length; x++)
	{
		*(src + x) = *(bytes + x);
	}

	VirtualProtect(src, length, currentProtection, &currentProtection);
}