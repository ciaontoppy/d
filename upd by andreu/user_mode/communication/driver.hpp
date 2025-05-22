#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

#define code_dirbase_fix CTL_CODE(FILE_DEVICE_UNKNOWN, 0x460B, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_read CTL_CODE(FILE_DEVICE_UNKNOWN, 0x461B, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_base CTL_CODE(FILE_DEVICE_UNKNOWN, 0x462B, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_security 0x4C21433

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

extern HANDLE driver_handle;
extern INT32 process_id;
extern uintptr_t virtaddrxd;

class ioio
{
public:
	bool initalize();
	void read_physical(PVOID address, PVOID buffer, DWORD size);
	uintptr_t find_image();
	bool find_dir_base();
	INT32 find_process(LPCTSTR process_name);

	template <typename T>
	T read(uint64_t address)
	{
		T buffer{ };
		read_physical((PVOID)address, &buffer, sizeof(T));

		return buffer;
	}
};
inline ioio* io;