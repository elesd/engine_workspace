#include <stdafx.h>

#include <engine/view/WindowManager.h>

#include <engine/Context.h>

#include <engine/app/Application.h>
#include <engine/events/EventManagerFactory.h>
#include <engine/events/EventManager.h>

#include <engine/exceptions/LogicalErrors.h>
#include <engine/exceptions/RuntimeErrors.h>

#include <engine/functional/functions.h>

#include <engine/render/RenderContext.h>

#include <engine/view/Window.h>

#include <engine/video/BufferObjectFactory.h>
#include <engine/video/BufferDesc.h>

namespace engine
{
	struct WindowManagerPrivate
	{
		std::unique_ptr<Window> mainWindow = nullptr;
		std::vector<std::unique_ptr<Window>> windowContainer;
		RenderContextParameters renderContextParameters;
		std::vector<Window*> closedWindows;
		DeviceParameters deviceParameters;
		explicit WindowManagerPrivate(const DeviceParameters& parameters)
			: deviceParameters(parameters)
		{ }
	};

	WindowManager::WindowManager(const DeviceParameters& parameters)
		: _members(new WindowManagerPrivate(parameters))
	{
		DriverInitParameters driverParameters;
		driverParameters.sampleCount = 1;
		driverParameters.description.format = TextureFormat::_R8G8B8A8;
		driverParameters.description.isSRGB = false;
		driverParameters.description.type = BufferType::UnsignedNormalized;
		_members->renderContextParameters = RenderContextParameters(driverParameters);
	}

	WindowManager::~WindowManager()
	{
		delete _members;
	}

	void WindowManager::update()
	{
		_members->mainWindow->update();
		for(std::unique_ptr<Window> &window : _members->windowContainer)
		{
			window->update();
		}
		eraseClosedWindows();
	}

	Window *WindowManager::createMainWindow(const WindowParameter &parameters, const std::string &title)
	{
		if(_members->mainWindow != nullptr)
			throw InitializationError("Main window is already exists");
		
		std::unique_ptr<Driver> driver = createDriver(_members->deviceParameters);
		Driver* driverPtr = driver.get();
		std::unique_ptr<RenderContext> context = createRenderContext(std::move(driver));
		
		preInitCreation(driverPtr, context.get(), _members->renderContextParameters);
		_members->mainWindow.reset(createMainWindowImpl(parameters, title));
		postInitCreation(driverPtr, context.get(), _members->renderContextParameters, _members->mainWindow.get());

		_members->mainWindow->initRenderContext(std::move(context));

		initWindow(_members->mainWindow.get());

		return _members->mainWindow.get();
	}

	Window *WindowManager::createFullScreenMainWindow(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId)
	{
		if(_members->mainWindow != nullptr)
			throw InitializationError("Main window is already exists");

		std::unique_ptr<Driver> driver = createDriver(_members->deviceParameters);
		Driver* driverPtr = driver.get();
		// TODO share render context
		std::unique_ptr<RenderContext> context = createRenderContext(std::move(driver));

		preInitCreation(driverPtr, context.get(), _members->renderContextParameters);
		_members->mainWindow.reset(createFullScreenMainWindowImpl(width, height, title, monitorId));
		postInitCreation(driverPtr, context.get(), _members->renderContextParameters, _members->mainWindow.get());

		_members->mainWindow->initRenderContext(std::move(context));
		initWindow(_members->mainWindow.get());
		return _members->mainWindow.get();
	}

	Window *WindowManager::createSecondaryWindow(const WindowParameter &parameters,
												 const std::string &title,
												 Window *mainWindow)
	{
		std::unique_ptr<Driver> driver = createDriver(_members->deviceParameters);
		Driver* driverPtr = driver.get();
		std::unique_ptr<RenderContext> context = createRenderContext(std::move(driver));

		preInitCreation(driverPtr, context.get(), _members->renderContextParameters);
		std::unique_ptr<Window> window(createSecondaryWindowImpl(parameters, title, mainWindow));
		postInitCreation(driverPtr, context.get(), _members->renderContextParameters, window.get());

		window->initRenderContext(std::move(context));
		_members->windowContainer.emplace_back(std::move(window));

		initWindow(_members->windowContainer.back().get());
		return _members->windowContainer.back().get();
	}

	Window *WindowManager::createSecondaryFullScreenWindow(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow)
	{

		std::unique_ptr<Driver> driver = createDriver(_members->deviceParameters);
		Driver* driverPtr = driver.get();
		std::unique_ptr<RenderContext> context = createRenderContext(std::move(driver));

		preInitCreation(driverPtr, context.get(), _members->renderContextParameters);
		std::unique_ptr<Window> window(createSecondaryFullScreenWindowImpl(width, height, title, monitorId, mainWindow));
		postInitCreation(driverPtr, context.get(), _members->renderContextParameters, window.get());

		window->initRenderContext(std::move(context));
		_members->windowContainer.emplace_back(std::move(window));
	
		initWindow(_members->windowContainer.back().get());
		return _members->windowContainer.back().get();
	}

	void WindowManager::destroyWindow(Window *window)
	{
		window->getEventManager()->removeEventSource(window);

		if(_members->mainWindow.get() == window)
		{
			_members->mainWindow.reset(nullptr);
		}
		else
		{
			auto it = std::find_if(_members->windowContainer.begin(), _members->windowContainer.end(),
								   PointerEqualTo<Window*>(window));
			if(it == _members->windowContainer.end())
				throw ItemNotFound("Window try to destroyed but it is not exists in manager.");
			_members->windowContainer.erase(it);
		}
	}

	Window *WindowManager::getMainWindow()
	{
		return _members->mainWindow.get();
	}

	const Window *WindowManager::getMainWindow() const
	{
		return _members->mainWindow.get();
	}

	std::vector<Window*> WindowManager::getAllWindows() const
	{
		std::vector<Window*> windows;
		std::transform(_members->windowContainer.begin(), _members->windowContainer.end(), std::back_inserter(windows),
					   [](std::unique_ptr<Window> &window)->Window* { return window.get(); });
		if(_members->mainWindow)
		{
			windows.push_back(_members->mainWindow.get());
		}
		return windows;
	}

	void WindowManager::setRenderContextParameter(const RenderContextParameters &defaultParameters)
	{
		_members->renderContextParameters = defaultParameters;
	}

	void WindowManager::initWindow(Window *window)
	{
		Application *application = Context::application();
		window->setEventManager(application->getEventManagerFactory()->createEventManager());
		window->getEventManager()->registerEventSource(window);
	}

	void WindowManager::eraseClosedWindows()
	{
		for(Window *window : _members->closedWindows)
		{
			if(_members->mainWindow.get() == window)
			{
				_members->mainWindow.reset(nullptr);
				Context::application()->stop();
				for(std::unique_ptr<Window> &w : _members->windowContainer)
				{
					w.reset(nullptr);
				}
				_members->windowContainer.clear();
			}
			else
			{
				auto it = std::find_if(_members->windowContainer.begin(), _members->windowContainer.end(),
									   PointerEqualTo<Window>(window));
				ASSERT(it != _members->windowContainer.end());
				it->reset(nullptr);
			}
		}
		_members->closedWindows.clear();
	}

	void WindowManager::windowClosed(Window *window)
	{
		_members->closedWindows.push_back(window);
	}

	const DeviceParameters& WindowManager::getDeviceParameters() const
	{
		return _members->deviceParameters;
	}
}
