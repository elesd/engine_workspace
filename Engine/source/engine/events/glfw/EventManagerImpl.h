#pragma once

#include <engine/events/EventManager.h>

struct GLFWwindow;


namespace engine
{
	namespace glfw
	{
		class WindowImpl;

		/**Glfw event manager which can handles the glfw events*/
		class EventManagerImpl : public EventManager
		{
		public:
			/**
			* Handle mouse moved event.
			* @param window: Window where the event is emitted.
			* @param xpos: x coordinate of the mouse.
			* @param ypos: y coordinate of the mouse.
			* @see http://www.glfw.org/docs/latest/group__input.html#ga4cfad918fa836f09541e7b9acd36686c
			*/
			void mouseMovedCallback(WindowImpl* window, double xpos, double ypos);
			/**
			* Mouse button event handling.
			* @param window: Window where the event is emitted.
			* @param button: The mouse button that was pressed or released.
			* @param action: One of GLFW_PRESS or GLFW_RELEASE.
			* @param mods: 	Bit field describing which modifier keys were held down.

			* @see http://www.glfw.org/docs/latest/group__input.html#ga39893a4a7e7c3239c98d29c9e084350c
			*/
			void mouseButtonCallback(WindowImpl* window, int button, int action, int mods);
			
			/**
			* Handle the mouse scroll event.
			* @param window: Window where the event is emitted.
			* @param xoffset: The scroll offset along the x-axis.
			* @param yoffset: The scroll offset along the y-axis.
			* @see http://www.glfw.org/docs/latest/group__input.html#ga4687e2199c60a18a8dd1da532e6d75c9
			*/
			void mouseScrolledCallback(WindowImpl* window, double xoffset, double yoffset);

			/**
			* Handle keyboard events.
			* @param window: Window where the event is emitted.
			* @param key: The keyboard key that was pressed or released.
			* @param scancode: The system-specific scancode of the key.
			* @param action: GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
			* @param mods:	Bit field describing which modifier keys were held down.
			* @see http://www.glfw.org/docs/latest/group__input.html#ga0192a232a41e4e82948217c8ba94fdfd
			*/
			void keyboardCallback(WindowImpl* window, int key, int scancode, int action, int mods);

			void windowClosedCallback(WindowImpl*);
			void windowResizedCallback(WindowImpl* window, int32_t width, int32_t height);
			void windowMovedCallback(WindowImpl* window, int32_t x, int32_t y);
			void windowFocusCallback(WindowImpl* window, int32_t focused);
			void windowFrameBufferResizeCallback(WindowImpl* window, int32_t width, int32_t height);
		};
	}
}
