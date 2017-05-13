#include <stdafx.h>
#if ENGINE_USE_SDL == 0
#include <engine/modules/sdl/Core.h>
/////////////////////////////////////////////////////


namespace engine
{
	namespace sdl
	{
		bool Core::init()
		{
			HARD_ASSERT("Inactive module");
			return false;
		}
	}
}
#endif