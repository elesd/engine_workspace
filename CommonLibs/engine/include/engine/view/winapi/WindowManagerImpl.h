#pragma once

#include <engine/view/WindowManager.h>

#include <Windows.h>
namespace engine
{
	namespace winapi
	{
		class WindowImpl;
		/**WinApi Window manager implementation.*/
		class WindowManagerImpl : public WindowManager
		{
		public:
			/**Default constructable*/
			WindowManagerImpl();
			/**PIMPL*/
			~WindowManagerImpl()  override;
			/**
			* @param hWnd: Window handler
			* @return Returns the window with the given window handler
			*/
			WindowImpl *findWindowById(HWND hWnd) const;

			/**@return Returns the number of monitors.*/
			uint32_t getMonitorCount() const override;
			/**@return Returns the id of the monitor*/
			uint32_t getMainMonitorId() const override;
		protected:
			/**
			* Creates a main window in winapi environment.
			* @param parameters: Window creation parameters
			* @param title: Title of the window
			* @return Returns the created winapi window
			*/
			Window *createMainWindowImpl(const WindowParameter &parameters,
										 const std::string &title) override;
			/**
			* Creates a full screen main window in winapi environment.
			* @param width: pixel width of the window.
			* @param height: pixel height of the window
			* @param title: Title of the window
			* @param monitorId: Id of the monitor where the window will be created.
			* @return Returns the created winapi window
			*/
			Window *createFullScreenMainWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId) override;

			/**
			* Creates a secondary window in winapi environment.
			* @param parameters: Window creation parameters
			* @param title: Title of the window
			* @param mainWindow: The main window of the application.
			* @return Returns the created winapi window
			*/
			Window *createSecondaryWindowImpl(const WindowParameter &parameters,
											  const std::string &title,
											  Window *mainWindow) override;
			
			/**
			* Creates a full screen main window in winapi environment.
			* @param width: pixel width of the window.
			* @param height: pixel height of the window
			* @param title: Title of the window
			* @param monitorId: Id of the monitor where the window will be created.
			* @param mainWindow: The main window of the application.
			* @return Returns the created winapi window
			*/
			Window *createSecondaryFullScreenWindowImpl(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId, Window *mainWindow) override;

			/**
			* Creates a driver for the given window.
			* @param params: Driver initialization parameters.
			* @param window: The driver will created to this window.
			* @return Returns the driver which was created for the given window.
			*/
			std::unique_ptr<Driver> createDriverForWindow(const DriverInitParameters &params, Window *window) const override;

		private:
			/** @copydoc */
			bool driverNeedsWindow() const override { return true; }
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
