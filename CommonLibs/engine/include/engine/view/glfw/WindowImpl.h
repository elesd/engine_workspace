#pragma once

#include <engine/view/Window.h>

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
			/**
			* Creates a glfw window
			* @param window: Created glfw window.
			* @param parameters: window creation parameter.
			* @param title: title of the window.
			*/
			WindowImpl(GLFWwindow *window, const WindowParameter &parameters, const std::string &title = "Window");
			/**
			* Creates a full screened glfw window.
			* @param window: Created glfw window.
			* @param title: title of the window.
			*/
			WindowImpl(GLFWwindow *window, const std::string &title = "Window");

			/**PIMPL*/
			~WindowImpl();

			/**
			* @return Returns true if the window is created successfuly.
			*/
			operator bool() const;
			/**Set the position of the window*/
			void setPositionImp(int32_t, int32_t) override;
			/**Set the width of the window*/
			void setWidthImpl(uint32_t) override;
			/**Set the height of the window*/
			void setHeightImpl(uint32_t) override;
			/**
			* Set the window's dimension
			* @param width: new window width
			* @param height: new window height
			*/
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
