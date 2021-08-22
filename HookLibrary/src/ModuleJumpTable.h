// Implementation details:
// All calls to allocation functions, allocates a space in the jump table, and hooks the jump to the table

// Example
// Detour32<5>(SRC, FUNCTION);
// Detour32 sends a request to module jump table and allcoates the FUNCTION and stores it in the jump table
// ModuleJumpTable returns the address in the jump table, so that the detour32 function can hook the jump to the returned address
// This way when we want to deallocate the jump table, the hook gets automatically restored to original code
// SwappedBytes object gets returned
// If the user wants to restore the SwappedBytes object, then the jump table removes the hook's entry in the jump table

// 


#ifndef STATICHOOK_MODULEJUMPTABLE_H_
#define STATICHOOK_MODULEJUMPTABLE_H_

#include <Windows.h>

#include "proc.h"
#include "SwappedBytes.h"

namespace HookLibrary {
	namespace HookUtils {
		namespace Memory {

			struct AbsoluteFarJmp {
				BYTE opcode[2]{ 0xFF, 0x25 };
				BYTE absoluteAddressSpecifier[4]{ 0x0, 0x0, 0x0, 0x0 };
				BYTE absoluteMemoryAddress[8]{ 0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x0 };

				AbsoluteFarJmp() = default;
				AbsoluteFarJmp(void* memoryAddress) {
					memcpy(absoluteMemoryAddress, &memoryAddress, 0x8);
				}
			}; // size: 0x14

			template<unsigned long HookCount>
			class ModuleJumpTable {
			public:
				ModuleJumpTable(const wchar_t* moduleName, const AbsoluteFarJmp(&initializer)[HookCount])
					: moduleName(moduleName) {

					// store hooks
					for (size_t i = 0; i < HookCount; i++) {
						jumps[i] = initializer[i];
					}

					// Get module base address
					DWORD dwProcessId = GetProcessIdW(moduleName);

					MODULEENTRY32W moduleEntry = { 0 };
					GetModuleEntryW(dwProcessId, moduleName, &moduleEntry);

					moduleBaseAddress = (unsigned long long)moduleEntry.modBaseAddr;
					moduleSize = (unsigned long)moduleEntry.modBaseSize;


					// Minimum allocation size is 1000 bytes

					unsigned long jumpsSize = 0x1000;
					while (sizeof(jumps) > jumpsSize) jumpsSize += 0x1000;
					allocationSize = jumpsSize;

					bool success = TryInject(dwProcessId);

					if (success) {
						memcpy((void*)allocationBase, (void*)jumps, HookCount * 14);
					}

					// Look for good allocation base

					// When found 
				}

				template<DWORD S>
				void Register(SwappedBytes<S> swappedBytes) {
					// Store swappedbytes object in linked list
				}

				void Deallocate() {
					// Store all memory addresses in the module that have been hooked
					// along with their original bytes

					// One hook can't be called from different addresses, due to jump-back-address



					// Deallocate all placed hooks

					// Make sure all hooks are restored to their original bytes befor deallocating hook-jump-table

					DWORD dwProcessId = GetProcessIdW(moduleName);

					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwProcessId);

					VirtualFreeEx(hProcess, (LPVOID)allocationBase, 0, MEM_RELEASE);

					CloseHandle(hProcess);
				}

				unsigned long long GetJumpTableAddressFromFunction(void* function) {
					int index = -1;
					for (size_t i = 0; i < HookCount; i++) {
						if (*(unsigned long long*)jumps[i].absoluteMemoryAddress == (unsigned long long)function) {
							index = (int)i;
							break;
						}
					}

					if (index == -1) return 0;

					return allocationBase + 14 * (size_t)index;
				}

				const wchar_t* moduleName;
				unsigned long long moduleBaseAddress;
				unsigned long moduleSize;
				unsigned long long allocationBase;
				unsigned long allocationSize;

				AbsoluteFarJmp jumps[HookCount];
			private:
				bool TryInject(DWORD dwProcessId) {
					HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, false, dwProcessId);
					unsigned long long selectedAllocationBase = moduleBaseAddress;
					MEMORY_BASIC_INFORMATION memInfo;

					// Last Possible Jump in module
					unsigned long long lowestAllocationBase = moduleBaseAddress + moduleSize - 0x80000000;

					do {
						selectedAllocationBase -= 0x10000;
						if (lowestAllocationBase > selectedAllocationBase) return false;

						VirtualQueryEx(hProcess, (LPCVOID)selectedAllocationBase, &memInfo, sizeof(memInfo));

					} while (!(memInfo.State == 0x10000 && memInfo.RegionSize >= sizeof(jumps)));

					CloseHandle(hProcess);

					hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwProcessId);

					allocationBase = (unsigned long long)VirtualAllocEx(hProcess, (LPVOID)selectedAllocationBase, sizeof(jumps), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

					CloseHandle(hProcess);

					return true;
				}
			};

		} // namespace Memory
	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_MODULEJUMPTABLE_H_