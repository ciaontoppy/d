#pragma once
#include "memory.hpp"

namespace pml
{
	PVOID split_memory(PVOID SearchBase, SIZE_T SearchSize, const void* Pattern, SIZE_T PatternSize)
	{
		const UCHAR* searchBase = static_cast<const UCHAR*>(SearchBase);
		const UCHAR* pattern = static_cast<const UCHAR*>(Pattern);

		for (SIZE_T i = 0; i <= SearchSize - PatternSize; ++i)
		{
			SIZE_T j = 0;
			for (; j < PatternSize; ++j)
			{
				if (searchBase[i + j] != pattern[j])
					break;
			}
			if (j == PatternSize)
				return const_cast<UCHAR*>(&searchBase[i]);
		}

		return nullptr;
	}

	void* g_mmonp_MmPfnDatabase;

	static NTSTATUS InitializeMmPfnDatabase()
	{
		struct MmPfnDatabaseSearchPattern
		{
			const UCHAR* bytes;
			SIZE_T bytes_size;
			bool hard_coded;
		};

		MmPfnDatabaseSearchPattern patterns;

		// Windows 10 x64 Build 14332+
		static const UCHAR kPatternWin10x64[] = {
			0x48, 0x8B, 0xC1,        // mov     rax, rcx
			0x48, 0xC1, 0xE8, 0x0C,  // shr     rax, 0Ch
			0x48, 0x8D, 0x14, 0x40,  // lea     rdx, [rax + rax * 2]
			0x48, 0x03, 0xD2,        // add     rdx, rdx
			0x48, 0xB8,              // mov     rax, 0FFFFFA8000000008h
		};

		patterns.bytes = kPatternWin10x64;
		patterns.bytes_size = sizeof(kPatternWin10x64);
		patterns.hard_coded = true;
		const auto p_MmGetVirtualForPhysical = reinterpret_cast<UCHAR*>(((MmGetVirtualForPhysical)));
		if (!p_MmGetVirtualForPhysical)
		{
			return STATUS_PROCEDURE_NOT_FOUND;
		}

		auto found = reinterpret_cast<UCHAR*>(split_memory(p_MmGetVirtualForPhysical, 0x20, patterns.bytes, patterns.bytes_size));
		if (!found)
		{
			return STATUS_UNSUCCESSFUL;
		}


		found += patterns.bytes_size;
		if (patterns.hard_coded) 
		{
			g_mmonp_MmPfnDatabase = *reinterpret_cast<void**>(found);
		}
		else
		{
			const auto mmpfn_address = *reinterpret_cast<ULONG_PTR*>(found);
			g_mmonp_MmPfnDatabase = *reinterpret_cast<void**>(mmpfn_address);
		}

		g_mmonp_MmPfnDatabase = PAGE_ALIGN(g_mmonp_MmPfnDatabase);

		return STATUS_SUCCESS;
	}

	uintptr_t dirbase_from_base_address(void* base)
	{
		if (!NT_SUCCESS(InitializeMmPfnDatabase()))
			return 0;

		virt_addr_t virt_base{}; virt_base.value = base;

		size_t read{};

		auto ranges = MmGetPhysicalMemoryRanges();

		for (int i = 0;; i++)
		{
			auto elem = &ranges[i];

			if (!elem->BaseAddress.QuadPart || !elem->NumberOfBytes.QuadPart)
				break;

			UINT64 current_phys_address = elem->BaseAddress.QuadPart;

			for (int j = 0; j < (elem->NumberOfBytes.QuadPart / 0x1000); j++, current_phys_address += 0x1000)
			{
				_MMPFN* pnfinfo = (_MMPFN*)((uintptr_t)g_mmonp_MmPfnDatabase + (current_phys_address >> 12) * sizeof(_MMPFN));

				if (pnfinfo->u4.PteFrame == (current_phys_address >> 12))
				{
					MMPTE pml4e{};
					if (!NT_SUCCESS(read_physical_memory(PVOID(current_phys_address + 8 * virt_base.pml4_index), &pml4e, 8, &read)))
						continue;

					if (!pml4e.u.Hard.Valid)
						continue;

					MMPTE pdpte{};
					if (!NT_SUCCESS(read_physical_memory(PVOID((pml4e.u.Hard.PageFrameNumber << 12) + 8 * virt_base.pdpt_index), &pdpte, 8, &read)))
						continue;

					if (!pdpte.u.Hard.Valid)
						continue;

					MMPTE pde{};
					if (!NT_SUCCESS(read_physical_memory(PVOID((pdpte.u.Hard.PageFrameNumber << 12) + 8 * virt_base.pd_index), &pde, 8, &read)))
						continue;

					if (!pde.u.Hard.Valid)
						continue;

					MMPTE pte{};
					if (!NT_SUCCESS(read_physical_memory(PVOID((pde.u.Hard.PageFrameNumber << 12) + 8 * virt_base.pt_index), &pte, 8, &read)))
						continue;

					if (!pte.u.Hard.Valid)
						continue;

					return current_phys_address;
				}
			}
		}

		return 0;
	}
}

