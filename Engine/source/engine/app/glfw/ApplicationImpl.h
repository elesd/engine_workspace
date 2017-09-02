#pragma once

#include <engine/app/Application.h>

struct GLFWwindow;

namespace engine
{
	namespace glfw
	{
		class EventManagerImpl;
		class WindowImpl;
		/** Glfw specific application implementation.*/
		class ApplicationImpl : public Application
		{
		public:
			/** @copydoc Application::Application */
			ApplicationImpl(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
			/**Ensure polimorphism.*/
			~ApplicationImpl() override {};

			static void mouseMovedCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
			static void mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
			static void mouseScrolledCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset);
			static void keyboardCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
			static void windowClosedCallback(GLFWwindow*);
			static void windowResizedCallback(GLFWwindow* window, int32_t width, int32_t height);
			static void windowMovedCallback(GLFWwindow* window, int32_t x, int32_t y);
			static void windowFocusCallback(GLFWwindow* window, int32_t focused);
			static void windowFrameBufferResizeCallback(GLFWwindow* window, int32_t width, int32_t height);

		private:
			static std::pair<EventManagerImpl*, WindowImpl*> findHandlersForWindow(GLFWwindow* glfwWindow);
		private:
			/**Update glfw module.*/
			void updateImpl() override;
		};
	}
}

