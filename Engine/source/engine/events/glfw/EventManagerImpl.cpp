#include <stdafx.h>
#include <engine/events/glfw/EventManagerImpl.h>

#if ENGINE_USE_GLFW
#include <engine/app/Application.h>

#include <engine/events/glfw/MouseImpl.h>
#include <engine/events/glfw/KeyboardImpl.h>
#include <engine/events/glfw/EventManagerImpl.h>
#include <engine/events/EventManager.h>
#include <engine/view/glfw/WindowManagerImpl.h>
#include <engine/view/glfw/WindowImpl.h>

#include <engine/Context.h>

namespace engine
{
	namespace glfw
	{
		void EventManagerImpl::mouseMovedCallback(WindowImpl* window, double xpos, double ypos)
		{
			std::vector<MouseImpl*> sources = window->getEventManager()->findEventSource<MouseImpl>();
			if(!sources.empty())
			{
				sources[0]->handleMoveEvent(float(xpos), float(ypos));
			}
			
		}
		void EventManagerImpl::mouseButtonCallback(WindowImpl* window, int button, int action, int mods)
		{
			std::vector<glfw::MouseImpl*> sources = window->getEventManager()->findEventSource<glfw::MouseImpl>();
			if(!sources.empty())
			{
				sources[0]->handleClickEvent(button, action, mods);
			}
		}

		void EventManagerImpl::mouseScrolledCallback(WindowImpl* window, double xoffset, double yoffset)
		{
			std::vector<glfw::MouseImpl*> sources = window->getEventManager()->findEventSource<glfw::MouseImpl>();
			if(!sources.empty())
			{
				sources[0]->handleScollEvent(float(xoffset), float(yoffset));
			}
		}

		void EventManagerImpl::keyboardCallback(WindowImpl* window, int key, int scancode, int action, int mods)
		{
			std::vector<glfw::KeyboardImpl*> sources = window->getEventManager()->findEventSource<glfw::KeyboardImpl>();
			if(!sources.empty())
			{
				sources[0]->handleKeyEvent(key, scancode, action, mods);
			}
		}

		void EventManagerImpl::windowClosedCallback(WindowImpl* window)
		{
			window->handleWindowClosedEvent();
		}

		void EventManagerImpl::windowResizedCallback(WindowImpl* window, int32_t width, int32_t height)
		{
			window->handleWindowResizedEvent(width, height);
		}

		void EventManagerImpl::windowMovedCallback(WindowImpl* window, int32_t x, int32_t y)
		{
			window->handleWindowMovedEvent(x, y);
		}

		void EventManagerImpl::windowFocusCallback(WindowImpl* window, int32_t focused)
		{
			window->handleWindowFocusEvent(focused);
		}

		void EventManagerImpl::windowFrameBufferResizeCallback(WindowImpl* window, int32_t width, int32_t height)
		{
			window->handleWindowFrameBufferResizeEvent(width, height);
		}
	}
}

#endif
