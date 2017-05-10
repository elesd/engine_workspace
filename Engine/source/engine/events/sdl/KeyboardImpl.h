#pragma once

#include <engine/events/Keyboard.h>

struct SDL_KeyboardEvent;

namespace engine
{
	namespace sdl
	{
		class KeyboardImpl : public Keyboard
		{
		public:
			KeyboardImpl() = default;
			~KeyboardImpl() override {}

			void handleEvent(const SDL_KeyboardEvent &);
		};
	}
}
