#include <stdafx.h>
#if ENGINE_USE_WINAPI
#include <engine/modules/winapi/Core.h>
/////////////////////////////////////////////////////


namespace engine
{
	namespace winapi
	{
		bool Core::init()
		{
			return true;
		}
	}
}
#else 

#include <engine/modules/winapi/empty/Core.cpp>

#endif