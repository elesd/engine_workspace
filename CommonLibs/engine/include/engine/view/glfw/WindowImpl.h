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
		public:
			/**
			* Creates a glfw window
			* @param window: Created glfw window.
			* @param parameters: window creation parameter.
			* @param title: title of the window.
			*/
			WindowImpl(WindowManager *windowManager, GLFWwindow *window, const WindowParameter &parameters, const std::string &title = "Window");
			/**
			* Creates a full screened glfw window.
			* @param window: Created glfw window.
			* @param title: title of the window.
			*/
			WindowImpl(WindowManager *windowManager, GLFWwindow *window, const std::string &title = "Window");

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

			/**
			* @return Returns the glfw window.
			*/
			GLFWwindow *getGlfwWindow();

			void handleWindowClosedEvent();
			void handleWindowResizedEvent(int32_t width, int32_t height);
			void handleWindowMovedEvent(int32_t x, int32_t y);
			void handleWindowFocusEvent(int32_t focused);
			void handleWindowFrameBufferResizeEvent(int32_t width, int32_t height);

		private:
			/**PIMPL*/
			struct WindowImplPrivate *_members = nullptr;
		};
	}
}
