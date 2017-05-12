#pragma once

#include <engine/events/Keyboard.h>

struct SDL_KeyboardEvent;

namespace engine
{
	namespace sdl
	{
		/** Implement sdl keyboard		*/
		class KeyboardImpl : public Keyboard
		{
		public:
			/** Default constructable*/
			KeyboardImpl() = default;
			/** Ensure virtual property*/
			~KeyboardImpl() override {}

			/** Handle sdl keyboard event.*/
			void handleEvent(const SDL_KeyboardEvent &);
		};
	}
}
