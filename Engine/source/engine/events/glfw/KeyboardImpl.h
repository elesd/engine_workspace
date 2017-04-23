#pragma once

#include <engine/events/Keyboard.h>


namespace engine
{
  namespace glfw
  {
	class KeyboardImpl : public Keyboard
	{
	public:
		KeyboardImpl() = default;
		~KeyboardImpl() override {}

		bool handleKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mods);
	private:
		bool handleKeyUpEvent(int32_t);
		bool handleKeyDownEvent(int32_t);
	};
  }
}
