#pragma once

namespace ayyxam
{
	class handler
	{
	public:
		handler() noexcept = default;
		~handler() noexcept = default;

		void initialise() noexcept;
		void release() noexcept;

		void handle_input() noexcept;

	private:

	};
}
