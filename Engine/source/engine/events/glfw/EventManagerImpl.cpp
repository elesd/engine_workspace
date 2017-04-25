#include <stdafx.h>
#include <engine/events/glfw/EventManagerImpl.h>

#if ENGINE_USE_GLFW
#include <engine/app/Application.h>

#include <engine/events/glfw/MouseImpl.h>
#include <engine/events/glfw/KeyboardImpl.h>
#include <engine/events/glfw/EventManagerImpl.h>
#include <engine/events/EventManager.h>
#include <engine/view/glfw/WindowManagerImpl.h>

#include <engine/Context.h>

namespace engine
{
	namespace glfw
	{
		void EventManagerImpl::mouseMovedCallback(GLFWwindow* window, double xpos, double ypos)
		{
			Application *app = Context::getInstance()->getApplication();
			WindowManagerImpl *windowManager = static_cast<WindowManagerImpl*>(app->getWindowManager());
			WindowImpl *window = windowManager->findWindow(window);
			ASSERT(window);
			std::vector<glfw::MouseImpl*> sources = window->getEventManager()->findEventSource<glfw::MouseImpl>();
			if(!sources.empty())
			{
				sources[0]->handleMoveEvent(float(xpos), float(ypos));
			}
		}
		void EventManagerImpl::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			Application *app = Context::getInstance()->getApplication();
			WindowManagerImpl *windowManager = static_cast<WindowManagerImpl*>(app->getWindowManager());
			WindowImpl *window = windowManager->findWindow(window);
			ASSERT(window);
			std::vector<glfw::MouseImpl*> sources = window->getEventManager()->findEventSource<glfw::MouseImpl>();
			if(!sources.empty())
			{
				sources[0]->handleClickEvent(button, action, mods);
			}
		}

		void EventManagerImpl::mouseScrolledCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			Application *app = Context::getInstance()->getApplication();
			WindowManagerImpl *windowManager = static_cast<WindowManagerImpl*>(app->getWindowManager());
			WindowImpl *window = windowManager->findWindow(window);
			ASSERT(window);
			std::vector<glfw::MouseImpl*> sources = window->getEventManager()->findEventSource<glfw::MouseImpl>();
			if(!sources.empty())
			{
				sources[0]->handleScollEvent(float(xoffset), float(yoffset));
			}
		}
		void EventManagerImpl::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Application *app = Context::getInstance()->getApplication();
			WindowManagerImpl *windowManager = static_cast<WindowManagerImpl*>(app->getWindowManager());
			WindowImpl *window = windowManager->findWindow(window);
			ASSERT(window);
			std::vector<glfw::KeyboardImpl*> sources = window->getEventManager()->findEventSource<glfw::KeyboardImpl>();
			if(!sources.empty())
			{
				sources[0]->handleKeyEvent(key, scancode, action, mods);
			}
		}
	}
}
#endif