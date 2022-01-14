#include "ModuleJumpTable.h"

#include "SwappedBytes.h"

namespace HookLibrary {
	namespace HookUtils {
		namespace Memory {
			
			ModuleJumpTable::ModuleJumpTable()
				: baseAddress(NULL), baseSize(0), allocationBase(NULL), allocationSize(0), jumps(nullptr), jumpsSize(0), jumpsCapacity(0)
			{}

			ModuleJumpTable::~ModuleJumpTable() {
				if (allocationBase != NULL) {
					DeallocateJumpTable(allocationBase);
				}
				if (jumps != nullptr) {
					delete[] jumps;
				}

				baseAddress = NULL;
				baseSize = 0;
				allocationBase = NULL;
				allocationSize = 0;

				jumps = nullptr;
				jumpsSize = 0;
				jumpsCapacity = 0;

			}

			ModuleJumpTable::ModuleJumpTable(ModuleJumpTable&& other) noexcept
				: baseAddress(other.baseAddress), baseSize(other.baseSize), allocationBase(other.allocationBase), allocationSize(other.allocationSize),
				jumps(other.jumps), jumpsSize(other.jumpsSize), jumpsCapacity(other.jumpsCapacity) {
				other.baseAddress = 0;
				other.baseSize = 0;
				other.allocationBase = 0;
				other.allocationSize = 0;
				other.jumps = nullptr;
				other.jumpsSize = 0;
				other.jumpsCapacity = 0;
			}

			ModuleJumpTable& ModuleJumpTable::operator=(const ModuleJumpTable& rhs) {
				if (jumps != nullptr) {
					delete[] jumps;
				}

				baseAddress = rhs.baseAddress;
				baseSize = rhs.baseSize;
				allocationBase = rhs.allocationBase;
				allocationSize = rhs.allocationSize;
				jumps = rhs.jumps;
				jumpsSize = rhs.jumpsSize;
				jumpsCapacity = rhs.jumpsCapacity;
				return *this;
			}
			
			ModuleJumpTable::ModuleJumpTable(ULONG_PTR baseAddress)
				: baseAddress(baseAddress) {

				DWORD peHeader = *(DWORD*)(baseAddress + 0x3C);

				DWORD sizeOfImage = *(DWORD*)(baseAddress + peHeader + 0x50);

				baseSize = sizeOfImage;

				ReallocateJumpTable(10);
			}

			PVOID ModuleJumpTable::RegisterSwappedBytes(SwappedBytes* swappedBytes) {
				for (SIZE_T i = 0; i < jumpsSize; i++) {
					if (*(ULONG_PTR*)jumps[i].absoluteMemoryAddress == (ULONG_PTR)swappedBytes->lpFunction) {
						throw "Multiple hooks can't target the same function";
					}
				}

				if (jumpsSize >= jumpsCapacity)
					ReallocateJumps(jumpsCapacity + jumpsCapacity / 2);

				if ((allocationSize - jumpsSize*sizeof(AbsoluteFarJmp)) < sizeof(AbsoluteFarJmp)) {
					// Reallocate Jump Table
					throw "Jumptable has reached full capacity, cannot allocate more jumps";
				}

				// store SwappedBytes Object
				// Update memory block with new jump

				jumps[jumpsSize] = std::move(swappedBytes->lpFunction);
				this->jumpsSize++;

				PVOID jumpAddress = (PVOID)(allocationBase + (jumpsSize - 1) * sizeof(AbsoluteFarJmp));

				memcpy(jumpAddress, (PVOID)&jumps[jumpsSize - 1], sizeof(AbsoluteFarJmp));

				return jumpAddress;
			}

			VOID ModuleJumpTable::UnregisterSwappedBytes(SwappedBytes* swappedBytes) {
				for (SIZE_T i = 0; i < jumpsSize; i++) {
					AbsoluteFarJmp farJump = jumps[i];
					PVOID functionAddress = *(PVOID*)farJump.absoluteMemoryAddress;
					if (functionAddress == (PVOID)swappedBytes->lpFunction) {

						SIZE_T remainingSize = (jumpsSize - (i + 1)) * sizeof(AbsoluteFarJmp);

						if (remainingSize != 0) {
							memcpy((PVOID)(allocationBase + sizeof(AbsoluteFarJmp) * i), (PVOID)(allocationBase + sizeof(AbsoluteFarJmp) * (i + 1)), remainingSize);
						}

						jumpsSize--;

						memset((PVOID)(allocationBase + jumpsSize * sizeof(AbsoluteFarJmp)), 0x0, sizeof(AbsoluteFarJmp));

						// remove entry from 
						memcpy((PVOID)&jumps[i], (PVOID)&jumps[i + 1], ((jumpsSize + 1) - (i + 1)) * sizeof(AbsoluteFarJmp));

						jumps[jumpsSize] = AbsoluteFarJmp();

						// remove from jumps list

						break;
					}
				}
			}

