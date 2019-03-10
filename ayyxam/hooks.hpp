#pragma once

#include <winsock2.h>
#include <iphlpapi.h>

#include <windows.h>
#include <winternl.h>

#include <cstdint>

namespace ayyxam::hooks
{
	// ntdll!NtQuerySystemInformation
	using nt_query_system_information_t = NTSTATUS(WINAPI*)(SYSTEM_INFORMATION_CLASS system_information_class, PVOID system_information, ULONG system_information_length, PULONG return_length);

	extern NTSTATUS WINAPI nt_query_system_information(SYSTEM_INFORMATION_CLASS system_information_class, PVOID system_information, ULONG system_information_length, PULONG return_length);
	extern nt_query_system_information_t original_nt_query_system_information;

	// iphlpapi!GetAdaptersAddresses
	using get_adapters_addresses_t = ULONG(WINAPI*)(ULONG family, ULONG flags, PVOID reserved, PIP_ADAPTER_ADDRESSES adapter_addresses, PULONG size_pointer);

	extern ULONG WINAPI get_adapters_addresses(ULONG family, ULONG flags, PVOID reserved, PIP_ADAPTER_ADDRESSES adapter_addresses, PULONG size_pointer);
	extern get_adapters_addresses_t original_get_adapters_addresses;

	// gdi32!BitBlt
	using bit_blt_t = BOOL(WINAPI*)(HDC hdc, int x, int y, int cx, int cy, HDC hdc_src, int x1, int y1, DWORD rop);

	extern BOOL WINAPI bit_blt(HDC hdc, int x, int y, int cx, int cy, HDC hdc_src, int x1, int y1, DWORD rop);
	extern bit_blt_t original_bit_blt;


	// UIAutomationCore!RawUiaGetPropertyValue
	using get_property_value_t = std::int32_t(WINAPI*)(void* handle, std::int32_t property_id, void* value);

	extern std::int32_t WINAPI get_property_value(void* handle, std::int32_t property_id, void* value);
	extern get_property_value_t original_get_property_value;
}