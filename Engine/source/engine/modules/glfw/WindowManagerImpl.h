#pragma once

#include "engine/view/WindowManager.h"

namespace engine
{
	namespace glfw
	{
		/**
		* Glfw window manager implementation.
		*/
		class WindowManagerImpl: public view::WindowManager
		{
		public:
			WindowManagerImpl() = default;

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
		};
	}
}