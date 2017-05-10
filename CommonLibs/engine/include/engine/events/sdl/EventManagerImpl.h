#pragma once

#include <engine/events/EventManager.h>

struct SDL_KeyboardEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;


namespace engine
{
	namespace sdl
	{
		class EventManagerImpl : public EventManager
		{
		public:
			void handleEvent(const SDL_KeyboardEvent&);
			void handleEvent(const SDL_MouseMotionEvent&);
			void handleEvent(const SDL_MouseButtonEvent&);
			void handleEvent(const SDL_MouseWheelEvent&);
		};
	}
}
