#pragma once

#include <engine/events/Keyboard.h>


namespace engine
{
	namespace glfw
	{
		/** Glfw keyboard implementation.*/
		class KeyboardImpl : public Keyboard
		{
		public:
			/**Default constructable.*/
			KeyboardImpl() = default;
			/**Ensure polimorf property*/
			~KeyboardImpl() override {}
			/**
			* Handle key event of glfw.
			* @param key: Pressed key
			* @param scancode: The system-specific scancode of the key.
			* @param action: GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
			* @param mods: Bit field describing which modifier keys were held down.
			* @see http://www.glfw.org/docs/latest/group__input.html#ga0192a232a41e4e82948217c8ba94fdfd
			* @return Returns true when the event was handled.
			*/
			bool handleKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mods);
		private:
			/**
			* Hanlde keyboard up event.
			* @param keycode: key code.
			* @return Returns always true.
			*/
			bool handleKeyUpEvent(int32_t keycode);
			/**
			* Hanlde keyboard down event.
			* @param keycode: key code.
			* @return Returns always true.
			*/
			bool handleKeyDownEvent(int32_t keycode);
		};
	}
}
