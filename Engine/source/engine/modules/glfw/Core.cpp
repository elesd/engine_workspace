#include <stdafx.h>
#if ENGINE_USE_GLFW
#include <engine/modules/glfw/Core.h>
/////////////////////////////////////////////////////

#include <GLFW/glfw3.h>

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

			int res = glfwInit();
			glfwSetErrorCallback(onError);
			return res == GL_TRUE;
		}
	}
}
#else 

#include <engine/modules/glfw/empty/Core.cpp>

#endif
