#include "stdafx.h"
#if ENGINE_USE_GLFW
#include "engine/modules/glfw/WindowManagerImpl.h"
///////////////////////////////////////////////////
#include "engine/modules/glfw/WindowImpl.h"

#include "GLFW/glfw3.h"

#include "engine/video/Driver.h"


namespace engine
{
	namespace view
	{
		namespace glfw
		{
			view::Window *WindowManagerImpl::createMainWindowImpl(const view::WindowParameter &parameters,
																  const std::string &title)
			{
				GLFWwindow *window(glfwCreateWindow(parameters.width, parameters.height, title.c_str(), NULL, NULL));
				std::unique_ptr<WindowImpl> result;
				if(window)
				{
					result.reset(new WindowImpl(std::move(window), parameters, title));
					glfwMakeContextCurrent(result->getGlfwWindow());
				}
				return result.release();
			}

			view::Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId)
			{
				int count = 0;
				GLFWmonitor** monitors = glfwGetMonitors(&count);
				std::unique_ptr<WindowImpl> result;
				if(monitorId < uint32_t(count))
				{
					GLFWwindow *window(glfwCreateWindow(width, height, title.c_str(), monitors[monitorId], NULL));
					if(window)
					{
						result.reset(new WindowImpl(window, title));
						glfwMakeContextCurrent(result->getGlfwWindow());
					}
				}
				return result.release();
			}

			view::Window *WindowManagerImpl::createSecondaryWindowImpl(const view::WindowParameter &parameters,
																	   const std::string &title,
																	   view::Window *mainWindow)
			{
				WindowImpl *glfMainWindow = static_cast<WindowImpl*>(mainWindow);
				GLFWwindow *window(glfwCreateWindow(parameters.width, parameters.height, title.c_str(), NULL, glfMainWindow->getGlfwWindow()));
				std::unique_ptr<WindowImpl> result;
				if(window)
				{
					result.reset(new WindowImpl(std::move(window), parameters, title));
				}
				return result.release();
			}

			view::Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, view::Window *mainWindow)
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
						result.reset(new WindowImpl(window, title));
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

			std::unique_ptr<video::Driver> WindowManagerImpl::createDriverForWindow(const video::DriverInitParameters &params, Window *) const
			{
				HARD_FAIL("Not implemented");
				return nullptr;
			}

		}
	}
}
#endif