#pragma once

#include <engine/events/EventManager.h>


namespace engine
{
	namespace winapi
	{
		class EventManagerImpl : public EventManager
		{
		public:
			bool handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		};
	}
}
