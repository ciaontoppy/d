#pragma once
#include "defines.hpp"

NTSTATUS read_physical_memory(PVOID target_address, PVOID buffer, SIZE_T size, SIZE_T* bytes_read)
{
	MM_COPY_ADDRESS copy_addr = { 0 };
	copy_addr.PhysicalAddress.QuadPart = (LONGLONG)target_address;

	return MmCopyMemory(buffer, copy_addr, size, MM_COPY_MEMORY_PHYSICAL, bytes_read);
}

struct cache {
    uintptr_t Address;
    MMPTE Value;
    bool IsValid;
};
static cache cached_pml4e[512];
static cache cached_pde[512];
static cache cached_pte[512];
UINT64 translate_linear(UINT64 directoryTableBase, UINT64 virtualAddress)
{
    _virt_addr_t virtual_address{};
    virtual_address.value = PVOID(virtualAddress);
    SIZE_T Size = 0;

    uintptr_t pml4eAddress = directoryTableBase + 8 * virtual_address.pml4_index;
    if (!cached_pml4e[virtual_address.pml4_index].IsValid || cached_pml4e[virtual_address.pml4_index].Address != pml4eAddress)
    {
        read_physical_memory(PVOID(pml4eAddress), reinterpret_cast<PVOID>(&cached_pml4e[virtual_address.pml4_index].Value), 8, &Size);

        cached_pml4e[virtual_address.pml4_index].Address = pml4eAddress;
        cached_pml4e[virtual_address.pml4_index].IsValid = cached_pml4e[virtual_address.pml4_index].Value.u.Hard.Valid;
    }

    if (!cached_pml4e[virtual_address.pml4_index].IsValid)
        return 0;

    uintptr_t pdptAddress = (cached_pml4e[virtual_address.pml4_index].Value.u.Hard.PageFrameNumber << 12) + 8 * virtual_address.pdpt_index;
    MMPTE pdpteValue;
    read_physical_memory(PVOID(pdptAddress), reinterpret_cast<PVOID>(&pdpteValue), 8, &Size);

    if (!pdpteValue.u.Hard.Valid)
        return 0;

    uintptr_t pdeAddress = (pdpteValue.u.Hard.PageFrameNumber << 12) + 8 * virtual_address.pd_index;
    MMPTE pdeValue;
    read_physical_memory(PVOID(pdeAddress), reinterpret_cast<PVOID>(&pdeValue), 8, &Size);

    if (!pdeValue.u.Hard.Valid)
        return 0;

    uintptr_t pteAddress = (pdeValue.u.Hard.PageFrameNumber << 12) + 8 * virtual_address.pt_index;
    MMPTE pteValue;
    read_physical_memory(PVOID(pteAddress), reinterpret_cast<PVOID>(&pteValue), 8, &Size);

    if (!pteValue.u.Hard.Valid)
        return 0;

    return (pteValue.u.Hard.PageFrameNumber << 12) + virtual_address.offset;
}