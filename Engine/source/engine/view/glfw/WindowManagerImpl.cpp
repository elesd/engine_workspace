#include <stdafx.h>
#include <engine/view/glfw/WindowManagerImpl.h>
///////////////////////////////////////////////////
#if ENGINE_USE_GLFW

#include <engine/events/glfw/EventManagerImpl.h>
#include <engine/view/glfw/WindowImpl.h>
#include <engine/video/glfw/DriverImpl.h>

#include <GLFW/glfw3.h>

#include <engine/video/Driver.h>

namespace
{
	void registerInputCallbacks(GLFWwindow *window)
	{
		glfwSetCursorPosCallback(window, engine::glfw::EventManagerImpl::mouseMovedCallback);
		glfwSetMouseButtonCallback(window, engine::glfw::EventManagerImpl::mouseButtonCallback);
		glfwSetScrollCallback(window, engine::glfw::EventManagerImpl::mouseScrolledCallback);
		glfwSetKeyCallback(window, engine::glfw::EventManagerImpl::keyboardCallback);
		glfwSetWindowCloseCallback(window, engine::glfw::WindowImpl::windowClosedCallback);
		glfwSetWindowFocusCallback(window, engine::glfw::WindowImpl::windowFocusCallback);
		glfwSetWindowSizeCallback(window, engine::glfw::WindowImpl::windowResizedCallback);
		glfwSetWindowPosCallback(window, engine::glfw::WindowImpl::windowMovedCallback);
		glfwSetFramebufferSizeCallback(window, engine::glfw::WindowImpl::windowFrameBufferResizeCallback);
	}
}

namespace engine
{
	namespace glfw
	{

		WindowImpl *WindowManagerImpl::findWindow(GLFWwindow *glfwWindow)
		{
			for(Window *window : getAllWindows())
			{
				WindowImpl *w = static_cast<WindowImpl*>(window);
				if(w->getGlfwWindow() == glfwWindow)
					return w;
			}
			return nullptr;
		}

		Window *WindowManagerImpl::createMainWindowImpl(const WindowParameter &parameters,
															  const std::string &title)
		{
			GLFWwindow *window(glfwCreateWindow(parameters.width, parameters.height, title.c_str(), NULL, NULL));
			std::unique_ptr<WindowImpl> result;
			if(window)
			{
				registerInputCallbacks(window);
				result.reset(new WindowImpl(this, std::move(window), parameters, title));
				glfwMakeContextCurrent(result->getGlfwWindow());
			}
			return result.release();
		}

		Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId)
		{
			int count = 0;
			GLFWmonitor** monitors = glfwGetMonitors(&count);
			std::unique_ptr<WindowImpl> result;
			if(monitorId < uint32_t(count))
			{
				GLFWwindow *window(glfwCreateWindow(width, height, title.c_str(), monitors[monitorId], NULL));
				if(window)
				{
					registerInputCallbacks(window);
					result.reset(new WindowImpl(this, window, title));
					glfwMakeContextCurrent(result->getGlfwWindow());
				}
			}
			return result.release();
		}

		Window *WindowManagerImpl::createSecondaryWindowImpl(const WindowParameter &parameters,
																   const std::string &title,
																   Window *mainWindow)
		{
			WindowImpl *glfMainWindow = static_cast<WindowImpl*>(mainWindow);
			GLFWwindow *window(glfwCreateWindow(parameters.width, parameters.height, title.c_str(), NULL, glfMainWindow->getGlfwWindow()));
			std::unique_ptr<WindowImpl> result;
			if(window)
			{
				registerInputCallbacks(window);
				result.reset(new WindowImpl(this, std::move(window), parameters, title));
			}
			return result.release();
		}

		Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow)
		{
			int count = 0;
			GLFWmonitor** monitors = glfwGetMonitors(&count);
			std::unique_ptr<WindowImpl> result;
			if(monitorId < uint32_t(count))
			{
				WindowImpl *glfMainWindow = static_cast<WindowImpl*>(mainWindow);
				GLFWwindow *window(glfwCreateWindow(width, height, title.c_str(), monitors[monitorId], glfMainWindow->getGlfwWindow()));
				if(window)
				{
					registerInputCallbacks(window);
					result.reset(new WindowImpl(this, window, title));
				}
			}
			return result.release();
		}

		uint32_t WindowManagerImpl::getMonitorCount() const
		{
			int count = 0;
			glfwGetMonitors(&count);
			return count;
		}

		uint32_t WindowManagerImpl::getMainMonitorId() const
		{
			GLFWmonitor *monitor = glfwGetPrimaryMonitor();
			int count = 0;
			GLFWmonitor **monitors = glfwGetMonitors(&count);
			GLFWmonitor **it = std::find(monitors, monitors + count + 1, monitor);
			return uint32_t(it - monitors);

		}

		std::unique_ptr<RenderContext> WindowManagerImpl::createRenderContext(const RenderContextParameters &params, Window *) const
		{
			std::unique_ptr<Driver> driver(new glfw::DriverImpl());
			std::unique_ptr<RenderContext> context(new RenderContext(std::move(driver)));
			context->init(params, window);
			return context;
		}

	}
}
#else 

#include <engine/view/glfw/empty/WindowManagerImpl.cpp>

#endif
