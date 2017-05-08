#pragma once

#include <engine/events/EventManager.h>


namespace engine
{
	namespace winapi
	{
		/**Event manager implementation for winapi*/
		class EventManagerImpl : public EventManager
		{
		public:
			/**
			* Handle events of the engine via WinProc.
			* This function dipatch the given parameters between registered or stored event handlers.
			* @param hWnd: WinProc parameter
			* @param message: WinProc parameter
			* @param wParam: WinProc parameter
			* @param lParam: WinProc parameter
			* @return Returns true if the given event was handeled someone.
			*/
			bool handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		};
	}
}
