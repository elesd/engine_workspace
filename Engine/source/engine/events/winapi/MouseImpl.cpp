#include <stdafx.h>
#include <engine/events/winapi/MouseImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_WINAPI

namespace
{
	std::vector<engine::MouseButton> parsePressedButtons(WPARAM param)
	{
		using engine::MouseButton;
		std::vector<MouseButton> result;
		if(param & MK_LBUTTON)
		{
			result.push_back(MouseButton::Left);
		}
		if(param & MK_RBUTTON)
		{
			result.push_back(MouseButton::Right);

		}
		if(param & MK_MBUTTON)
		{
			result.push_back(MouseButton::Middle);
		}
		return result;
	}
}

namespace engine
{
	namespace winapi
	{
		bool MouseImpl::handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			bool handled = false;
			switch(message)
			{
				case WM_MBUTTONDOWN: handled = handleMiddleButtonDownEvent(hWnd, wParam, lParam); break;
				case WM_MBUTTONUP:   handled = handleMiddleButtonUpEvent(hWnd, wParam, lParam); break;
				case WM_LBUTTONDOWN: handled = handleLeftButtonDownEvent(hWnd, wParam, lParam); break;
				case WM_LBUTTONUP:   handled = handleLeftButtonUpEvent(hWnd, wParam, lParam); break;
				case WM_RBUTTONDOWN: handled = handleRightButtonDownEvent(hWnd, wParam, lParam); break;
				case WM_RBUTTONUP:   handled = handleRightButtonUpEvent(hWnd, wParam, lParam); break;
				case WM_MOUSEMOVE:   handled = handleMoveEvent(hWnd, wParam, lParam); break;
				case WM_MOUSEWHEEL:   handled = handleScrollEvent(hWnd, wParam, lParam); break;
			}
			return handled;
		}

		bool MouseImpl::handleLeftButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			if(getButtonState(MouseButton::Left) != MouseButtonState::Pressed)
			{
				POINTS points = MAKEPOINTS(lParam);
				int32_t x = points.x;
				int32_t y = points.y;
				leftButtonPressed.emit(x, y);
				onLeftButtonPressed();
			}
			return true;
		}

		bool MouseImpl::handleLeftButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			if(getButtonState(MouseButton::Left) != MouseButtonState::Released)
			{
				POINTS points = MAKEPOINTS(lParam);
				int32_t x = points.x;
				int32_t y = points.y;
				leftButtonReleased.emit(x, y);
				onLeftButtonReleased();
			}
			return true;
		}

		bool MouseImpl::handleRightButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			if(getButtonState(MouseButton::Right) != MouseButtonState::Pressed)
			{
				POINTS points = MAKEPOINTS(lParam);
				int32_t x = points.x;
				int32_t y = points.y;
				rightButtonPressed.emit(x, y);
				onRightButtonPressed();
			}
			return true;
		}

		bool MouseImpl::handleRightButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			if(getButtonState(MouseButton::Right) != MouseButtonState::Released)
			{
				POINTS points = MAKEPOINTS(lParam);
				int32_t x = points.x;
				int32_t y = points.y;
				rightButtonReleased.emit(x, y);
				onRightButtonReleased();
			}
			return true;
		}

		bool MouseImpl::handleMiddleButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			if(getButtonState(MouseButton::Middle) != MouseButtonState::Pressed)
			{
				POINTS points = MAKEPOINTS(lParam);
				int32_t x = points.x;
				int32_t y = points.y;
				middleButtonPressed.emit(x, y);
				onMiddleButtonPressed();
			}
			return true;
		}

		bool MouseImpl::handleMiddleButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			if(getButtonState(MouseButton::Middle) != MouseButtonState::Released)
			{
				POINTS points = MAKEPOINTS(lParam);
				int32_t x = points.x;
				int32_t y = points.y;
				middleButtonReleased.emit(x, y);
				onMiddleButtonReleased();
			}
			return true;
		}

		bool MouseImpl::handleMoveEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			POINTS points = MAKEPOINTS(lParam);
			int32_t x = points.x;
			int32_t y = points.y;

			moved.emit(x, y);
			onMouseMoved(x, y);
			return true;
		}

		bool MouseImpl::handleScrollEvent(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			int32_t delta = GET_WHEEL_DELTA_WPARAM(wParam);
			POINTS points = MAKEPOINTS(lParam);
			int32_t x = points.x;
			int32_t y = points.y;
			scrolled.emit(x, y, delta);
			return true;
		}

	}
}

#else 

#include <engine/events/winapi/empty/MouseImpl.cpp>

#endif
