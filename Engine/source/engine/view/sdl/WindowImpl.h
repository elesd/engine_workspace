#pragma once

#include <engine/view/Window.h>

struct SDL_Window;
struct SDL_WindowEvent;

namespace engine
{
	namespace sdl
	{
		class WindowManagerImpl;

		/**
		* Sdl Window implementation.
		*/
		class WindowImpl : public engine::Window
		{
			friend class engine::sdl::WindowManagerImpl;
		public:
			/**
			* Creates an sdl window
			* @param window: Created sdl window.
			* @param parameters: window creation parameter.
			* @param title: title of the window.
			*/
			WindowImpl(WindowManager *windowManager, SDL_Window *window, const WindowParameter &parameters, const std::string &title = "Window");
			/**
			* Creates a full screened sdl window
			* @param window: Created sdl window.
			* @param title: title of the window.
			*/
			WindowImpl(WindowManager *windowManager, SDL_Window *window, const std::string &title = "Window");

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
			* @return Returns the Sdl window.
			*/
			SDL_Window *getSDLWindow();

			void handleEvent(const SDL_WindowEvent& event);
		private:
			/**PIMPL*/
			struct WindowImplPrivate *_members = nullptr;
		};
	}
}
