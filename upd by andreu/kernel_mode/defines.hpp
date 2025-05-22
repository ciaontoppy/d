#pragma once
#include <ntifs.h>
#include <windef.h>
#include <intrin.h>
#include "low.hpp"

#define code_dirbase_fix CTL_CODE(FILE_DEVICE_UNKNOWN, 0x460B, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_read CTL_CODE(FILE_DEVICE_UNKNOWN, 0x461B, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_base CTL_CODE(FILE_DEVICE_UNKNOWN, 0x462B, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_security 0x4C21433

#define PAGE_OFFSET_SIZE 12
#define Win1803 17134
#define Win1809 17763
#define Win1903 18362
#define Win1909 18363
#define Win2004 19041
#define Win20H2 19569
#define Win21H1 20180

static const UINT64 PMASK = (~0xfull << 8) & 0xfffffffffull;

UNICODE_STRING driver_name;
UNICODE_STRING symbolic_link_name;
ULONGLONG m_stored_dtb;

typedef struct _SystemBigpoolEntry {
    PVOID VirtualAddress;
    ULONG_PTR NonPaged : 1;
    ULONG_PTR SizeInBytes;
    UCHAR Tag[4];
} SystemBigpoolEntry, * PSystemBigpoolEntry;

typedef struct _SystemBigpoolInformation {
    ULONG Count;
    SystemBigpoolEntry AllocatedInfo[1];
} SystemBigpoolInformation, * PSystemBigpoolInformation;

typedef enum _SystemInformationClass {
    SystemBigpoolInformationClass = 0x42,
} SystemInformationClass;

extern "C" NTSTATUS NTAPI IoCreateDriver(PUNICODE_STRING DriverName, PDRIVER_INITIALIZE InitializationFunction);
extern "C" PVOID NTAPI PsGetProcessSectionBaseAddress(PEPROCESS Process);
extern "C" NTSTATUS NTAPI ZwQuerySystemInformation(SystemInformationClass systemInformationClass, PVOID systemInformation, ULONG systemInformationLength, PULONG returnLength);

typedef struct _dirbase {
	INT32 process_id;
	bool* operation;
} dirbase, * p_dirbase;

typedef struct _read {
	INT32 security;
	INT32 process_id;
	ULONGLONG address;
	ULONGLONG buffer;
	ULONGLONG size;
} read, * p_read;

typedef struct _base {
	INT32 security;
	INT32 process_id;
	ULONGLONG* address;
} base, * p_base;

ULONG64 find_min(INT32 a, SIZE_T b)
{
	INT32 BInt = (INT32)b;

	return (((a) < (BInt)) ? (a) : (BInt));
}