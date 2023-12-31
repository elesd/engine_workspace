#pragma once

#include <engine/view/WindowManager.h>

struct SDL_WindowEvent;

namespace engine
{
	struct RenderContextParameters;
	struct DeviceParameters;
	class RenderContext;
	class GlobalResourceMapping;
	class Window;
	namespace sdl
	{
		class WindowImpl;
		/** SDL window manager implementation.*/
		class WindowManagerImpl : public WindowManager
		{
		public:
			WindowManagerImpl(const DeviceParameters& driverContextParameters, const GlobalResourceMapping& resourceMapping);

			/** @copydoc */
			uint32_t getMonitorCount() const override;
			/** @copydoc */
			uint32_t getMainMonitorId() const override;
			/**
			* Finds a window for the sdl window id.
			* @param id: sdl window id.
			* @return Returns nullptr if it is not found, otherwise the corresponding window.
			*/
			WindowImpl *findWindowBySDLId(uint32_t id) const;
			/** Handles window events.*/
			void handleEvent(const SDL_WindowEvent&);
		private:
			/** @copydoc */
			Window *createMainWindowImpl(const WindowParameter &parameters, const std::string &title) override;
			/** @copydoc */
			Window *createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId) override;
			/** @copydoc */
			Window *createSecondaryWindowImpl(const WindowParameter &parameters, const std::string &title, Window *mainWindow) override;
			/** @copydoc */
			Window *createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow) override;

			std::unique_ptr<Driver> createDriver(const DeviceParameters&) const override;
			/** @copydoc */
			std::unique_ptr<RenderContext> createRenderContext(std::unique_ptr<Driver>&& driver) const override;
			void preInitCreation(Driver* driver, RenderContext* renderContext, const RenderContextParameters &params) const override;
			void postInitCreation(Driver* driver, RenderContext* renderContext, const RenderContextParameters &params, Window* window) const override;
		};
	}
}
