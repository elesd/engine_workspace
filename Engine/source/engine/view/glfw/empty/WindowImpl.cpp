#include <stdafx.h>
#if ENGINE_USE_GLFW == 0
#include <engine/view/glfw/WindowImpl.h>
/////////////////////////////////////////

namespace engine
{
	namespace glfw
	{
		WindowImpl::WindowImpl(WindowManager *windowManager, GLFWwindow *, const WindowParameter &, const std::string &)
			: Window(windowManager)
		{
			HARD_FAIL("Not active module");
		}

		WindowImpl::WindowImpl(WindowManager *windowManager, GLFWwindow *, const std::string &)
			: Window(windowManager)
		{
			HARD_FAIL("Not active module");
		}

		WindowImpl::~WindowImpl()
		{
			HARD_FAIL("Not active module");
		}

		WindowImpl::operator bool() const
		{
			HARD_FAIL("Not active module");
			return false;
		}

		void WindowImpl::setPositionImp(int32_t, int32_t)
		{
			HARD_FAIL("Not active module");
		}

		void WindowImpl::setWidthImpl(uint32_t)
		{
			HARD_FAIL("Not active module");
		}

		void WindowImpl::setHeightImpl(uint32_t)
		{
			HARD_FAIL("Not active module");
		}

		void WindowImpl::setSizeImpl(uint32_t, uint32_t)
		{
			HARD_FAIL("Not active module");
		}

		GLFWwindow *WindowImpl::getGlfwWindow()
		{
			HARD_FAIL("Not active module");
			return nullptr;
		}
	}
}
#endif