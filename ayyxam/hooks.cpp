#include "hooks.hpp"
#include "global.hpp"

ayyxam::hooks::nt_query_system_information_t ayyxam::hooks::original_nt_query_system_information = nullptr;
ayyxam::hooks::get_adapters_addresses_t ayyxam::hooks::original_get_adapters_addresses = nullptr;
ayyxam::hooks::bit_blt_t ayyxam::hooks::original_bit_blt = nullptr;
ayyxam::hooks::get_property_value_t ayyxam::hooks::original_get_property_value = nullptr;



NTSTATUS WINAPI ayyxam::hooks::nt_query_system_information(SYSTEM_INFORMATION_CLASS system_information_class, PVOID system_information, ULONG system_information_length, PULONG return_length)
{
	// DONT HANDLE OTHER CLASSES
	if (system_information_class != SystemProcessInformation)
		return ayyxam::hooks::original_nt_query_system_information(
				system_information_class, system_information,
				system_information_length, return_length);

	ayyxam::global::console.log("NtQuerySystemInformation called");
	
	// HIDE PROCESSES
	const auto value = ayyxam::hooks::original_nt_query_system_information(
			system_information_class, system_information, 
			system_information_length, return_length);

	// DONT HANDLE UNSUCCESSFUL CALLS
	if (!NT_SUCCESS(value))
		return value;

	// DEFINE STRUCTURE FOR LIST
	struct SYSTEM_PROCESS_INFO
	{
		ULONG                   NextEntryOffset;
		ULONG                   NumberOfThreads;
		LARGE_INTEGER           Reserved[3];
		LARGE_INTEGER           CreateTime;
		LARGE_INTEGER           UserTime;
		LARGE_INTEGER           KernelTime;
		UNICODE_STRING          ImageName;
		ULONG                   BasePriority;
		HANDLE                  ProcessId;
		HANDLE                  InheritedFromProcessId;
	};

	// HELPER FUNCTION: GET NEXT ENTRY IN LINKED LIST
	auto get_next_entry = [](SYSTEM_PROCESS_INFO* entry)
	{
		return reinterpret_cast<SYSTEM_PROCESS_INFO*>(
			reinterpret_cast<std::uintptr_t>(entry) + entry->NextEntryOffset);
	};

	// ITERATE AND HIDE PROCESS
	auto entry = reinterpret_cast<SYSTEM_PROCESS_INFO*>(system_information);
	SYSTEM_PROCESS_INFO* previous_entry = nullptr;
	for (; entry->NextEntryOffset > 0x00; entry = get_next_entry(entry))
	{
		if (entry->ProcessId == reinterpret_cast<HANDLE>(7488) && previous_entry != nullptr)
		{
			// SKIP ENTRY
			previous_entry->NextEntryOffset += entry->NextEntryOffset;
		}

		// SAVE PREVIOUS ENTRY FOR SKIPPING
		previous_entry = entry;
	}


	return value;
}

ULONG WINAPI ayyxam::hooks::get_adapters_addresses(ULONG family, ULONG flags, PVOID reserved, PIP_ADAPTER_ADDRESSES adapter_addresses, PULONG size_pointer)
{
	ayyxam::global::console.log("GetAdaptersAddresses called");

	return ayyxam::hooks::original_get_adapters_addresses(family, flags, reserved, adapter_addresses, size_pointer);
}

BOOL __stdcall ayyxam::hooks::bit_blt(HDC hdc, int x, int y, int cx, int cy, HDC hdc_src, int x1, int y1, DWORD rop)
{
	ayyxam::global::console.log("BitBlt called");

	return ayyxam::hooks::original_bit_blt(hdc, x, y, cx, cy, hdc_src, x1, y1, rop);
}

std::int32_t __stdcall ayyxam::hooks::get_property_value(void* handle, std::int32_t property_id, void* value)
{
	ayyxam::global::console.log("RawUiaGetPropertyValue called");

	return ayyxam::hooks::original_get_property_value(handle, property_id, value);
}
