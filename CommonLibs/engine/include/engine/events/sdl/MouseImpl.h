#pragma once

#include <engine/events/Mouse.h>

struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;

namespace engine
{
	namespace sdl
	{
		/** Sdl mouse implementation.*/
		class MouseImpl : public Mouse
		{
		public:
			/**Default constructable.*/
			MouseImpl() = default;
			/**Ensure polimorphsm.*/
			~MouseImpl() override {};
			/**Handle move event.*/
			void handleMoveEvent(const SDL_MouseMotionEvent&);
			/**Handle click event.*/
			void handleClickEvent(const SDL_MouseButtonEvent&);
			/**Handle scroll event.*/
			void handleScrollEvent(const SDL_MouseWheelEvent&);
		};
	}
}
