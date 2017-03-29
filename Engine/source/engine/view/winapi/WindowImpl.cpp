#include <stdafx.h>
#if ENGINE_USE_WINAPI

#include <engine/view/winapi/WindowImpl.h>
/////////////////////////////////////////

namespace engine
{
	namespace winapi
	{
		struct WindowImplPrivate
		{
			HWND windowHandler;
			std::string title;
		};

		WindowImpl::WindowImpl(HWND window, const WindowParameter &parameters, const std::string &title)
			: Window(parameters),
			_members(new WindowImplPrivate())
		{
			_members->windowHandler = window;
			_members->title = title;
		}

		WindowImpl::WindowImpl(HWND window, const std::string &title)
			: Window(),
			_members(new WindowImplPrivate())
		{
			_members->windowHandler = window;
			_members->title = title;

		}

		WindowImpl::~WindowImpl()
		{
			delete _members;
		}

		WindowImpl::operator bool() const
		{
			return _members->windowHandler != nullptr;
		}

		void WindowImpl::setPositionImp(int32_t x, int32_t y)
		{
			SetWindowPos(_members->windowHandler, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
		}

		void WindowImpl::setWidthImpl(uint32_t width)
		{
			setSizeImpl(width, getParameters().height);
		}

		void WindowImpl::setHeightImpl(uint32_t height)
		{
			setSizeImpl(getParameters().width, height);
		}

		void WindowImpl::setSizeImpl(uint32_t width, uint32_t height)
		{
			SetWindowPos(_members->windowHandler, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);
		}

		HWND WindowImpl::getWindowHandler()
		{
			return _members->windowHandler;
		}

		bool WindowImpl::handleEvent(HWND hWnd,
									 UINT message,
									 WPARAM wParam,
									 LPARAM lParam)
		{
			bool handled = false;
			switch(message)
			{
				case WM_CLOSE:
					windowClosed.emit();
					handled = true;
					break;
				case WM_SIZE:
				{
					uint32_t width = LOWORD(lParam);
					uint32_t height = HIWORD(lParam);
					windowSizeChanged.emit(width, height);
					handled = true;
				}
				break;
				case WM_MOVE:
				{
					POINTS newCoord = MAKEPOINTS(lParam);
					int32_t xPos = newCoord.x;
					int32_t yPos = newCoord.y;
					windowMoved.emit(xPos, yPos);
					handled = true;
				}
				break;
				case WM_SETFOCUS:
					windowInFocus.emit();
					handled = true;
					break;
				case WM_KILLFOCUS:
					windowOutFocus.emit();
					handled = true;
					break;
			}
			return handled;
		}
	}
}
#endif