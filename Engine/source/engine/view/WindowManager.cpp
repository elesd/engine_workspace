#include "stdafx.h"

#include "engine/view/WindowManager.h"
#include "engine/view/Window.h"
#include "engine/functional/functions.h"
#include "engine/video/Driver.h"

namespace engine
{
	namespace view
	{
		struct WindowManagerPrivate
		{
			std::unique_ptr<Window> mainWindow = nullptr;
			std::vector<std::unique_ptr<Window>> windowContainer;
			video::DriverInitParameters driverParameters;
		};

		WindowManager::WindowManager()
			: _members(new WindowManagerPrivate())
		{

		}

		WindowManager::~WindowManager()
		{
			delete _members;
		}


		Window *WindowManager::createMainWindow(const WindowParameter &parameters,
			const std::string &title)
		{
			ASSERT(_members->mainWindow == nullptr);
			_members->mainWindow.reset(createMainWindowImpl(parameters, title));
			std::unique_ptr<video::Driver> driver = createDriverForWindow(_members->driverParameters, _members->mainWindow.get());
			_members->mainWindow->initDriver(std::move(driver));
			return _members->mainWindow.get();
		}
		Window *WindowManager::createFullScreenMainWindow(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId)
		{
			ASSERT(_members->mainWindow == nullptr);
			_members->mainWindow.reset(createFullScreenMainWindowImpl(width, height, title, monitorId));
			std::unique_ptr<video::Driver> driver = createDriverForWindow(_members->driverParameters, _members->mainWindow.get());
			_members->mainWindow->initDriver(std::move(driver));
			return _members->mainWindow.get();
		}
		Window *WindowManager::createSecondaryWindow(const WindowParameter &parameters,
			const std::string &title,
			Window *mainWindow)
		{
			std::unique_ptr<Window> window(createSecondaryWindowImpl(parameters, title, mainWindow));
			_members->windowContainer.emplace_back(std::move(window));

			std::unique_ptr<video::Driver> driver = createDriverForWindow(_members->driverParameters, window.get());
			window->initDriver(std::move(driver));

			return _members->windowContainer.back().get();
		}

		Window *WindowManager::createSecondaryFullScreenWindow(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow)
		{
			std::unique_ptr<Window> window(createSecondaryFullScreenWindowImpl(width, height, title, monitorId, mainWindow));
			_members->windowContainer.emplace_back(std::move(window));

			std::unique_ptr<video::Driver> driver = createDriverForWindow(_members->driverParameters, window.get());
			window->initDriver(std::move(driver));

			return _members->windowContainer.back().get();
		}

		void WindowManager::destroyWindow(Window *window)
		{
			if(_members->mainWindow.get() == window)
			{
				_members->mainWindow.reset(nullptr);
			}
			else
			{
				auto it = std::find_if(_members->windowContainer.begin(), _members->windowContainer.end(),
					functional::PointerEqualTo<Window*>(window));
				ASSERT(it != _members->windowContainer.end());
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

		std::vector<const Window*> WindowManager::getAllWindows() const
		{
			std::vector<const Window*> windows;
			std::transform(_members->windowContainer.begin(), _members->windowContainer.end(), std::back_inserter(windows),
				[](std::unique_ptr<Window> &window)->const Window*{return window.get(); });
			return windows;
		}

		std::vector<Window*> WindowManager::getAllWindows()
		{
			std::vector<Window*> windows;
			std::transform(_members->windowContainer.begin(), _members->windowContainer.end(), std::back_inserter(windows),
				[](std::unique_ptr<Window> &window)->Window*{return window.get(); });
			return windows;
		}
	}
}
