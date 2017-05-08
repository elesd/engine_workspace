#include <stdafx.h>
#include <engine/events/glfw/EventManagerImpl.h>

#if !ENGINE_USE_GLFW

namespace engine
{
	namespace glfw
	{
		void EventManagerImpl::mouseMovedCallback(GLFWwindow* , double , double )
		{
			HARD_FAIL("Inactive module");
		}
		void EventManagerImpl::mouseButtonCallback(GLFWwindow*, int , int , int )
		{
			HARD_FAIL("Inactive module");
		}

		void EventManagerImpl::mouseScrolledCallback(GLFWwindow* , double , double )
		{
			HARD_FAIL("Inactive module");
		}
		void EventManagerImpl::keyboardCallback(GLFWwindow* , int , int , int , int )
		{
			HARD_FAIL("Inactive module");
		}
	}
}
#endif
