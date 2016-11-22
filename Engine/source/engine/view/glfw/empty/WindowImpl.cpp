#include "stdafx.h"
#if ENGINE_USE_GLFW == 0
#include "engine/view/glfw/WindowImpl.h"
/////////////////////////////////////////

namespace engine
{
	namespace view
	{
		namespace glfw
		{
			WindowImpl::WindowImpl(GLFWwindow *, const view::WindowParameter &, const std::string &)
				: view::Window()
			{
				HARD_FAIL("Not active module");
			}

			WindowImpl::WindowImpl(GLFWwindow *, const std::string &)
				: view::Window()
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
}
#endif