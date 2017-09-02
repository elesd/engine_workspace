#include <stdafx.h>
#if ENGINE_USE_WINAPI

#include <engine/view/winapi/WindowManagerImpl.h>
///////////////////////////////////////////////////
#include <engine/Context.h>
#include <engine/app/Application.h>

#include <engine/app/winapi/WinApiApplicationParameter.h>
#include <engine/app/winapi/ApplicationImpl.h>

#include <engine/render/RenderContext.h>

#include <engine/view/Window.h>
#include <engine/view/winapi/WindowImpl.h>

#include <engine/video/winapi/BufferObjectFactoryImpl.h>
#include <engine/video/winapi/DriverImpl.h>


namespace
{

	bool handleEventsOfApplication(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		engine::winapi::ApplicationImpl *application = static_cast<engine::winapi::ApplicationImpl*>(engine::Context::application());
		return application->handleEvent(hWnd, message, wParam, lParam);
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		bool handled = handleEventsOfApplication(hWnd, message, wParam, lParam);
		handled = handled || DefWindowProc(hWnd, message, wParam, lParam);
		return handled;
	}

	BOOL CALLBACK MonitorInitializer(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
	{
		std::vector<HMONITOR> *monitorData = (std::vector<HMONITOR>*)dwData;
		monitorData->push_back(hMonitor);
		return TRUE;
	}

	const std::string windowClassName = "win32enginewindow";

}


namespace engine
{
	namespace winapi
	{
		struct WindowManagerImplPrivate
		{
			std::vector<HMONITOR> monitors;
			WNDCLASSEX windowClass;
			bool hasWindowClass = false;
		};

		WindowManagerImpl::WindowManagerImpl(const DeviceParameters& driverContextParameters, const GlobalResourceMapping& resourceMapping)
			: WindowManager(driverContextParameters, resourceMapping)
			, _members(new WindowManagerImplPrivate())
		{
			EnumDisplayMonitors(NULL, NULL, MonitorInitializer, (LPARAM)&_members->monitors);
		}

		WindowManagerImpl::~WindowManagerImpl()
		{
			UnregisterClass(windowClassName.c_str(), nullptr);
			delete _members;
		}

		WindowImpl *WindowManagerImpl::findWindowById(HWND hWnd) const
		{
			for(Window *window : getAllWindows())
			{
				WindowImpl *w = static_cast<WindowImpl*>(window);
				if(w->getWindowHandler() == hWnd)
					return w;
			}
			return nullptr;
		}

		Window *WindowManagerImpl::createMainWindowImpl(const WindowParameter &parameters, const std::string &title)
		{
			if(!_members->hasWindowClass)
			{
				RegisterWindowClass();
			}
			const IApplicationParameter *arguments = Context::application()->getArguments();
			const winapi::WinApiApplicationParameter *args = static_cast<const winapi::WinApiApplicationParameter*>(arguments);


			HWND hWnd = CreateWindowEx(NULL,
									   windowClassName.c_str(),
									   title.c_str(),
									   WS_OVERLAPPEDWINDOW,
									   parameters.x, parameters.y,
									   parameters.width, parameters.height,
									   NULL,
									   NULL,
									   args->getInstance(),
									   NULL);
			std::unique_ptr<WindowImpl> result;
			if(hWnd)
			{
				result.reset(new WindowImpl(this, hWnd, parameters, title));
				ShowWindow(hWnd, args->getCmdShow());
				UpdateWindow(hWnd);
			}
			return result.release();
		}

		Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId)
		{
			if(!_members->hasWindowClass)
			{
				RegisterWindowClass();
			}
			const IApplicationParameter *arguments = Context::application()->getArguments();
			const winapi::WinApiApplicationParameter *args = static_cast<const winapi::WinApiApplicationParameter*>(arguments);

			MONITORINFO monitor_info;
			monitor_info.cbSize = sizeof(monitor_info);
			ASSERT(getMonitorCount() > monitorId);
			HMONITOR monitor = _members->monitors[monitorId];
			GetMonitorInfo(monitor, &monitor_info);

			HWND hWnd = CreateWindowEx(NULL,
									   windowClassName.c_str(),
									   title.c_str(),
									   WS_OVERLAPPEDWINDOW,
									   monitor_info.rcMonitor.left,
									   monitor_info.rcMonitor.top,
									   monitor_info.rcMonitor.right - monitor_info.rcMonitor.left,
									   monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top,
									   NULL,
									   NULL,
									   args->getInstance(),
									   NULL);
			std::unique_ptr<WindowImpl> result;
			if(hWnd)
			{
				result.reset(new WindowImpl(this, hWnd, title));


				ShowWindow(hWnd, args->getCmdShow());
				UpdateWindow(hWnd);
			}
			return result.release();
		}

