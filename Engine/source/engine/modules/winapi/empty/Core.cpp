#include <stdafx.h>
#if ENGINE_USE_WINAPI == 0
#include <engine/modules/winapi/Core.h>
/////////////////////////////////////////////////////


namespace engine
{
	namespace winapi
	{
		bool Core::init()
		{
			HARD_ASSERT("Inactive module");
			return false;
		}
	}
}
#endif