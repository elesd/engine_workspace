#pragma once

#include "engine/constraints/NonCopyable.h"

namespace engine
{
	namespace view
	{
		struct WindowParameter;
		class Window;

		/**
		* Class for manage window creation and windows connected functionality.
		*/
		class WindowManager: constraints::NonCopyable
		{
		public:
			/** Default constructable. */
			WindowManager();
			/** Destructor for PIMPL */
			virtual ~WindowManager() ;

			/**
			* @return Returns the number of available monitors.
			*/
			virtual uint32_t getMonitorCount() const = 0;
			/**
			* @return Return the main monitor id.
			*/
			virtual uint32_t getMainMonitorId() const = 0;

			/**
			* Creates a main window with the given parameter and title.
			* @param parameters: Window creation parameters.
			* @param title: title of the window
			*/
			Window *createMainWindow(const WindowParameter &parameters,
				const std::string &title);

			/**
			* Creates a main full screened window with the given parameter and title.
			* @param width: width of the window in pixels
			* @param height: height of the window in pixels
			* @param title: title of the window
			* @param monitorId: id of the monitor where the window will created.
			*/
			Window *createFullScreenMainWindow(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId);

			/**
			* Creates a secondary window with the given parameter and title.
			* @param parameters: Window creation parameters.
			* @param title: title of the window
			* @param mainWindow: Main window, the secondary window shares the main window context.
			*/
			Window *createSecondaryWindow(const WindowParameter &parameters,
				const std::string &title,
				Window *mainWindow);

			/**
			* Creates a secondary full screened window with the given parameter and title.
			* @param width: width of the window in pixels
			* @param height: height of the window in pixels
			* @param title: title of the window
			* @param monitorId: id of the monitor where the window will created.
			* @param mainWindow: Main window, the secondary window shares the main window context.
			*/
			Window *createSecondaryFullScreenWindow(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow);

			/**
			* Destroy the given window.
			*/
			void destroyWindow(Window *);

			/**
			* @return Returns the main window.
			*/
			Window *getMainWindow();

			/**
			* @return Returns the main window.
			*/
			const Window *getMainWindow() const;

			/**
			* @return Returns all created window.
			*/
			std::vector<const Window*> getAllWindows() const;

			/**
			* @return Returns all created window.
			*/
			std::vector<Window*> getAllWindows();

		protected:
			/**
			* Window system dependent creation function.
			* @param parameters: Window creation parameters.
			* @param title: title of the window
			*/
			virtual Window *createMainWindowImpl(const WindowParameter &parameters,
				const std::string &title) = 0;

			/**
			* Window system dependent creation function.
			* This function must create a full screen window with the given parameters.
			* @param width : width of the window in pixels
			* @param height : height of the window in pixels
			* @param title : title of the window
			* @param monitorId : id of the monitor where the window will created.
			*/
			virtual Window *createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId) = 0;

			/**
			* Window system dependent creation function.
			* @param parameters: Window creation parameters.
			* @param title: title of the window
			* @param mainWindow: Main window, the secondary window shares the main window context.
			*/
			virtual Window *createSecondaryWindowImpl(const WindowParameter &parameters,
				const std::string &title,
				Window *mainWindow) = 0;

			/**
			* Window system dependent creation function.
			* @param width: width of the window in pixels
			* @param height: height of the window in pixels
			* @param title: title of the window
			* @param monitorId: id of the monitor where the window will created.
			* @param mainWindow: Main window, the secondary window shares the main window context.
			*/
			virtual Window *createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow) = 0;
		private:
			struct WindowManagerPrivate *_members = nullptr;
		};
	}
}
