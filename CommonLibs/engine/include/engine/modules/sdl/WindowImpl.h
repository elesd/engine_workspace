#pragma once

#include "engine/view/Window.h"

struct SDL_Window;

namespace engine
{
	namespace sdl
	{
		class WindowManagerImpl;

		/**
		* Sdl Window implementation.
		*/
		class WindowImpl: public engine::view::Window
		{
			friend class engine::sdl::WindowManagerImpl;
		public:
			WindowImpl(SDL_Window *window, const view::WindowParameter &parameters, const std::string &title = "Window");
			/** @todo add width, height*/
			WindowImpl(SDL_Window *window, const std::string &title = "Window");
			~WindowImpl() ;
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
			* @return Returns the Sdl window.
			*/
			SDL_Window *getSDLWindow();
		private:
			/**PIMPL*/
			struct WindowImplPrivate *_members = nullptr;
		};
	}
}
