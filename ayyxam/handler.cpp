#include "handler.hpp"
#include "hooks.hpp"
#include "global.hpp"

#include "Minhook/include/MinHook.h"

#include <windows.h>
#include <winternl.h>

void ayyxam::handler::initialise() noexcept
{
	ayyxam::global::console.log("AYYXAM LOADED");

	// HANDLE SETTINGS
	// this->handle_input();

	// SETUP HOOKS
	ayyxam::global::console.log("Initialising MinHook...");

	MH_Initialize();

	ayyxam::global::console.log("Initialised MinHook..!");

	// PROCESS LIST HOOK
	ayyxam::global::console.log("Hooking NtQuerySystemInformation");
	MH_CreateHook(
		NtQuerySystemInformation, 
		ayyxam::hooks::nt_query_system_information, 
		reinterpret_cast<void**>(&ayyxam::hooks::original_nt_query_system_information));
	
	MH_EnableHook(NtQuerySystemInformation);
	
	// NETWORK ADAPTER HOOK
	ayyxam::global::console.log("Hooking GetAdaptersAddresses");
	MH_CreateHook(
		GetAdaptersAddresses, 
		ayyxam::hooks::get_adapters_addresses, 
		reinterpret_cast<void**>(&ayyxam::hooks::original_get_adapters_addresses));
	
	MH_EnableHook(GetAdaptersAddresses);
	
	// SCREENSHOT HOOK
	ayyxam::global::console.log("Hooking BitBlt");
	MH_CreateHook(
		BitBlt, 
		ayyxam::hooks::bit_blt, 
		reinterpret_cast<void**>(&ayyxam::hooks::original_bit_blt));
	
	MH_EnableHook(BitBlt);
	
	// CREATE PROCESS HOOK (ExamCookie SPECIFIC)
	ayyxam::global::console.log("Hooking CreateProcess");
	MH_CreateHook(CreateProcess, 
		ayyxam::hooks::create_process, 
		reinterpret_cast<void**>(&ayyxam::hooks::original_create_process));
	
	MH_EnableHook(CreateProcess);
	
	// WEBSITE LIST HOOK
	ayyxam::global::console.log("Hooking UiaGetPropertyValue");
	const auto automation_handle = GetModuleHandle(L"UIAutomationCore.dll");
	const auto get_property_value_function = GetProcAddress(automation_handle, "UiaGetPropertyValue");
	
	ayyxam::global::console.log_formatted<true>("Automation handle", automation_handle);
	ayyxam::global::console.log_formatted<true>("GetPropertyValue", get_property_value_function);
	
	MH_CreateHook(
		get_property_value_function,
		ayyxam::hooks::get_property_value,
		reinterpret_cast<void**>(&ayyxam::hooks::original_get_property_value));
	
	MH_EnableHook(get_property_value_function);


	// CLIPBOARD HOOK
	ayyxam::global::console.log("Hooking ole32.dll!OleGetClipboard");
	const auto ole_handle = GetModuleHandle(L"ole32.dll");
	const auto get_clipboard_function = GetProcAddress(ole_handle, "OleGetClipboard");

	MH_CreateHook(
		get_clipboard_function,
		ayyxam::hooks::get_clipboard,
		reinterpret_cast<void**>(&ayyxam::hooks::original_get_clipboard));

	MH_EnableHook(get_clipboard_function);

}

void ayyxam::handler::release() noexcept
{
	// DISABLE HOOKS
	const auto automation_handle = GetModuleHandle(L"UIAutomationCore.dll");
	const auto ole_handle = GetModuleHandle(L"ole32.dll");

	const auto get_property_value_function = GetProcAddress(automation_handle, "UiaGetPropertyValue");
	const auto get_clipboard_function = GetProcAddress(ole_handle, "OleGetClipboard");


	MH_DisableHook(NtQuerySystemInformation);
	MH_DisableHook(GetAdaptersAddresses);
	MH_DisableHook(BitBlt);
	MH_DisableHook(CreateProcess);
	MH_DisableHook(get_property_value_function);
	MH_DisableHook(get_clipboard_function);
}

void ayyxam::handler::handle_input() noexcept
{
	ayyxam::global::console.log("Please input settings, marked as [I]");


	// HIDDEN PROCESS IDS
	std::string process_id_list;
	ayyxam::global::console.get_input("Process id list (comma seperated)", process_id_list);


	ayyxam::global::console.log_formatted("Ids", process_id_list);

	// HIDDEN WINDOW NAMES


}
