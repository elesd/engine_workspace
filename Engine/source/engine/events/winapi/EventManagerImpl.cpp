#include <stdafx.h>
#include <engine/events/winapi/EventManagerImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_WINAPI
#include <engine/events/winapi/MouseImpl.h>
#include <engine/events/winapi/KeyboardImpl.h>
#include <engine/view/winapi/WindowImpl.h>

namespace
{
	template<class T_EventHandler>
	bool handleEventOf(engine::winapi::EventManagerImpl *eventManager, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		std::vector<T_EventHandler*> handlers = eventManager->findEventSource<T_EventHandler>();
		bool handled = false;
		for(T_EventHandler *handler : handlers)
		{
			handled = handler->handleEvent(hWnd, message, wParam, lParam);
			if(handled)
				break;
		}
		return handled;
	}
}

namespace engine
{
	namespace winapi
	{
		bool EventManagerImpl::handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			if(handleEventOf<MouseImpl>(this, hWnd, message, wParam, lParam))
				return true;
			else if(handleEventOf<KeyboardImpl>(this, hWnd, message, wParam, lParam))
				return true;
			else if(handleEventOf<WindowImpl>(this, hWnd, message, wParam, lParam))
				return true;
			else
				return false;
		}
	}
}
#else 

#include <engine/events/winapi/empty/EventManagerImpl.cpp>

#endif
