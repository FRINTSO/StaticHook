#ifndef STATICHOOK_PROC_H_
#define STATICHOOK_PROC_H_

#include <Windows.h>

#include <cstdint>

DWORD
WINAPI
GetProcessIdW(
	_In_ LPCWSTR lpProcessName
	);

DWORD
WINAPI
GetProcessIdA(
	_In_ LPCSTR lpProcessName
	);

#ifdef UNICODE
#define GetProcessId GetProcessIdW
#else
#define GetProcessId GetProcessIdA
#endif // !UNICODE

LPVOID
WINAPI
GetModuleBaseAddressW(
	_In_ DWORD dwProcessId,
	_In_ LPCWSTR lpModuleName
	);

LPVOID
WINAPI
GetModuleBaseAddressA(
	_In_ DWORD dwProcessId,
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
GetModuleNameW(
	_Out_ LPMODULE_NAMEW lpModuleName
	);


typedef struct _MODULE_NAMEA {
	char szModuleName[MAX_PATH];
} MODULE_NAMEA, *LPMODULE_NAMEA;

VOID
WINAPI
GetModuleNameA(
	_Out_ LPMODULE_NAMEA lpModuleName
	);


#ifdef UNICODE
#define GetModuleName GetModuleNameW
#define MODULE_NAME MODULE_NAMEW
#define LPMODULE_NAME LPMODULE_NAMEW
#endif // !UNICODE

#endif // !STATICHOOK_PROC_H_
