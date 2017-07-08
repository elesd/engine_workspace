#include <stdafx.h>

#if ENGINE_USE_GLFW == 0

#include <engine/modules/glfw/Core.h>
/////////////////////////////////////////////////////

namespace
{
	void onError(int error, const char *description)
	{
		std::cout << "[GLFW-ERROR] : Code {" << error << "} Description {" << description << "}" << std::endl;
	}
}

namespace engine
{
	namespace glfw
	{
		bool Core::init()
		{
			HARD_FAIL("Not active module");
			return false;
		}
	}
}
#endif
