#include <stdafx.h>
#include <engine/view/winapi/ConsoleImpl.h>

#if ENGINE_USE_WINAPI

namespace engine
{
	namespace winapi
	{
		void ConsoleImpl::printImpl(const std::string& str) const
		{
			OutputDebugString(str.c_str());
		}
	}
}

#else

#include <engine/view/winapi/empty/ConsoleImpl.cpp>

#endif