#include <stdafx.h>
#include <engine/view/Console.h>

namespace engine
{
	void Console::printImpl(const std::string& str) const
	{
		std::cout << str << std::flush;
	}

}