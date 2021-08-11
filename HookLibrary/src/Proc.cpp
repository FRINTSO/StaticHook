#include "proc.h"

#include <Windows.h>
#include <TlHelp32.h>

DWORD
WINAPI
GetProcIdW(_In_ LPCWSTR lpProcessName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {
			do {
				if (!_wcsicmp(procEntry.szExeFile, lpProcessName)) {
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

DWORD
WINAPI
GetProcIdA(_In_ LPCSTR lpProcessName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {
			do {
				if (!_wcsicmp(procEntry.szExeFile, lpProcessName)) {
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}



DWORD GetProcId(LPCWSTR procName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {
			do {
				if (!_wcsicmp(procEntry.szExeFile, procName)) {
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

uintptr_t GetModuleBaseAddress(HookLibrary::DWORD processId, const wchar_t* moduleName) {
	uintptr_t moduleBaseAddress = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(hSnap, &moduleEntry)) {
			do {
				if (_wcsicmp(moduleEntry.szModule, moduleName)) {
					moduleBaseAddress = (uintptr_t)moduleEntry.modBaseAddr;
				}
			} while (Module32Next(hSnap, &moduleEntry));
		}
	}
	CloseHandle(hSnap);
	return moduleBaseAddress;
}

VOID
WINAPI
GetModuleNameW(LPMODULE_NAME lpModuleName) {
	HMODULE hExe = GetModuleHandleW(NULL);
	wchar_t fullPath[MAX_PATH]{ 0 };
	wchar_t fname[MAX_PATH] = { 0 };
	wchar_t ext[MAX_PATH] = { 0 };
	GetModuleFileNameW(hExe, fullPath, MAX_PATH);
	_wsplitpath(fullPath, 0, 0, fname, ext);
	wcscpy(lpModuleName->modName, fname);
	wcscat(lpModuleName->modName, ext);
}

VOID
WINAPI
GetModuleName(LPMODULE_NAME lpModuleName) {
	HMODULE hExe = GetModuleHandleA(NULL);
	char fullPath[MAX_PATH]{ 0 };
	char fname[MAX_PATH] = { 0 };
	char ext[MAX_PATH] = { 0 };
	GetModuleFileNameA(hExe, fullPath, MAX_PATH);
	_splitpath(fullPath, 0, 0, fname, ext);
	strcpy(lpModuleName->modName, fname);
	strcat(lpModuleName->modName, ext);
}