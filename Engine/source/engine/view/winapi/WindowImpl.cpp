#include "stdafx.h"
#if ENGINE_USE_WINAPI

#include "engine/view/winapi/WindowImpl.h"
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
	}
}
#endif