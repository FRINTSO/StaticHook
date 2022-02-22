// Implementation details:
// All calls to allocation functions, allocates a space in the jump table, and hooks the jump to the table

// Example
// Detour32<5>(SRC, FUNCTION);
// Detour32 sends a request to module jump table and allcoates the FUNCTION and stores it in the jump table
// ModuleJumpTable returns the address in the jump table, so that the detour32 function can hook the jump to the returned address
// This way when we want to deallocate the jump table, the hook gets automatically restored to original code
// SwappedBytes object gets returned
// If the user wants to restore the SwappedBytes object, then the jump table removes the hook's entry in the jump table


#ifndef STATICHOOK_MODULEJUMPTABLE_H_
#define STATICHOOK_MODULEJUMPTABLE_H_

#include <Windows.h>

#include <unordered_map>

#include "proc.h"
#include "AbsoluteFarJmp.h"
#include "SwappedBytes.h"

namespace HookLibrary {
	namespace HookUtils {
		namespace Memory {

			class ModuleJumpTable {
			public:
				ModuleJumpTable();

				~ModuleJumpTable();

				ModuleJumpTable(const ModuleJumpTable& other) = delete;

				ModuleJumpTable(ModuleJumpTable&& other) noexcept;

				ModuleJumpTable& operator=(const ModuleJumpTable& rhs);

				ModuleJumpTable(ULONG_PTR baseAddress);

				static ModuleJumpTable* FetchModuleJumpTable(BYTE* dst) {
					DWORD dwProcessId = GetCurrentProcessId();

					ULONG_PTR baseAddress = (ULONG_PTR)GetModuleBaseOfAddress(dwProcessId, (LPVOID)dst);

					if (baseAddress == NULL) {
						HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, false, dwProcessId);

						MEMORY_BASIC_INFORMATION memInfo;

						VirtualQueryEx(hProcess, dst, &memInfo, sizeof(memInfo));

						CloseHandle(hProcess);

						throw "Base address was null";
					}
					else {
						std::unordered_map<ULONG_PTR, ModuleJumpTable>::iterator got = ModuleJumpTable::jumpTables.find(baseAddress);

						ModuleJumpTable* jumpTable = nullptr;

						if (got == ModuleJumpTable::jumpTables.end()) { // create new jumptable
							jumpTable = &ModuleJumpTable::jumpTables.emplace(baseAddress, ModuleJumpTable(baseAddress)).first->second;
						}
						else {
							jumpTable = &got->second;
						}

						return jumpTable;
					}
				}

				static std::unordered_map<ULONG_PTR, ModuleJumpTable> jumpTables;

				PVOID RegisterSwappedBytes(SwappedBytes* swappedBytes);

				VOID UnregisterSwappedBytes(SwappedBytes* swappedBytes);

			private:

				VOID ReallocateJumpTable(SIZE_T newCapacity);

				BOOL AllocateJumpTable(SIZE_T size);

				VOID DeallocateJumpTable(ULONG_PTR address);

				VOID ReallocateJumps(SIZE_T newCapacity);

				friend class SwappedBytes;

				ULONG_PTR baseAddress = NULL;
				SIZE_T baseSize = 0;
				ULONG_PTR allocationBase = NULL;
				SIZE_T allocationSize = 0;

				AbsoluteFarJmp* jumps = nullptr;
				SIZE_T jumpsSize = 0;
				SIZE_T jumpsCapacity = 0;
			};

		} // namespace Memory
	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_MODULEJUMPTABLE_H_