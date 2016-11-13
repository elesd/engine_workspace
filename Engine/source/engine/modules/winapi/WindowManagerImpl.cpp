#include "stdafx.h"
#if ENGINE_USE_WINAPI

#include "engine/modules/winapi/WindowManagerImpl.h"
///////////////////////////////////////////////////
#include "engine/modules/winapi/WindowImpl.h"

#include "engine/Context.h"
#include "engine/app/Application.h"

#include "engine/modules/winapi/WinApiApplicationParameter.h"

namespace
{
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hWnd, message, wParam, lParam);;
	}

	BOOL CALLBACK MonitorInitializer(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
	{
		std::vector<HMONITOR> *monitorData = (std::vector<HMONITOR>*)dwData;
		monitorData->push_back(hMonitor);
		return TRUE;
	}

	static TCHAR windowClassName[] = _T("win32app");

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

		WindowManagerImpl::WindowManagerImpl()
			:_members(new WindowManagerImplPrivate())
		{
			EnumDisplayMonitors(NULL, NULL, MonitorInitializer, (LPARAM)&_members->monitors);



		}

		WindowManagerImpl::~WindowManagerImpl()
		{
			delete _members;
		}

		view::Window *WindowManagerImpl::createMainWindowImpl(const view::WindowParameter &parameters, const std::string &title)
		{
			if(!_members->hasWindowClass)
			{
				RegisterWindowClass();
			}
			const app::IApplicationParameter *arguments = Context::getInstance()->getApplication()->getArguments();
			const WinApiApplicationParameter *args = static_cast<const WinApiApplicationParameter*>(arguments);


			HWND hWnd = CreateWindow(
				windowClassName,
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
				result.reset(new WindowImpl(hWnd, title));
				ShowWindow(hWnd, args->getCmdShow());
			}
			return result.release();
		}

		view::Window *WindowManagerImpl::createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId)
		{
			if(!_members->hasWindowClass)
			{
				RegisterWindowClass();
			}
			const app::IApplicationParameter *arguments = Context::getInstance()->getApplication()->getArguments();
			const WinApiApplicationParameter *args = static_cast<const WinApiApplicationParameter*>(arguments);

			MONITORINFO monitor_info;
			monitor_info.cbSize = sizeof(monitor_info);
			ASSERT(getMonitorCount() > monitorId);
			HMONITOR monitor = _members->monitors[monitorId];
			GetMonitorInfo(monitor, &monitor_info);

			HWND hWnd = CreateWindow(
				windowClassName,
				title.c_str(),
				WS_POPUP | WS_VISIBLE,
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
				result.reset(new WindowImpl(hWnd, title));


				ShowWindow(hWnd, args->getCmdShow());
			}
			return result.release();
		}

		view::Window *WindowManagerImpl::createSecondaryWindowImpl(const view::WindowParameter &parameters,
			const std::string &title,
			view::Window *mainWindow)
		{
			if(!_members->hasWindowClass)
			{
				RegisterWindowClass();
			}
			const app::IApplicationParameter *arguments = Context::getInstance()->getApplication()->getArguments();
			const WinApiApplicationParameter *args = static_cast<const WinApiApplicationParameter*>(arguments);

			WindowImpl *winapiWindow = static_cast<WindowImpl*>(mainWindow);
			HWND hWnd = CreateWindow(
				windowClassName,
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
				result.reset(new WindowImpl(hWnd, title));
				ShowWindow(hWnd, args->getCmdShow());
			}
			return result.release();
		}

		view::Window *WindowManagerImpl::createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, view::Window *mainWindow)
		{
			if(!_members->hasWindowClass)
			{
				RegisterWindowClass();
			}
			const app::IApplicationParameter *arguments = Context::getInstance()->getApplication()->getArguments();
			const WinApiApplicationParameter *args = static_cast<const WinApiApplicationParameter*>(arguments);

			MONITORINFO monitor_info;
			monitor_info.cbSize = sizeof(monitor_info);
			ASSERT(getMonitorCount() > monitorId);
			HMONITOR monitor = _members->monitors[monitorId];
			GetMonitorInfo(monitor, &monitor_info);
			WindowImpl *winapiWindow = static_cast<WindowImpl*>(mainWindow);

			HWND hWnd = CreateWindow(
				windowClassName,
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
				result.reset(new WindowImpl(hWnd, title));


				ShowWindow(hWnd, args->getCmdShow());
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
			const app::IApplicationParameter *arguments = Context::getInstance()->getApplication()->getArguments();
			const WinApiApplicationParameter *args = static_cast<const WinApiApplicationParameter*>(arguments);
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
			_members->windowClass.lpszClassName = windowClassName;
			_members->windowClass.hIconSm = LoadIcon(args->getInstance(), MAKEINTRESOURCE(IDI_APPLICATION));
			RegisterClassEx(&_members->windowClass);
			_members->hasWindowClass = true;
		}
	}
}
#endif