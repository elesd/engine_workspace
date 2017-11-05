#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Driver;
	class EventManagerFactory;
	class RenderContext;
	class GlobalResourceMapping;
	class Window;
	struct DeviceParameters;
	struct RenderContextParameters;
	struct WindowParameter;

	/**
	* Class for manage window creation and windows connected functionality.
	*/
	class WindowManager 
		: private NonCopyable
		, private NonMoveable
	{
	public:
		/** Default constructable. */
		WindowManager(const DeviceParameters& parameters, const GlobalResourceMapping& resourceMapping, std::unique_ptr<EventManagerFactory>&& eventManagerFactory);
		/** Destructor for PIMPL */
		virtual ~WindowManager();

		/**
		* Update its windows.
		*/
		void update();

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
		std::vector<Window*> getAllWindows() const;

		/**
		* Set the default driver creation parameters.
		* When a new window is created a driver will be attached to it. This is the driver creation parameters.
		* It will use when the next window is created.
		* @param defaultParameters: driver creation parameters
		*/
		void setRenderContextParameter(const RenderContextParameters &defaultParameters);

		void windowClosed(Window *window);

	protected:
		const DeviceParameters& getDeviceParameters() const;

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
		virtual Window *createSecondaryWindowImpl(const WindowParameter &parameters, const std::string &title, Window *mainWindow) = 0;

		/**
		* Window system dependent creation function.
		* @param width: width of the window in pixels
		* @param height: height of the window in pixels
		* @param title: title of the window
		* @param monitorId: id of the monitor where the window will created.
		* @param mainWindow: Main window, the secondary window shares the main window context.
		*/
		virtual Window *createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow) = 0;

		
		virtual std::unique_ptr<Driver> createDriver(const DeviceParameters&) const = 0;
		virtual std::unique_ptr<RenderContext> createRenderContext(std::unique_ptr<Driver>&& driver) const = 0;

		virtual void preInitCreation(Driver* driver, RenderContext* renderContext, const RenderContextParameters &) const = 0;
		virtual void postInitCreation(Driver* driver, RenderContext* renderContext, const RenderContextParameters &, Window* window) const = 0;
	private:

		/**
		* Creates a secondary window with the given parameter and title.
		* @param parameters: Window creation parameters.
		* @param title: title of the window
		* @param mainWindow: Main window, the secondary window shares the main window context.
		* @todo: Implement sharing render context
		*/
		DEPRECATED(Window *createSecondaryWindow(const WindowParameter &parameters, const std::string &title, Window *mainWindow));

		/**
		* Creates a secondary full screened window with the given parameter and title.
		* @param width: width of the window in pixels
		* @param height: height of the window in pixels
		* @param title: title of the window
		* @param monitorId: id of the monitor where the window will created.
		* @param mainWindow: Main window, the secondary window shares the main window context.
		* @todo: Implement sharing render context
		*/
		DEPRECATED(Window *createSecondaryFullScreenWindow(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow));

		/**
		* Common initialization of a window.
		* @param window: Window to be initialized
		*/
		void initWindow(Window *window);

		void eraseClosedWindows();
	private:
		/**PIMPL*/
		struct WindowManagerPrivate *_members = nullptr;
	};
}
