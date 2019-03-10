#pragma once
#include "handler.hpp"
#include "logger.hpp"

namespace ayyxam::global
{
	static ayyxam::handler instance;
	static io::logger console;
}