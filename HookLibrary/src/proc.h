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
	_In_ PCWSTR pszProcessName
	);

DWORD
WINAPI
GetProcessIdA(
	_In_ PCSTR pszProcessName
	);

#ifdef UNICODE
#define GetProcessId GetProcessIdW
#else
#define GetProcessId GetProcessIdA
#endif // !UNICODE

PVOID
WINAPI
GetModuleBaseAddressW(
	_In_ DWORD dwProcessId,
	_In_ PCWSTR pszModuleName
	);

PVOID
WINAPI
GetModuleBaseAddressA(
	_In_ DWORD dwProcessId,
	_In_ PCSTR pszModuleName
	);

#ifdef UNICODE
#define GetModuleBaseAddress GetModuleBaseAddressW
#else
#define GetModuleBaseAddress GetModuleBaseAddressA
#endif // !UNICODE


PVOID
WINAPI
GetBaseOfAddress(
	_In_ DWORD dwProcessId,
	_In_ PVOID lpAddress
	);



typedef struct _MODULE_NAMEW {
	WCHAR szModuleName[MAX_PATH];
} MODULE_NAMEW, *PMODULE_NAMEW;

VOID
WINAPI
GetModuleNameW(
	_Out_ PMODULE_NAMEW pModuleName
	);


typedef struct _MODULE_NAMEA {
	char szModuleName[MAX_PATH];
} MODULE_NAMEA, *PMODULE_NAMEA;

VOID
WINAPI
GetModuleNameA(
	_Out_ PMODULE_NAMEA pModuleName
	);


#ifdef UNICODE
#define GetModuleName GetModuleNameW
#define MODULE_NAME MODULE_NAMEW
#define PMODULE_NAME PMODULE_NAMEW
#endif // !UNICODE

VOID
WINAPI
GetModuleByBaseAddressW(
	_In_ DWORD dwProcessId,
	_In_ PVOID pModuleBaseAddress,
	_Out_ PMODULE_NAMEW pModuleName
	);

VOID
WINAPI
GetModuleByBaseAddressA(
	_In_ DWORD dwProcessId,
	_In_ PVOID pModuleBaseAddress,
	_Out_ PMODULE_NAMEA pModuleName
	);

#ifdef UNICODE
#define GetModuleByBaseAddress GetModuleByBaseAddressW
#endif // !UNICODE

VOID
WINAPI
GetModuleEntryW(
	_In_ DWORD dwProcessId,
	_In_ PCWSTR pszModuleName,
	_Out_ PMODULEENTRY32W pme
	);


VOID
WINAPI
GetModuleEntryA(
	_In_ DWORD dwProcessId,
	_In_ PCSTR pszModuleName,
	_Out_ PMODULEENTRY32 pme
	);

#ifdef UNICODE
#define GetModuleEntry GetModuleEntryW
#else
#define GetModuleEntry GetModuleEntryA
#endif // UNICODE


#endif // !STATICHOOK_PROC_H_
