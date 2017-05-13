#include <stdafx.h>
#include <engine/events/winapi/EventManagerImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_WINAPI
#include <engine/events/winapi/MouseImpl.h>
#include <engine/events/winapi/KeyboardImpl.h>
#include <engine/view/winapi/WindowImpl.h>

namespace engine
{
	namespace winapi
	{
		bool EventManagerImpl::handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Inactive module");
			return false;
		}
	}
}
#endif
