#ifndef STATICHOOK_PROC_H_
#define STATICHOOK_PROC_H_

#include <Windows.h>

#ifdef UNICODE
#undef UNICODE
#include <TlHelp32.h>
#define UNICODE
#else
#include <TlHelp32.h>
#endif // !UNICODE

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


LPVOID
WINAPI
GetModuleBaseOfAddress(
	_In_ DWORD dwProcessId,
	_In_ LPVOID lpAddress
	);



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

VOID
WINAPI
GetModuleByBaseAddressW(
	_In_ DWORD dwProcessId,
	_In_ LPVOID lpModuleBaseAddress,
	_Out_ LPMODULE_NAMEW lpModuleName
	);

VOID
WINAPI
GetModuleByBaseAddressA(
	_In_ DWORD dwProcessId,
	_In_ LPVOID lpModuleBaseAddress,
	_Out_ LPMODULE_NAMEA lpModuleName
	);

#ifdef UNICODE
#define GetModuleByBaseAddress GetModuleByBaseAddressW
#endif // !UNICODE

VOID
WINAPI
GetModuleEntryW(
	_In_ DWORD dwProcessId,
	_In_ LPCWSTR lpModuleName,
	_Out_ LPMODULEENTRY32W lpme
	);


VOID
WINAPI
GetModuleEntryA(
	_In_ DWORD dwProcessId,
	_In_ LPCSTR lpModuleName,
	_Out_ LPMODULEENTRY32 lpme
	);

#ifdef UNICODE
#define GetModuleEntry GetModuleEntryW
#else
#define GetModuleEntry GetModuleEntryA
#endif // UNICODE


#endif // !STATICHOOK_PROC_H_
