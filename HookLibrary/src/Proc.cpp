#include "proc.h"

DWORD
WINAPI
GetProcessIdW(_In_ PCWSTR pszProcessName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32W procEntry{ 0 };
		procEntry.dwSize = sizeof(procEntry);

		if (Process32FirstW(hSnap, &procEntry)) {
			do {
				if (!_wcsicmp(procEntry.szExeFile, pszProcessName)) {
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32NextW(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

DWORD
WINAPI
GetProcessIdA(_In_ PCSTR pszProcessName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry{ 0 };
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {
			do {
				if (!_stricmp(procEntry.szExeFile, pszProcessName)) {
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

PVOID
WINAPI
GetModuleBaseAddressW(_In_ DWORD dwProcessId, _In_ PCWSTR pszModuleName) {
	PVOID moduleBaseAddress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32W moduleEntry{ 0 };
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32FirstW(hSnap, &moduleEntry)) {
			do {
				if (!_wcsicmp(moduleEntry.szModule, pszModuleName)) {
					moduleBaseAddress = (PVOID)moduleEntry.modBaseAddr;
					break;
				}
			} while (Module32NextW(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
	return moduleBaseAddress;
}

PVOID
WINAPI
GetModuleBaseAddressA(_In_ DWORD dwProcessId, _In_ PCSTR pszModuleName) {
	PVOID moduleBaseAddress = NULL;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 moduleEntry{ 0 };
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(hSnap, &moduleEntry)) {
			do {
				if (!_stricmp(moduleEntry.szModule, pszModuleName)) {
					moduleBaseAddress = (PVOID)moduleEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
	return moduleBaseAddress;
}


PVOID
WINAPI
GetBaseOfAddress(_In_ DWORD dwProcessId, _In_ PVOID pAddress) {
	PVOID moduleBaseAddress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32W moduleEntry{ 0 };
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32FirstW(hSnap, &moduleEntry)) {
			do
			{
				if (pAddress >= moduleEntry.modBaseAddr && pAddress < moduleEntry.modBaseAddr + moduleEntry.modBaseSize) {
					moduleBaseAddress = (PVOID)moduleEntry.modBaseAddr;
					break;
				}
			} while (Module32NextW(hSnap, &moduleEntry));
		}
	}

	CloseHandle(hSnap);
	return moduleBaseAddress;
}

VOID
WINAPI
GetModuleNameW(_Out_ PMODULE_NAMEW pModuleName) {
	HMODULE hExe = GetModuleHandleW(NULL);
	wchar_t fullPath[MAX_PATH]{ 0 };
	wchar_t fname[MAX_PATH]{ 0 };
	wchar_t ext[MAX_PATH]{ 0 };
	GetModuleFileNameW(hExe, fullPath, MAX_PATH);
	_wsplitpath(fullPath, 0, 0, fname, ext);
	wcscpy(pModuleName->szModuleName, fname);
	wcscat(pModuleName->szModuleName, ext);
}

VOID
WINAPI
GetModuleNameA(_Out_ PMODULE_NAMEA pModuleName) {
	HMODULE hExe = GetModuleHandleA(NULL);
	char fullPath[MAX_PATH]{ 0 };
	char fname[MAX_PATH]{ 0 };
	char ext[MAX_PATH]{ 0 };
	GetModuleFileNameA(hExe, fullPath, MAX_PATH);
	_splitpath(fullPath, 0, 0, fname, ext);
	strcpy(pModuleName->szModuleName, fname);
	strcat(pModuleName->szModuleName, ext);
}

VOID
WINAPI
GetModuleByBaseAddressW(_In_ DWORD dwProcessId, _In_ PVOID pModuleBaseAddress, _Out_ PMODULE_NAMEW pModuleName) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32W moduleEntry{ 0 };
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32FirstW(hSnap, &moduleEntry)) {
			do {
				if (moduleEntry.modBaseAddr == pModuleBaseAddress) {
					wcscpy(pModuleName->szModuleName, moduleEntry.szModule);
					break;
				}
			} while (Module32NextW(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
}

VOID
WINAPI
GetModuleByBaseAddressA(_In_ DWORD dwProcessId, _In_ PVOID pModuleBaseAddress, _Out_ PMODULE_NAMEA pModuleName) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 moduleEntry{ 0 };
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(hSnap, &moduleEntry)) {
			do {
				if (moduleEntry.modBaseAddr == pModuleBaseAddress) {
					strcpy(pModuleName->szModuleName, moduleEntry.szModule);
					break;
				}
			} while (Module32Next(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
}

VOID
WINAPI
GetModuleEntryW(_In_ DWORD dwProcessId, _In_ PCWSTR pszModuleName, _Out_ PMODULEENTRY32W pme) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		pme->dwSize = sizeof(*pme);
		if (Module32FirstW(hSnap, pme)) {
			do {
				if (!_wcsicmp(pme->szModule, pszModuleName)) {
					break;
				}
			} while (Module32NextW(hSnap, pme));
		}
	}
	CloseHandle(hSnap);
}

VOID
WINAPI
GetModuleEntryA(_In_ DWORD dwProcessId, _In_ PCSTR pszModuleName, _Out_ PMODULEENTRY32 pme) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		pme->dwSize = sizeof(*pme);
		if (Module32First(hSnap, pme)) {
			do {
				if (!_stricmp(pme->szModule, pszModuleName)) {
					break;
				}
			} while (Module32Next(hSnap, pme));
		}
	}
	CloseHandle(hSnap);
}