#include <windows.h>
#include <cstdint>

#include "global.hpp"

std::int32_t WINAPI DllMain(void* library_handle[[maybe_unused]], std::uint32_t reason, void* reserved[[maybe_unused]])
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		ayyxam::global::instance.initialise();
		break;

	case DLL_PROCESS_DETACH:
		ayyxam::global::instance.release();
		break;
	}

	return 1;
}