NTSTATUS handle_memory_request(p_read req)
{
	if (req->security != code_security)
	{
		return STATUS_UNSUCCESSFUL;
	}

	if (!req->process_id)
	{
		return STATUS_UNSUCCESSFUL;
	}

	PEPROCESS process = 0;
	PsLookupProcessByProcessId((HANDLE)req->process_id, &process);
	if (!process)
	{
		return STATUS_UNSUCCESSFUL;
	}
	ObDereferenceObject(process);

	SIZE_T total_size = req->size;

	INT64 physical_addr = translate_linear(m_stored_dtb, (ULONG64)req->address);
	if (!physical_addr)
	{
		return STATUS_UNSUCCESSFUL;
	}

	ULONG64 final_size = find_min(PAGE_SIZE - (physical_addr & 0xfff), total_size);
	SIZE_T bytes_read = 0;

	read_physical_memory(PVOID(physical_addr), (PVOID)((ULONG64)req->buffer), final_size, &bytes_read);

	return STATUS_SUCCESS;
}

NTSTATUS handle_dirbase_fix(p_dirbase req)
{
	dirbase dtbdata = { 0 };
	if (!req->process_id)
	{
		return STATUS_UNSUCCESSFUL;
	}

	PEPROCESS procc = 0;
	PsLookupProcessByProcessId((HANDLE)req->process_id, &procc);
	if (!procc)
	{
		return STATUS_UNSUCCESSFUL;
	}
	m_stored_dtb = pml::dirbase_from_base_address((void*)PsGetProcessSectionBaseAddress(procc));
	ObDereferenceObject(procc);

	ULONGLONG raaa = 1;
	RtlCopyMemory(req->operation, &raaa, sizeof(raaa));

	return STATUS_SUCCESS;
}

NTSTATUS handle_base_request(p_base req)
{
	if (req->security != code_security)
	{
		return STATUS_UNSUCCESSFUL;
	}

	if (!req->process_id)
	{
		return STATUS_UNSUCCESSFUL;
	}

	PEPROCESS process = 0;
	PsLookupProcessByProcessId((HANDLE)req->process_id, &process);
	if (!process)
	{
		return STATUS_UNSUCCESSFUL;
	}

	ULONGLONG image_base = (ULONGLONG)PsGetProcessSectionBaseAddress(process);
	if (!image_base)
	{
		return STATUS_UNSUCCESSFUL;
	}

	RtlCopyMemory(req->address, &image_base, sizeof(image_base));
	ObDereferenceObject(process);

	return STATUS_SUCCESS;
}

NTSTATUS io_control_handler(PDEVICE_OBJECT device_obj, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_obj);

	NTSTATUS status = {};
	ULONG bytes_returned = {};
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);
	ULONG io_control_code = stack->Parameters.DeviceIoControl.IoControlCode;
	ULONG input_buffer_length = stack->Parameters.DeviceIoControl.InputBufferLength;

	if (io_control_code == code_read)
	{
		if (input_buffer_length == sizeof(_read))
		{
			p_read req = (p_read)(irp->AssociatedIrp.SystemBuffer);
			status = handle_memory_request(req);
			bytes_returned = sizeof(_read);
		}
		else
		{
			status = STATUS_INFO_LENGTH_MISMATCH;
			bytes_returned = 0;
		}
	}
	if (io_control_code == code_dirbase_fix)
	{
		if (input_buffer_length == sizeof(_dirbase))
		{
			p_dirbase req = (p_dirbase)(irp->AssociatedIrp.SystemBuffer);
			status = handle_dirbase_fix(req);
			bytes_returned = sizeof(_dirbase);
		}
		else
		{
			status = STATUS_INFO_LENGTH_MISMATCH;
			bytes_returned = 0;
		}
	}
	else if (io_control_code == code_base)
	{
		if (input_buffer_length == sizeof(_base))
		{
			p_base req = (p_base)(irp->AssociatedIrp.SystemBuffer);
			status = handle_base_request(req);
			bytes_returned = sizeof(_base);
		}
		else
		{
			status = STATUS_INFO_LENGTH_MISMATCH;
			bytes_returned = 0;
		}
	}

	irp->IoStatus.Status = status;
	irp->IoStatus.Information = bytes_returned;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return status;
}