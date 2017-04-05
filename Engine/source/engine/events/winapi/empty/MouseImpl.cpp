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
			HARD_FAIL("Not implemented module");
			return false;
		}

		bool MouseImpl::handleLeftButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not implemented module");
			return false;
		}

		bool MouseImpl::handleLeftButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not implemented module");
			return false;
		}

		bool MouseImpl::handleRightButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not implemented module");
			return false;
		}

		bool MouseImpl::handleRightButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not implemented module");
			return false;
		}

		bool MouseImpl::handleMiddleButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not implemented module");
			return false;
		}

		bool MouseImpl::handleMiddleButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not implemented module");
			return false;
		}

		bool MouseImpl::handleMoveEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not implemented module");
			return false;
		}

		bool MouseImpl::handleScrollEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			HARD_FAIL("Not implemented module");
			return false;
		}

	}
}
#endif