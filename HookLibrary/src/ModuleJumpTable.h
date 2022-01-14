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

				ModuleJumpTable(ULONG64 baseAddress);

				static ModuleJumpTable* FetchModuleJumpTable(BYTE* dst) {
					DWORD dwProcessId = GetCurrentProcessId();

					ULONG64 baseAddress = (ULONG64)GetBaseOfAddress(dwProcessId, (LPVOID)dst);

					if (baseAddress == NULL) {
						HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, false, dwProcessId);

						MEMORY_BASIC_INFORMATION memInfo;

						VirtualQueryEx(hProcess, dst, &memInfo, sizeof(memInfo));

						CloseHandle(hProcess);

						throw "Base address was null";
					}
					else {
						std::unordered_map<ULONG64, ModuleJumpTable>::iterator got = ModuleJumpTable::jumpTables.find(baseAddress);

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

				static std::unordered_map<ULONG64, ModuleJumpTable> jumpTables;

				LPVOID RegisterSwappedBytes(SwappedBytes* swappedBytes);

				VOID UnregisterSwappedBytes(SwappedBytes* swappedBytes);

			private:

				void ReallocateJumpTable(size_t newCapacity);

				BOOL AllocateJumpTable(size_t size);

				VOID DeallocateJumpTable(ULONG64 address);

				VOID ReallocateJumps(size_t newCapacity);

				friend class SwappedBytes;

				ULONG64 baseAddress = NULL;
				ULONG baseSize = 0;
				ULONG64 allocationBase = NULL;
				ULONG allocationSize = 0;

				AbsoluteFarJmp* jumps = nullptr;
				size_t jumpsSize = 0;
				size_t jumpsCapacity = 0;
			};

		} // namespace Memory
	} // namespace HookUtils
} // namespace HookLibrary

#endif // !STATICHOOK_MODULEJUMPTABLE_H_