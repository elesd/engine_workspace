#pragma once

#include <engine/events/EventManager.h>

class GLFWwindow;


namespace engine
{
	namespace glfw
	{
		class EventManagerImpl : public EventManager
		{
		public:
			static void mouseMovedCallback(GLFWwindow* window, double xpos, double ypos);
			static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			static void mouseScrolledCallback(GLFWwindow* window, double xoffset, double yoffset);
		};
	}
}