#include <stdafx.h>
#include <engine/events/winapi/EventManagerImp.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/events/winapi/MouseImpl.h>
#include <engine/events/winapi/KeyboardImpl.h>
#include <engine/view/winapi/WindowImpl.h>

namespace
{
	template<class T_EventHandler>
	bool handleEventOf(engine::winapi::EventManagerImpl *eventManager, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		HARD_FAIL("Not implemented module");
		return false;
	}
}

namespace engine
{
	namespace winapi
	{
		bool EventManagerImpl::handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not implemented module");
			return false;
		}
	}
}