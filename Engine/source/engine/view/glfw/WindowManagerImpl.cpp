#include <stdafx.h>
#include <engine/view/glfw/WindowManagerImpl.h>
///////////////////////////////////////////////////
#if ENGINE_USE_GLFW

#include <engine/app/glfw/ApplicationImpl.h>

#include <engine/modules/glew/Core.h>

#include <engine/render/RenderContext.h>

#include <engine/view/glfw/WindowImpl.h>

#include <engine/video/glew/BufferObjectFactoryImpl.h>
#include <engine/video/glfw/DriverImpl.h>
#include <engine/video/Driver.h>

#include <GLFW/glfw3.h>
namespace
{
	void registerInputCallbacks(GLFWwindow *window)
	{
		glfwSetCursorPosCallback(window, engine::glfw::ApplicationImpl::mouseMovedCallback);
		glfwSetMouseButtonCallback(window, engine::glfw::ApplicationImpl::mouseButtonCallback);
		glfwSetScrollCallback(window, engine::glfw::ApplicationImpl::mouseScrolledCallback);
		glfwSetKeyCallback(window, engine::glfw::ApplicationImpl::keyboardCallback);
		glfwSetWindowCloseCallback(window, engine::glfw::ApplicationImpl::windowClosedCallback);
		glfwSetWindowFocusCallback(window, engine::glfw::ApplicationImpl::windowFocusCallback);
		glfwSetWindowSizeCallback(window, engine::glfw::ApplicationImpl::windowResizedCallback);
		glfwSetWindowPosCallback(window, engine::glfw::ApplicationImpl::windowMovedCallback);
		glfwSetFramebufferSizeCallback(window, engine::glfw::ApplicationImpl::windowFrameBufferResizeCallback);
	}
}

namespace engine
{
	namespace glfw
	{

		WindowManagerImpl::WindowManagerImpl(const DeviceParameters& driverContextParameters, const GlobalResourceMapping& resourceMapping, std::unique_ptr<EventManagerFactory>&& eventManagerFactory)
			: WindowManager(driverContextParameters, resourceMapping, std::move(eventManagerFactory))
		{
		}

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
				result.reset(new WindowImpl(this, std::move(window), parameters, title));
				registerInputCallbacks(window);

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
					result.reset(new WindowImpl(this, window, title));
					registerInputCallbacks(window);
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
				result.reset(new WindowImpl(this, std::move(window), parameters, title));
				registerInputCallbacks(window);
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
					result.reset(new WindowImpl(this, window, title));
					registerInputCallbacks(window);
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

		std::unique_ptr<Driver> WindowManagerImpl::createDriver(const DeviceParameters& parameters) const
		{
			std::unique_ptr<Driver> driver(new DriverImpl());
			driver->initDevice(parameters);
			return driver;
		}

		std::unique_ptr<RenderContext> WindowManagerImpl::createRenderContext(std::unique_ptr<Driver>&& driver) const
		{
			std::unique_ptr<BufferObjectFactory> bufferObjectFactory(new glew::BufferObjectFactoryImpl(driver.get()));
			std::unique_ptr<RenderContext> context(new RenderContext(std::move(driver), std::move(bufferObjectFactory)));
			return context;

		}

		void WindowManagerImpl::preInitCreation(Driver* /*driver*/, RenderContext* renderContext, const RenderContextParameters &params) const
		{
			renderContext->init(params);

		}

		void WindowManagerImpl::postInitCreation(Driver* /*driver*/, RenderContext* renderContext, const RenderContextParameters& /*params*/, Window* window) const
		{
			glfwMakeContextCurrent(static_cast<WindowImpl*>(window)->getGlfwWindow());
			glew::Core::initOpenglContext();
			renderContext->setWindow(window);
		}
	}
}

#endif
