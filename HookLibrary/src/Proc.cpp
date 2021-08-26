#include "proc.h"

#ifdef UNICODE
#undef UNICODE
#include <TlHelp32.h>
#define UNICODE
#else
#include <TlHelp32.h>
#endif // !UNICODE

DWORD
WINAPI
GetProcessIdW(_In_ LPCWSTR lpProcessName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32W procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32FirstW(hSnap, &procEntry)) {
			do {
				if (!_wcsicmp(procEntry.szExeFile, lpProcessName)) {
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
GetProcessIdA(_In_ LPCSTR lpProcessName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {
			do {
				if (!_stricmp(procEntry.szExeFile, lpProcessName)) {
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

LPVOID
WINAPI
GetModuleBaseAddressW(_In_ DWORD dwProcessId, _In_ LPCWSTR lpModuleName) {
	LPVOID moduleBaseAddress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32W moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32FirstW(hSnap, &moduleEntry)) {
			do {
				if (_wcsicmp(moduleEntry.szModule, lpModuleName)) {
					moduleBaseAddress = (LPVOID)moduleEntry.modBaseAddr;
				}
			} while (Module32NextW(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
	return moduleBaseAddress;
}

LPVOID
WINAPI
GetModuleBaseAddressA(_In_ DWORD dwProcessId, _In_ LPCSTR lpModuleName) {
	LPVOID moduleBaseAddress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(hSnap, &moduleEntry)) {
			do {
				if (_stricmp(moduleEntry.szModule, lpModuleName)) {
					moduleBaseAddress = (LPVOID)moduleEntry.modBaseAddr;
				}
			} while (Module32Next(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
	return moduleBaseAddress;
}


VOID
WINAPI
GetModuleNameW(_Out_ LPMODULE_NAMEW lpModuleName) {
	HMODULE hExe = GetModuleHandleW(NULL);
	wchar_t fullPath[MAX_PATH]{ 0 };
	wchar_t fname[MAX_PATH] = { 0 };
	wchar_t ext[MAX_PATH] = { 0 };
	GetModuleFileNameW(hExe, fullPath, MAX_PATH);
	_wsplitpath(fullPath, 0, 0, fname, ext);
	wcscpy(lpModuleName->szModuleName, fname);
	wcscat(lpModuleName->szModuleName, ext);
}

VOID
WINAPI
GetModuleNameA(_Out_ LPMODULE_NAMEA lpModuleName) {
	HMODULE hExe = GetModuleHandleA(NULL);
	char fullPath[MAX_PATH]{ 0 };
	char fname[MAX_PATH] = { 0 };
	char ext[MAX_PATH] = { 0 };
	GetModuleFileNameA(hExe, fullPath, MAX_PATH);
	_splitpath(fullPath, 0, 0, fname, ext);
	strcpy(lpModuleName->szModuleName, fname);
	strcat(lpModuleName->szModuleName, ext);
}
}

VOID
WINAPI
GetModuleByBaseAddressW(_In_ DWORD dwProcessId, _In_ LPVOID lpModuleBaseAddress, _Out_ LPMODULE_NAMEW lpModuleName) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32W moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32FirstW(hSnap, &moduleEntry)) {
			do {
				if (moduleEntry.modBaseAddr == lpModuleBaseAddress) {
					wcscpy(lpModuleName->szModuleName, moduleEntry.szModule);
					break;
				}
			} while (Module32NextW(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
}

VOID
WINAPI
GetModuleByBaseAddressA(_In_ DWORD dwProcessId, _In_ LPVOID lpModuleBaseAddress, _Out_ LPMODULE_NAMEA lpModuleName) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(hSnap, &moduleEntry)) {
			do {
				if (moduleEntry.modBaseAddr == lpModuleBaseAddress) {
					strcpy(lpModuleName->szModuleName, moduleEntry.szModule);
					break;
				}
			} while (Module32Next(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
}

VOID
WINAPI
GetModuleByBaseAddressW(_In_ DWORD dwProcessId, _In_ LPVOID lpModuleBaseAddress, _Out_ LPMODULE_NAMEW lpModuleName) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32W moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32FirstW(hSnap, &moduleEntry)) {
			do {
				if (moduleEntry.modBaseAddr == lpModuleBaseAddress) {
					wcscpy(lpModuleName->szModuleName, moduleEntry.szModule);
					break;
				}
			} while (Module32NextW(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
}

VOID
WINAPI
GetModuleByBaseAddressA(_In_ DWORD dwProcessId, _In_ LPVOID lpModuleBaseAddress, _Out_ LPMODULE_NAMEA lpModuleName) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(hSnap, &moduleEntry)) {
			do {
				if (moduleEntry.modBaseAddr == lpModuleBaseAddress) {
					strcpy(lpModuleName->szModuleName, moduleEntry.szModule);
					break;
				}
			} while (Module32Next(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
}

VOID
WINAPI
GetModuleEntryW( _In_ DWORD dwProcessId, _In_ LPCWSTR lpModuleName, _Out_ LPMODULEENTRY32W lpme) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		lpme->dwSize = sizeof(*lpme);
		if (Module32FirstW(hSnap, lpme)) {
			do {
				if (!_wcsicmp(lpme->szModule, lpModuleName)) {
					break;
				}
			} while (Module32NextW(hSnap, lpme));
		}
	}
	CloseHandle(hSnap);
}

VOID
WINAPI
GetModuleEntryA(_In_ DWORD dwProcessId, _In_ LPCSTR lpModuleName, _Out_ LPMODULEENTRY32 lpme) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		lpme->dwSize = sizeof(*lpme);
		if (Module32First(hSnap, lpme)) {
			do {
				if (!_stricmp(lpme->szModule, lpModuleName)) {
					break;
				}
			} while (Module32Next(hSnap, lpme));
		}
	}
	CloseHandle(hSnap);
}