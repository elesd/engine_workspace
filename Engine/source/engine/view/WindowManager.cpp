#include <stdafx.h>

#include <engine/view/WindowManager.h>

#include <engine/Context.h>

#include <engine/app/Application.h>

#include <engine/events/EventManager.h>

#include <engine/exceptions/LogicalErrors.h>
#include <engine/exceptions/RuntimeErrors.h>

#include <engine/functional/functions.h>

#include <engine/view/Window.h>

#include <engine/video/Driver.h>
#include <engine/video/BufferDesc.h>

namespace engine
{
	struct WindowManagerPrivate
	{
		std::unique_ptr<Window> mainWindow = nullptr;
		std::vector<std::unique_ptr<Window>> windowContainer;
		DriverInitParameters driverParameters;
	};

	WindowManager::WindowManager()
		: _members(new WindowManagerPrivate())
	{
		_members->driverParameters.description.format = TextureFormat::_R8G8B8A8;
		_members->driverParameters.description.isSRGB = false;
		_members->driverParameters.description.type = BufferType::UnsignedInteger;
	}

	WindowManager::~WindowManager()
	{
		delete _members;
	}

	Window *WindowManager::createMainWindow(const WindowParameter &parameters, const std::string &title)
	{
		if(_members->mainWindow != nullptr)
			throw InitializationError("Main window is already exists");

		if(driverNeedsWindow())
		{
			_members->mainWindow.reset(createMainWindowImpl(parameters, title));
			std::unique_ptr<Driver> driver = createDriverForWindow(_members->driverParameters, _members->mainWindow.get());
			_members->mainWindow->initDriver(std::move(driver));
		}
		else
		{
			std::unique_ptr<Driver> driver = createDriverForWindow(_members->driverParameters, nullptr);
			_members->mainWindow.reset(createMainWindowImpl(parameters, title));
			_members->mainWindow->initDriver(std::move(driver));
		}
		Context::getInstance()->getApplication()->getEventManager()->registerEventSource(_members->mainWindow.get());
		return _members->mainWindow.get();
	}

	Window *WindowManager::createFullScreenMainWindow(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId)
	{
		if(_members->mainWindow != nullptr)
			throw InitializationError("Main window is already exists");
		if(driverNeedsWindow())
		{
			_members->mainWindow.reset(createFullScreenMainWindowImpl(width, height, title, monitorId));
			std::unique_ptr<Driver> driver = createDriverForWindow(_members->driverParameters, _members->mainWindow.get());
			_members->mainWindow->initDriver(std::move(driver));
		}
		else
		{
			std::unique_ptr<Driver> driver = createDriverForWindow(_members->driverParameters, nullptr);
			_members->mainWindow.reset(createFullScreenMainWindowImpl(width, height, title, monitorId));
			_members->mainWindow->initDriver(std::move(driver));
		}
		Context::getInstance()->getApplication()->getEventManager()->registerEventSource(_members->mainWindow.get());
		return _members->mainWindow.get();
	}

	Window *WindowManager::createSecondaryWindow(const WindowParameter &parameters,
												 const std::string &title,
												 Window *mainWindow)
	{
		if(driverNeedsWindow())
		{
			std::unique_ptr<Window> window(createSecondaryWindowImpl(parameters, title, mainWindow));
			_members->windowContainer.emplace_back(std::move(window));
			std::unique_ptr<Driver> driver = createDriverForWindow(_members->driverParameters, window.get());
			window->initDriver(std::move(driver));
		}
		else
		{
			std::unique_ptr<Driver> driver = createDriverForWindow(_members->driverParameters, nullptr);
			std::unique_ptr<Window> window(createSecondaryWindowImpl(parameters, title, mainWindow));
			window->initDriver(std::move(driver));
			_members->windowContainer.emplace_back(std::move(window));
		}
		Context::getInstance()->getApplication()->getEventManager()->registerEventSource(_members->windowContainer.back().get());
		return _members->windowContainer.back().get();
	}

	Window *WindowManager::createSecondaryFullScreenWindow(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow)
	{
		if(driverNeedsWindow())
		{
			std::unique_ptr<Window> window(createSecondaryFullScreenWindowImpl(width, height, title, monitorId, mainWindow));
			_members->windowContainer.emplace_back(std::move(window));

		//	std::unique_ptr<Driver> driver = createDriverForWindow(_members->driverParameters, window.get());
		//	window->initDriver(std::move(driver));
		}
		else
		{
	//		std::unique_ptr<Driver> driver = createDriverForWindow(_members->driverParameters, nullptr);
			std::unique_ptr<Window> window(createSecondaryFullScreenWindowImpl(width, height, title, monitorId, mainWindow));
			//window->initDriver(std::move(driver));
			_members->windowContainer.emplace_back(std::move(window));

		}
		Context::getInstance()->getApplication()->getEventManager()->registerEventSource(_members->windowContainer.back().get());
		return _members->windowContainer.back().get();
	}

	void WindowManager::destroyWindow(Window *window)
	{
		Context::getInstance()->getApplication()->getEventManager()->removeEventSource(window);

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
					   [](std::unique_ptr<Window> &window)->Window*{return window.get(); });
		return windows;
	}

	void WindowManager::setDriverParameter(const DriverInitParameters &defaultParameters)
	{
		_members->driverParameters = defaultParameters;
	}
}
