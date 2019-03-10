#pragma once
#include <string>
#include <string_view>
#include <iostream>

namespace io
{
	class logger
	{
	public:
		inline logger() noexcept
		{
			// ALLOC CONSOLE FOR DEBUG OUTPUT
			//AllocConsole();

			// REDIRECT CONSOLE OUTPUT TO CONSOLE
#pragma warning(push)
#pragma warning(disable:4996)
			//freopen("CONOUT$", "w", stdout);
#pragma warning(pop)

			// SET CONSOLE TITLE
			//SetConsoleTitleW(L"[AYYXAM]");
		}

		inline ~logger() noexcept
		{
			// FREE THE CONSOLE
			//ShowWindow(GetConsoleWindow(), SW_HIDE);
			//FreeConsole();
		}

		inline void log(const std::string_view message) const noexcept
		{
			std::cout << "[+] " << message << std::endl;
		}

		inline void log_error(const std::string_view message) const noexcept
		{
			std::cout << "[!] " << message << std::endl;
		}

		template <bool hexadecimal = false, class T>
		void log_formatted(const std::string_view identifier, const T& value) const noexcept
		{
			std::cout << "[?] " << identifier << ": ";

			if constexpr (hexadecimal)
				std::cout << std::hex;

			std::cout << value << std::endl;

			if constexpr (hexadecimal)
				std::cout << std::dec;
		}

		inline void get_line(const std::string_view message, std::string& value)
		{
			std::cout << "[I] " << message << ": ";

			std::getline(std::cin, value);
		}

		template <class T>
		inline void get_input(const std::string_view message, T& value)
		{
			std::cout << "[I] " << message << ": ";

			std::cin >> value;
		}
	};
}
