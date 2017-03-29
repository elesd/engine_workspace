#pragma once

#include <engine/events/Keyboard.h>

#include <Windows.h>

namespace engine
{
	namespace winapi
	{
		class KeyboardImpl : public Keyboard
		{
		public:
			KeyboardImpl() = default;
			~KeyboardImpl() override {}

			bool handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		private:
			bool handleKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
			bool handleKeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

		};
	}
}