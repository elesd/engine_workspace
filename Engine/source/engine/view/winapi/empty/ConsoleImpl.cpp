#include <stdafx.h>
#include <engine/view/winapi/ConsoleImpl.h>

#if ENGINE_USE_WINAPI == 0

namespace engine
{
	namespace winapi
	{
		void ConsoleImpl::printImpl(const std::string& str) const
		{
			INACTIVE_MODULE_ERROR();
		}
	}
}


#endif