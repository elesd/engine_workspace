#pragma once

#include <engine/view/Window.h>

namespace engine
{
	namespace winapi
	{
		class WindowManagerImpl;

		/** WinApi window implementation.*/
		class WindowImpl : public engine::Window
		{
			friend class engine::winapi::WindowManagerImpl;

		public:
			/**
			* Creates a winapi window
			* @param window: Created winapi window.
			* @param parameters: window creation parameter.
			* @param title: title of the window.
			*/
			WindowImpl(HWND window, const WindowParameter &parameters, const std::string &title = "Window");
			/**
			* Creates a full screened winapi window.
			* @param window: Created winapi window.
			* @param title: title of the window.
			*/
			WindowImpl(HWND window, const std::string &title = "Window");
			/**PIMPL*/
			~WindowImpl();

			/** @return Returns true if the window is valid*/
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
			* @return Returns the Windows handler.
			*/
			HWND getWindowHandler();

			/**
			* Handle the winproc event.
			* @param hWnd: winproc parameter.
			* @param message: winproc parameter.
			* @param wParam: winproc parameter.
			* @param lParam: winproc parameter.
			* @return Returns true if the event was handled
			*/
			bool handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		private:
			/** PIMPL */
			struct WindowImplPrivate *_members = nullptr;
		};
	}
}
