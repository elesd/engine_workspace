#include <stdafx.h>
#include <engine/app/glfw/ApplicationImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLFW

#include <engine/app/IMain.h>
#include <engine/app/IApplicationParameter.h>

#include <engine/events/glfw/EventManagerImpl.h>
#include <engine/events/glfw/MouseImpl.h>
#include <engine/events/glfw/KeyboardImpl.h>

#include <engine/view/glfw/WindowManagerImpl.h>
#include <engine/view/glfw/WindowImpl.h>

#include <engine/Context.h>

#include <GLFW/glfw3.h>

namespace engine
{
	namespace glfw
	{
		ApplicationImpl::ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
			:Application(std::move(arguments), std::move(main))
		{
		}

		void ApplicationImpl::updateImpl()
		{
			glfwPollEvents();
		}

		std::pair<EventManagerImpl*, WindowImpl*> ApplicationImpl::findHandlersForWindow(GLFWwindow* glfwWindow)
		{
			ApplicationImpl* app = static_cast<ApplicationImpl*>(Context::application());
			WindowManagerImpl* windowManager = static_cast<WindowManagerImpl*>(app->getWindowManager());
			WindowImpl* window = windowManager->findWindow(glfwWindow);
			ASSERT(window);
			EventManagerImpl* eventManager = static_cast<EventManagerImpl*>(window->getEventManager());

			return std::make_pair(eventManager, window);
		}


		void ApplicationImpl::mouseMovedCallback(GLFWwindow* glfwWindow, double xpos, double ypos)
		{
			EventManagerImpl* eventManager = nullptr;
			WindowImpl* window = nullptr;
			std::tie(eventManager, window) = findHandlersForWindow(glfwWindow);

			eventManager->mouseMovedCallback(window, xpos, ypos);
		}

		void ApplicationImpl::mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
		{
			EventManagerImpl* eventManager = nullptr;
			WindowImpl* window = nullptr;
			std::tie(eventManager, window) = findHandlersForWindow(glfwWindow);

			eventManager->mouseButtonCallback(window, button, action, mods);
		}

		void ApplicationImpl::mouseScrolledCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset)
		{
			EventManagerImpl* eventManager = nullptr;
			WindowImpl* window = nullptr;
			std::tie(eventManager, window) = findHandlersForWindow(glfwWindow);

			eventManager->mouseScrolledCallback(window, xoffset, yoffset);
		}

		void ApplicationImpl::keyboardCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
		{
			EventManagerImpl* eventManager = nullptr;
			WindowImpl* window = nullptr;
			std::tie(eventManager, window) = findHandlersForWindow(glfwWindow);

			eventManager->keyboardCallback(window, key, scancode, action, mods);
		}

		void ApplicationImpl::windowClosedCallback(GLFWwindow* glfwWindow)
		{
			EventManagerImpl* eventManager = nullptr;
			WindowImpl* window = nullptr;
			std::tie(eventManager, window) = findHandlersForWindow(glfwWindow);

			eventManager->windowClosedCallback(window);
		}

		void ApplicationImpl::windowResizedCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height)
		{
			EventManagerImpl* eventManager = nullptr;
			WindowImpl* window = nullptr;
			std::tie(eventManager, window) = findHandlersForWindow(glfwWindow);

			eventManager->windowResizedCallback(window, width, height);
		}

		void ApplicationImpl::windowMovedCallback(GLFWwindow* glfwWindow, int32_t x, int32_t y)
		{
			EventManagerImpl* eventManager = nullptr;
			WindowImpl* window = nullptr;
			std::tie(eventManager, window) = findHandlersForWindow(glfwWindow);

			eventManager->windowMovedCallback(window, x, y);
		}

		void ApplicationImpl::windowFocusCallback(GLFWwindow* glfwWindow, int32_t focused)
		{
			EventManagerImpl* eventManager = nullptr;
			WindowImpl* window = nullptr;
			std::tie(eventManager, window) = findHandlersForWindow(glfwWindow);

			eventManager->windowFocusCallback(window, focused);
		}

		void ApplicationImpl::windowFrameBufferResizeCallback(GLFWwindow* glfwWindow, int32_t width, int32_t height)
		{
			EventManagerImpl* eventManager = nullptr;
			WindowImpl* window = nullptr;
			std::tie(eventManager, window) = findHandlersForWindow(glfwWindow);

			eventManager->windowFrameBufferResizeCallback(window, width, height);
		}

	}
}

#endif