		Window *WindowManagerImpl::createSecondaryWindowImpl(const WindowParameter &parameters,
															 const std::string &title,
															 Window *mainWindow)
		{
			if(!_members->hasWindowClass)
			{
				RegisterWindowClass();
			}
			const IApplicationParameter *arguments = Context::application()->getArguments();
			const winapi::WinApiApplicationParameter *args = static_cast<const winapi::WinApiApplicationParameter*>(arguments);

			WindowImpl *winapiWindow = static_cast<WindowImpl*>(mainWindow);
			HWND hWnd = CreateWindowEx(NULL,
									   windowClassName.c_str(),
									   title.c_str(),
									   WS_OVERLAPPEDWINDOW,
									   parameters.x, parameters.y,
									   parameters.width, parameters.height,
									   winapiWindow->getWindowHandler(),
									   NULL,
									   args->getInstance(),
									   NULL);
			std::unique_ptr<WindowImpl> result;
			if(hWnd)
			{
				result.reset(new WindowImpl(this, hWnd, parameters, title));
				ShowWindow(hWnd, args->getCmdShow());
				UpdateWindow(hWnd);
			}
			return result.release();
		}

		Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow)
		{
			if(!_members->hasWindowClass)
			{
				RegisterWindowClass();
			}
			const IApplicationParameter *arguments = Context::application()->getArguments();
			const winapi::WinApiApplicationParameter *args = static_cast<const winapi::WinApiApplicationParameter*>(arguments);

			MONITORINFO monitor_info;
			monitor_info.cbSize = sizeof(monitor_info);
			ASSERT(getMonitorCount() > monitorId);
			HMONITOR monitor = _members->monitors[monitorId];
			GetMonitorInfo(monitor, &monitor_info);
			WindowImpl *winapiWindow = static_cast<WindowImpl*>(mainWindow);

			HWND hWnd = CreateWindowEx(NULL,
									   windowClassName.c_str(),
									   title.c_str(),
									   WS_OVERLAPPEDWINDOW,
									   monitor_info.rcMonitor.left,
									   monitor_info.rcMonitor.top,
									   monitor_info.rcMonitor.right - monitor_info.rcMonitor.left,
									   monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top,
									   winapiWindow->getWindowHandler(),
									   NULL,
									   args->getInstance(),
									   NULL);
			std::unique_ptr<WindowImpl> result;
			if(hWnd)
			{
				result.reset(new WindowImpl(this, hWnd, title));


				ShowWindow(hWnd, args->getCmdShow());
				UpdateWindow(hWnd);
			}
			return result.release();
		}

		uint32_t WindowManagerImpl::getMonitorCount() const
		{
			return uint32_t(_members->monitors.size());
		}

		uint32_t WindowManagerImpl::getMainMonitorId() const
		{
			return 0;
		}

		void WindowManagerImpl::RegisterWindowClass()
		{
			const IApplicationParameter *arguments = Context::application()->getArguments();
			const winapi::WinApiApplicationParameter *args = static_cast<const winapi::WinApiApplicationParameter*>(arguments);
			memset(&_members->windowClass, 0, sizeof(WNDCLASSEX));
			_members->windowClass.cbSize = sizeof(WNDCLASSEX);
			_members->windowClass.style = CS_HREDRAW | CS_VREDRAW;

			_members->windowClass.lpfnWndProc = WndProc;
			_members->windowClass.cbClsExtra = 0;
			_members->windowClass.cbWndExtra = 0;
			_members->windowClass.hInstance = args->getInstance();
			_members->windowClass.hIcon = LoadIcon(args->getInstance(), MAKEINTRESOURCE(IDI_APPLICATION));
			_members->windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			_members->windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			_members->windowClass.lpszMenuName = NULL;
			_members->windowClass.lpszClassName = windowClassName.c_str();
			_members->windowClass.hIconSm = LoadIcon(args->getInstance(), MAKEINTRESOURCE(IDI_APPLICATION));
			ASSERT(RegisterClassEx(&_members->windowClass));
			_members->hasWindowClass = true;
		}

		std::unique_ptr<Driver> WindowManagerImpl::createDriver(const DeviceParameters& deviceParameter) const
		{
			std::unique_ptr<Driver> driver(new DriverImpl());
			driver->initDevice(deviceParameter);
			return driver;
		}

		std::unique_ptr<RenderContext> WindowManagerImpl::createRenderContext(std::unique_ptr<Driver>&& driver) const
		{
			std::unique_ptr<BufferObjectFactory> bufferObjectFactory(new BufferObjectFactoryImpl(driver.get()));
			std::unique_ptr<RenderContext> context(new RenderContext(std::move(driver), std::move(bufferObjectFactory)));
			return context;
		}

		void WindowManagerImpl::preInitCreation(Driver* driver, RenderContext* renderContext, const RenderContextParameters &params) const
		{

		}

		void WindowManagerImpl::postInitCreation(Driver* driver, RenderContext* renderContext, const RenderContextParameters &params, Window* window) const
		{
			renderContext->setWindow(window);
			renderContext->init(params);
		}
	}
}

#endif
