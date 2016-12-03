#pragma once

#include "engine/view/Window.h"

struct GLFWwindow;

namespace engine
{
	namespace glfw
	{
		class WindowManagerImpl;

		/**
		* Glfw Window implementation.
		*/
		class WindowImpl : public engine::Window
		{
			friend class engine::glfw::WindowManagerImpl;
		public:
			WindowImpl(GLFWwindow *window, const WindowParameter &parameters, const std::string &title = "Window");
			WindowImpl(GLFWwindow *window, const std::string &title = "Window");
			~WindowImpl();

			/**
			* @return Returns true if the window is created successfuly.
			*/
			operator bool() const;
			void setPositionImp(int32_t x, int32_t y) override;
			void setWidthImpl(uint32_t width) override;
			void setHeightImpl(uint32_t height) override;
			void setSizeImpl(uint32_t width, uint32_t height) override;

		private:
			/**
			* @return Returns the glfw window.
			*/
			GLFWwindow *getGlfwWindow();
		private:
			/**PIMPL*/
			struct WindowImplPrivate *_members = nullptr;
		};
	}
}
