#pragma once

#include <engine/events/Mouse.h>

namespace engine
{
	namespace winapi
	{
		/**Winapi mouse implementation.*/
		class MouseImpl : public Mouse
		{
		public:
			/**Default constructable*/
			MouseImpl() = default;
			/**Ensure polimorphism.*/
			~MouseImpl() override {}

			/**
			* Try to handle an event.
			* @param hWnd: Window handler.
			* @param message: Event id.
			* @param wParam: Additional message information
			* @param lParam: Additional message information
			* @return Returns true when the event was handled.
			*/
			bool handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		private:
			/**
			* Try to handle an event.
			* @param hWnd: Window handler.
			* @param message: Event id.
			* @param wParam: Additional message information
			* @param lParam: Additional message information
			* @return Returns true when the event was handled.
			* @see https://msdn.microsoft.com/en-us/library/windows/desktop/ms645607(v=vs.85).aspx
			*/
			bool handleLeftButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
			/**
			* Try to handle an event.
			* @param hWnd: Window handler.
			* @param message: Event id.
			* @param wParam: Additional message information
			* @param lParam: Additional message information
			* @return Returns true when the event was handled.
			* @see https://msdn.microsoft.com/en-us/library/windows/desktop/ms645608(v=vs.85).aspx
			*/
			bool handleLeftButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);

			/**
			* Try to handle an event.
			* @param hWnd: Window handler.
			* @param message: Event id.
			* @param wParam: Additional message information
			* @param lParam: Additional message information
			* @return Returns true when the event was handled.
			* @see https://msdn.microsoft.com/en-us/library/windows/desktop/ms646242(v=vs.85).aspx
			*/
			bool handleRightButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
			/**
			* Try to handle an event.
			* @param hWnd: Window handler.
			* @param message: Event id.
			* @param wParam: Additional message information
			* @param lParam: Additional message information
			* @return Returns true when the event was handled.
			* @see https://msdn.microsoft.com/en-us/library/windows/desktop/ms646243(v=vs.85).aspx
			*/
			bool handleRightButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
			/**
			* Try to handle an event.
			* @param hWnd: Window handler.
			* @param message: Event id.
			* @param wParam: Additional message information
			* @param lParam: Additional message information
			* @return Returns true when the event was handled.
			* @see https://msdn.microsoft.com/en-us/library/windows/desktop/ms645610(v=vs.85).aspx
			*/
			bool handleMiddleButtonDownEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
			/**
			* Try to handle an event.
			* @param hWnd: Window handler.
			* @param message: Event id.
			* @param wParam: Additional message information
			* @param lParam: Additional message information
			* @return Returns true when the event was handled.
			* @see https://msdn.microsoft.com/en-us/library/windows/desktop/ms645611(v=vs.85).aspx
			*/
			bool handleMiddleButtonUpEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
			/**
			* Try to handle an event.
			* @param hWnd: Window handler.
			* @param message: Event id.
			* @param wParam: Additional message information
			* @param lParam: Additional message information
			* @return Returns true when the event was handled.
			* @see https://msdn.microsoft.com/en-us/library/windows/desktop/ms645616(v=vs.85).aspx
			*/
			bool handleMoveEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);
			/**
			* Try to handle an event.
			* @param hWnd: Window handler.
			* @param message: Event id.
			* @param wParam: Additional message information
			* @param lParam: Additional message information
			* @return Returns true when the event was handled.
			* @see https://msdn.microsoft.com/en-us/library/windows/desktop/ms645614(v=vs.85).aspx
			*/
			bool handleScrollEvent(HWND hWnd, WPARAM wParam, LPARAM lParam);

		};
	}
}

