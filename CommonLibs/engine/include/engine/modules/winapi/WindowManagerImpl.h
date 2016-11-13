#pragma once

#include "engine/view/WindowManager.h"

namespace engine
{
	namespace winapi
	{
		/**WinApi Window manager implementation.*/
		class WindowManagerImpl: public view::WindowManager
		{
		public:
			WindowManagerImpl();
			~WindowManagerImpl()  override;
			uint32_t getMonitorCount() const override;
			uint32_t getMainMonitorId() const override;
		protected:
			view::Window *createMainWindowImpl(const view::WindowParameter &parameters,
										 const std::string &title) override;
			view::Window *createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId) override;
			view::Window *createSecondaryWindowImpl(const view::WindowParameter &parameters,
				  							  const std::string &title,
											  view::Window *mainWindow) override;
			view::Window *createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, view::Window *mainWindow) override;
		private:
			/**
			* Register the window class in Windows based on the application parameters.
			*/
			void RegisterWindowClass();
		private:
			/**PIMPL*/
			struct WindowManagerImplPrivate *_members = nullptr;
		};
	}
}
