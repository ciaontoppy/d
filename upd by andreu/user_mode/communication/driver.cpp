#include "driver.hpp"

HANDLE driver_handle = INVALID_HANDLE_VALUE;
INT32 process_id = 0;
uintptr_t virtaddrxd = 0;

bool ioio::initalize()
{
	driver_handle = CreateFileW(L"\\\\.\\\{SerCx}", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (!driver_handle || (driver_handle == INVALID_HANDLE_VALUE))
	{
		return false;
	}

	return true;
}

void ioio::read_physical(PVOID address, PVOID buffer, DWORD size)
{
	_read args = { 0 };
	args.security = code_security;
	args.address = (ULONGLONG)address;
	args.buffer = (ULONGLONG)buffer;
	args.size = size;
	args.process_id = process_id;

	DeviceIoControl(driver_handle, code_read, &args, sizeof(args), nullptr, 0, 0, 0);
}

uintptr_t ioio::find_image()
{
	uintptr_t image_address = { 0 };
	_base args = { 0 };
	args.security = code_security;
	args.process_id = process_id;
	args.address = (ULONGLONG*)&image_address;

	DeviceIoControl(driver_handle, code_base, &args, sizeof(args), nullptr, 0, 0, 0);

	return image_address;
}

bool ioio::find_dir_base()
{
	bool ret = false;
	_dirbase args = { 0 };
	args.process_id = process_id;
	args.operation = (bool*)&ret;

	DeviceIoControl(driver_handle, code_dirbase_fix, &args, sizeof(args), nullptr, 0, 0, 0);

	return ret;
}

INT32 ioio::find_process(LPCTSTR process_name)
{
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hsnap, &pt))
	{
		do
		{
			if (!lstrcmpi(pt.szExeFile, process_name))
			{
				CloseHandle(hsnap);
				process_id = pt.th32ProcessID;

				return pt.th32ProcessID;
			}
		} while (Process32Next(hsnap, &pt));
	}

	CloseHandle(hsnap);

	return { 0 };
}