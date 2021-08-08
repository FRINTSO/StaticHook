#ifndef STATICHOOK_PROC_H_
#define STATICHOOK_PROC_H_

#include <cstdint>

#include "DataTypes.h"

HookLibrary::DWORD GetProcId(const wchar_t* procName);
uintptr_t GetModuleBaseAddress(HookLibrary::DWORD procId, const wchar_t* modName);

#endif // !STATICHOOK_PROC_H_