			std::unordered_map<ULONG_PTR, ModuleJumpTable> ModuleJumpTable::jumpTables = std::unordered_map<ULONG_PTR, ModuleJumpTable>();

			VOID ModuleJumpTable::ReallocateJumpTable(SIZE_T newCapacity) {
				// newCapacity: capacity of amount jumps
				// capacity doesn't referer to bytes allocated
				// bytes allocated is stored in allocationSize
				// capacity of 1 jump is 14 bytes, due to a jump being 14 bytes
				// floor capacity to nearest common divisor of 14

				SIZE_T sizeOfJumps = newCapacity * sizeof(AbsoluteFarJmp); // the size of an absolute jump is 14 bytes

				if (newCapacity == 0) {

					// restore hooks or point all active hooks to new jumptable
					// if new jumptable, then deallocate will deallocate new jumptable, not the old one

					DeallocateJumpTable(allocationBase);
				}

				if (newCapacity > jumpsCapacity) {
					BOOL bSuccess = AllocateJumpTable(sizeOfJumps);

					if (bSuccess)
						ReallocateJumps(newCapacity);
					else
						throw "Allocation of ModuleJumpTable failed";
				}
			}

			BOOL ModuleJumpTable::AllocateJumpTable(SIZE_T size) {
				// TODO: Refactor method and add a private findAllocationBase method which finds the allocation base, which also uses the highestAllocationBase

				DWORD dwProcessId = GetCurrentProcessId();
				HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);

				ULONG_PTR lowestAllocationBase = baseAddress + baseSize + INT32_MIN;
				// ULONG_PTR highestAllocationBase = (baseAddress + INT32_MAX + 5) - size;

				MEMORY_BASIC_INFORMATION memInfo{ 0 };

				ULONG_PTR selectedAllocationAddress = baseAddress;

				// find allocation base
				do {
					selectedAllocationAddress -= 0x10000;

					if (lowestAllocationBase > selectedAllocationAddress) {
						CloseHandle(hProcess);
						return FALSE;
					}

					VirtualQueryEx(hProcess, (LPCVOID)selectedAllocationAddress, &memInfo, sizeof(memInfo));

				} while (!(memInfo.State == MEM_FREE && memInfo.RegionSize >= size));

				CloseHandle(hProcess);

				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

				PVOID pAllocatedAddress = VirtualAllocEx(hProcess, (PVOID)selectedAllocationAddress, size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
				
				CloseHandle(hProcess);

				if (pAllocatedAddress == NULL) {
					allocationSize = 0;
					return FALSE;
				}
				allocationBase = (ULONG_PTR)pAllocatedAddress;

				allocationSize = ((size + 0xFFF) / 0x1000) * 0x1000;

				return TRUE;
			}

			VOID ModuleJumpTable::DeallocateJumpTable(ULONG_PTR address) {
				DWORD dwProcessId = GetCurrentProcessId();
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
				BOOL bSuccess = VirtualFreeEx(hProcess, (PVOID)address, 0, MEM_RELEASE);

				if (!bSuccess) throw "Jumptable deallocation failed";

				CloseHandle(hProcess);
			}

			VOID ModuleJumpTable::ReallocateJumps(SIZE_T newCapacity) {
				AbsoluteFarJmp* buffer = new AbsoluteFarJmp[newCapacity];

				if (newCapacity < jumpsSize)
					jumpsSize = newCapacity;

				for (SIZE_T i = 0; i < jumpsSize; i++)
					buffer[i] = std::move(jumps[i]);


				delete[] jumps;
				jumps = buffer;
				jumpsCapacity = newCapacity;
			}

		} // namespace Memory
	} // namespace HookUtils
} // namespace HookLibrary