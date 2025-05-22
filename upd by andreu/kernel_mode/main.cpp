#include "requests.hpp"

NTSTATUS unsupported_dispatch(PDEVICE_OBJECT device_obj, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_obj);

	irp->IoStatus.Status = STATUS_NOT_SUPPORTED;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return irp->IoStatus.Status;
}

NTSTATUS dispatch_handler(PDEVICE_OBJECT device_obj, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_obj);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);

	switch (stack->MajorFunction)
	{
	case IRP_MJ_CREATE:
	case IRP_MJ_CLOSE:
		break;
	default:
		break;
	}

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	
	return irp->IoStatus.Status;
}

void unload_driver(PDRIVER_OBJECT driver_obj)
{
	NTSTATUS status = {};
	status = IoDeleteSymbolicLink(&symbolic_link_name);

	if (!NT_SUCCESS(status)) return;

	IoDeleteDevice(driver_obj->DeviceObject);
}

NTSTATUS initalize_driver(PDRIVER_OBJECT driver_obj, PUNICODE_STRING reg_path)
{
	UNREFERENCED_PARAMETER(reg_path);

	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT device_obj = NULL;

	RtlInitUnicodeString(&driver_name, L"\\Device\\{SerCx}");
	RtlInitUnicodeString(&symbolic_link_name, L"\\DosDevices\\{SerCx}");

	status = IoCreateDevice(driver_obj, 0, &driver_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device_obj);
	if (!NT_SUCCESS(status))
	{
		return status;
	}

	status = IoCreateSymbolicLink(&symbolic_link_name, &driver_name);
	if (!NT_SUCCESS(status))
	{
		IoDeleteDevice(device_obj);
		return status;
	}

	for (int i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		driver_obj->MajorFunction[i] = &unsupported_dispatch;
	}

	driver_obj->MajorFunction[IRP_MJ_CREATE] = &dispatch_handler;
	driver_obj->MajorFunction[IRP_MJ_CLOSE] = &dispatch_handler;
	driver_obj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = &io_control_handler;
	driver_obj->DriverUnload = &unload_driver;

	device_obj->Flags |= DO_BUFFERED_IO;
	device_obj->Flags &= ~DO_DEVICE_INITIALIZING;

	return status;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	return IoCreateDriver(NULL, &initalize_driver);
}