#include <stdafx.h>

#if !ENGINE_USE_WINAPI
#include <engine/events/winapi/KeyboardImpl.h>


namespace engine
{
	namespace winapi
	{
		bool KeyboardImpl::handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not active module");
			return false;
		}

		bool KeyboardImpl::handleKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not active module");
			return false;
		}

		bool KeyboardImpl::handleKeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not active module");
			return false;
		}
	}
}

#endif