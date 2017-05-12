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
		/**Sdl specific implementation of the event manager in order to handle different type of events. */
		class EventManagerImpl : public EventManager
		{
		public:
			/**Handle keyboard events*/
			void handleEvent(const SDL_KeyboardEvent&);
			/**Handle mouse motion events*/
			void handleEvent(const SDL_MouseMotionEvent&);
			/**Handle mouse button events*/
			void handleEvent(const SDL_MouseButtonEvent&);
			/**Handle mouse wheel events*/
			void handleEvent(const SDL_MouseWheelEvent&);
		};
	}
}
