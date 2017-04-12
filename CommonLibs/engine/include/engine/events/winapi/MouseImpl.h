#pragma once

#include <engine/events/Mouse.h>

namespace engine
{
	namespace winapi
	{
		class MouseImpl : public Mouse
		{
		public:
			MouseImpl() = default;
			~MouseImpl() override {}

			bool handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		private:
			bool handleLeftButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
			bool handleLeftButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);

			bool handleRightButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
			bool handleRightButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);

			bool handleMiddleButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
			bool handleMiddleButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);

			bool handleMoveEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
			bool handleScrollEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);

		};
	}
}

