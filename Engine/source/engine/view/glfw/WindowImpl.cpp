#include <stdafx.h>
#if ENGINE_USE_GLFW
#include <engine/view/glfw/WindowImpl.h>
/////////////////////////////////////////
#include <GLFW/glfw3.h>

#include <engine/Context.h>
#include <engine/app/Application.h>
#include <engine/events/glfw/EventManagerImpl.h>
#include <engine/view/glfw/WindowManagerImpl.h>

namespace engine
{
	namespace glfw
	{
		struct WindowImplPrivate
		{
			GLFWwindow *window = nullptr;
			std::string title;
		};

		WindowImpl::WindowImpl(WindowManager *windowManager, GLFWwindow *window, const WindowParameter &parameters, const std::string &title)
			: Window(windowManager, parameters),
			_members(new WindowImplPrivate())
		{
			_members->window = window;
			_members->title = title;
			_parameters = parameters;

			ASSERT(_members->window != nullptr);
			glfwSetWindowPos(_members->window, _parameters.x, _parameters.y);
			glfwSetWindowSize(_members->window, _parameters.width, _parameters.height);

		}

		WindowImpl::WindowImpl(WindowManager *windowManager, GLFWwindow *window, const std::string &title)
			: Window(windowManager),
			_members(new WindowImplPrivate())
		{
			_members->window = window;
			_members->title = title;
		}

		WindowImpl::~WindowImpl()
		{
			if(_members && _members->window)
			{
				glfwDestroyWindow(_members->window);
			}
			delete _members;
		}

		WindowImpl::operator bool() const
		{
			return _members->window != nullptr;
		}

		void WindowImpl::setPositionImp(int32_t x, int32_t y)
		{
			ASSERT(_members->window != nullptr);
			glfwSetWindowPos(_members->window, x, y);

		}

		void WindowImpl::setWidthImpl(uint32_t width)
		{
			ASSERT(_members->window != nullptr);
			glfwSetWindowSize(_members->window, width, _parameters.height);
		}

		void WindowImpl::setHeightImpl(uint32_t height)
		{
			ASSERT(_members->window != nullptr);
			glfwSetWindowSize(_members->window, _parameters.width, height);
		}

		void WindowImpl::setSizeImpl(uint32_t width, uint32_t height)
		{
			ASSERT(_members->window != nullptr);
			glfwSetWindowSize(_members->window, width, height);
		}

		GLFWwindow *WindowImpl::getGlfwWindow()
		{
			return _members->window;
		}

		void WindowImpl::handleWindowClosedEvent()
		{
			windowClosed.emit();
			getWindowManager()->windowClosed(this);
		}

		void WindowImpl::handleWindowResizedEvent(int32_t width, int32_t height)
		{
			windowSizeChanged.emit(width, height);
		}

		void WindowImpl::handleWindowMovedEvent(int32_t x, int32_t y)
		{
			windowMoved.emit(x, y);
		}

		void WindowImpl::handleWindowFocusEvent(int32_t focused)
		{
			if(focused == GLFW_TRUE)
			{
				windowInFocus.emit();
			}
			else
			{
				windowOutFocus.emit();
			}
		}

		void WindowImpl::handleWindowFrameBufferResizeEvent(int32_t width, int32_t height)
		{
			windowFrameBufferSizeChanged.emit(width, height);
		}
	}
}

#endif
