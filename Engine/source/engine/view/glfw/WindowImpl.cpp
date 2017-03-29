#include <stdafx.h>
#if ENGINE_USE_GLFW
#include <engine/view/glfw/WindowImpl.h>
/////////////////////////////////////////
#include <GLFW/glfw3.h>

namespace engine
{
	namespace glfw
	{
		struct WindowImplPrivate
		{
			GLFWwindow *window = nullptr;
			std::string title;
		};

		WindowImpl::WindowImpl(GLFWwindow *window, const WindowParameter &parameters, const std::string &title)
			: Window(parameters),
			_members(new WindowImplPrivate())
		{
			_members->window = window;
			_members->title = title;
			_parameters = parameters;

			ASSERT(_members->window != nullptr);
			glfwSetWindowPos(_members->window, _parameters.x, _parameters.y);
			glfwSetWindowSize(_members->window, _parameters.width, _parameters.height);

		}

		WindowImpl::WindowImpl(GLFWwindow *window, const std::string &title)
			: Window(),
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

	}
}
#endif