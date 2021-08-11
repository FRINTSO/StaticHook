#ifndef STATICHOOK_PROC_H_
#define STATICHOOK_PROC_H_

#include <Windows.h>

#include <cstdint>

DWORD
WINAPI
GetProcIdW(
	_In_ LPCWSTR lpProcessName
	);

DWORD
WINAPI
GetProcIdA(
	_In_ LPCSTR lpProcessName
	);

#ifdef UNICODE
#define GetProcId GetProcIdW
#else
#define GetProcId GetProcIdA
#endif // !UNICODE

LPVOID
WINAPI
GetModuleBaseAddressW(
	_In_ DWORD procId,
	_In_ LPCWSTR lpModuleName
	);

LPVOID
WINAPI
GetModuleBaseAddressA(
	_In_ DWORD procId,
	_In_ LPCSTR lpModuleName
	);

#ifdef UNICODE
#define GetModuleBaseAddress GetModuleBaseAddressW
#else
#define GetModuleBaseAddress GetModuleBaseAddressA
#endif // !UNICODE


typedef struct _MODULE_NAMEW {
	WCHAR szModuleName[MAX_PATH];
} MODULE_NAMEW, *LPMODULE_NAMEW;

VOID
WINAPI
GetModuleNameW(_Out_ LPMODULE_NAMEW lpModuleName);


typedef struct _MODULE_NAME {
	char szModuleName[MAX_PATH];
} MODULE_NAME, *LPMODULE_NAME;

VOID
WINAPI
GetModuleNameA(_Out_ LPMODULE_NAME lpModuleName);


#ifdef UNICODE
#define GetModuleName GetModuleNameW
#define MODULE_NAME MODULE_NAMEW
#define LPMODULE_NAME LPMODULENAMEW
#endif // !UNICODE

#endif // !STATICHOOK_PROC_H_
