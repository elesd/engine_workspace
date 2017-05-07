#pragma once

#include <engine/view/WindowManager.h>

struct GLFWwindow;

namespace engine
{
	namespace glfw
	{
		class WindowImpl;
		/**
		* Glfw window manager implementation.
		*/
		class WindowManagerImpl : public WindowManager
		{
		public:
			WindowManagerImpl() = default;

			uint32_t getMonitorCount() const override;
			uint32_t getMainMonitorId() const override;
			WindowImpl *findWindow(GLFWwindow *window);
		protected:
			Window *createMainWindowImpl(const WindowParameter &parameters,
											   const std::string &title) override;
			Window *createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId) override;
			Window *createSecondaryWindowImpl(const WindowParameter &parameters,
													const std::string &title,
													Window *mainWindow) override;
			Window *createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow) override;
			std::unique_ptr<Driver> createDriverForWindow(const DriverInitParameters &params, Window *) const override;
		private:
			bool driverNeedsWindow() const override { return false; }

		};
	}
}
