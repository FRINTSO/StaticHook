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
GetModuleBaseOfAddress(_In_ DWORD dwProcessId, _In_ PVOID pAddress) {
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
GetModuleNameW(_In_opt_ HMODULE hModule, _Out_ PMODULE_NAMEW pModuleName) {
	wchar_t fullPath[MAX_PATH]{ 0 };
	wchar_t fname[MAX_PATH]{ 0 };
	wchar_t ext[MAX_PATH]{ 0 };
	GetModuleFileNameW(hModule, fullPath, MAX_PATH);
	_wsplitpath(fullPath, 0, 0, fname, ext);
	wcscpy(pModuleName->szModuleName, fname);
	wcscat(pModuleName->szModuleName, ext);
}

VOID
WINAPI
GetModuleNameA(_In_opt_ HMODULE hModule, _Out_ PMODULE_NAMEA pModuleName) {
	char fullPath[MAX_PATH]{ 0 };
	char fname[MAX_PATH]{ 0 };
	char ext[MAX_PATH]{ 0 };
	GetModuleFileNameA(hModule, fullPath, MAX_PATH);
	_splitpath(fullPath, 0, 0, fname, ext);
	strcpy(pModuleName->szModuleName, fname);
	strcat(pModuleName->szModuleName, ext);
}

VOID
WINAPI
GetModuleEntryW(_In_ DWORD dwProcessId, _In_ HMODULE hModule, _Out_ PMODULEENTRY32W pme) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		pme->dwSize = sizeof(*pme);
		if (Module32FirstW(hSnap, pme)) {
			do {
				if (pme->hModule == hModule) {
					break;
				}
			} while (Module32NextW(hSnap, pme));
		}
	}
	CloseHandle(hSnap);
}

VOID
WINAPI
GetModuleEntryA(_In_ DWORD dwProcessId, _In_ HMODULE hModule, _Out_ PMODULEENTRY32 pme) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		pme->dwSize = sizeof(*pme);
		if (Module32First(hSnap, pme)) {
			do {
				if (pme->hModule == hModule) {
					break;
				}
			} while (Module32Next(hSnap, pme));
		}
	}
	CloseHandle(hSnap);
}