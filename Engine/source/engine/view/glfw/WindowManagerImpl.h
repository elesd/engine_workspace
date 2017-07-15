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
			/**Default constructable*/
			WindowManagerImpl() = default;

			/** @copydoc */
			uint32_t getMonitorCount() const override;
			/** @copydoc */
			uint32_t getMainMonitorId() const override;
			/** 
			* Search the corresponding window wrapper for a given glfw window.
			* @param window: glfwWindow.
			* @return Returns nullptr if the window was not found otherwise the corresponding WindowImpl.
			*/
			WindowImpl *findWindow(GLFWwindow *window);
		protected:
			/** @copydoc */
			Window *createMainWindowImpl(const WindowParameter &parameters, const std::string &title) override;
			/** @copydoc */
			Window *createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId) override;
			/** @copydoc */
			Window *createSecondaryWindowImpl(const WindowParameter &parameters, const std::string &title, Window *mainWindow) override;
			/** @copydoc */
			Window *createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow) override;
			/** @copydoc */
			std::unique_ptr<RenderContext> createRenderContext(const RenderContextParameters &params, Window *) const override;
			std::unique_ptr<RenderContext> preCreateRenderContext(const RenderContextParameters &) const override;
			void postCreateRenderContext(RenderContext* renderContext, const RenderContextParameters& params, Window* window) const override;
		private:
			/** @copydoc */
			bool driverNeedsWindow() const override { return false; }
		};
	}
}
