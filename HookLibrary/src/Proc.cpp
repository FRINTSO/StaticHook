#include "proc.h"

#include <Windows.h>
#include <TlHelp32.h>

HookLibrary::DWORD GetProcId(const wchar_t* procName) {
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