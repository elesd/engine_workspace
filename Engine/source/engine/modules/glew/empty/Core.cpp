#include <stdafx.h>

#if ENGINE_USE_GLEW == 0

#include <engine/modules/glew/Core.h>
/////////////////////////////////////////////////////


namespace engine
{
	namespace glew
	{
		bool Core::init()
		{
			HARD_FAIL("Not active module");
			return false;
		}

		bool Core::initOpenglContext()
		{
			HARD_FAIL("Not active module");
			return false;
		}

	}
}
#endif
