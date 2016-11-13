#pragma once

#include "engine/view/Window.h"

#include <windows.h>

namespace engine
{
	namespace winapi
	{
		class WindowManagerImpl;

		/** WinApi window implementation.*/
		class WindowImpl: public engine::view::Window
		{
			friend class engine::winapi::WindowManagerImpl;
		public:
			WindowImpl(HWND window, const view::WindowParameter &parameters, const std::string &title = "Window");
			WindowImpl(HWND window, const std::string &title = "Window");
			~WindowImpl();

			/** @return Returns true if the window is valid*/
			operator bool() const;
			void setPositionImp(int32_t x, int32_t y) override;
			void setWidthImpl(uint32_t width) override;
			void setHeightImpl(uint32_t height) override;
			void setSizeImpl(uint32_t width, uint32_t height) override;

		private:
			/**
			* @return Returns the Windows handler.
			*/
			HWND getWindowHandler();
		private:
			/** PIMPL */
			struct WindowImplPrivate *_members = nullptr;
		};
	}
}
