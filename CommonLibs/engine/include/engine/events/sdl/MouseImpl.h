#pragma once

#include <engine/events/Mouse.h>

struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;

namespace engine
{
	namespace sdl
	{
		class MouseImpl : public Mouse
		{

		public:
			MouseImpl() = default;
			~MouseImpl() override {};
			void handleMoveEvent(const SDL_MouseMotionEvent&);
			void handleClickEvent(const SDL_MouseButtonEvent&);
			void handleScrollEvent(const SDL_MouseWheelEvent&);
		};
	}
}
