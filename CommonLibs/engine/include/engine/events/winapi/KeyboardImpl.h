#pragma once

#include <engine/events/Keyboard.h>

#include <Windows.h>

namespace engine
{
	namespace winapi
	{
		/**
		* Keyboard implementation for winapi.
		*/
		class KeyboardImpl : public Keyboard
		{
		public:
			/**Default constructable*/
			KeyboardImpl() = default;
			/**Simple destructor*/
			~KeyboardImpl() override {}

			/**
			* Handle winapi event.
			* @param hWnd: WinProc parameter.
			* @param message: WinProc parameter.
			* @param wParam: WinProc parameter.
			* @param lParam: WinProc parameter.
			* @return Returns true if it handled any event.
			*/
			bool handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		private:
			/**
			* Handle winapi event.
			* @param hWnd: WinProc parameter.
			* @param message: WinProc parameter.
			* @param wParam: WinProc parameter.
			* @param lParam: WinProc parameter.
			* @return Returns true if it handled any event.
			*/
			bool handleKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
			/**
			* Handle winapi event.
			* @param hWnd: WinProc parameter.
			* @param message: WinProc parameter.
			* @param wParam: WinProc parameter.
			* @param lParam: WinProc parameter.
			* @return Returns true if it handled any event.
			*/
			bool handleKeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

		};
	}
}