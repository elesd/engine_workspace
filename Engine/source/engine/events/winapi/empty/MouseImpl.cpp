#include <stdafx.h>
#include <engine/events/winapi/MouseImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if !ENGINE_USE_WINAPI
namespace engine
{
	namespace winapi
	{
		bool MouseImpl::handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not active module");
			return false;
		}

		bool MouseImpl::handleDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not active module");
			return false;
		}

		bool MouseImpl::handleUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not active module");
			return false;
		}

		bool MouseImpl::handleMoveEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not active module");
			return false;
		}

		bool MouseImpl::handleScrollEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not active module");
			return false;
		}

	}
}
#endif