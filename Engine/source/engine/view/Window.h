#pragma once

#include <engine/signalSlot/Signal.h>
#include <engine/constraints/NonCopyable.h>
#include <engine/events/EventSourceBase.h>

namespace engine
{
	class Window;
	class RenderContext;
	class EventManager;
	class WindowManager;

	/**
	* Holds the creation parameter for a window.
	*/
	struct WindowParameter
	{
		/**Default construct a window parameter for holding it in different containers.*/
		WindowParameter() = default;
		/**
		* Initialize the members of the window.
		* @param x: x coordinate of the position.
		* @param y: y coordinate of the position.
		* @param width: Window's width
		* @param height: Window's height
		*/
		WindowParameter(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
			:x(x), y(y), width(width), height(height)
		{}

		/** X coordinate of the position.*/
		int32_t x;
		/** Y coordinate of the position.*/
		int32_t y;
		/** Width of the window.*/
		uint32_t width;
		/** Height of the window.*/
		uint32_t height;
	};

	/**
	* Abstract window class.
	* Based on the context and library settings this window class have different implementation.
	* The basic functionality is written here and all the cases these interface should enough.
	* The implementation of this class contains the library specific part of the window.
	*/
	class Window : public EventSourceBase
	{
		friend class WindowManager;
	public:
		/**Event source id for windows*/
		static const std::string EventSourceId;
	public:
		/** 
		* Construct a full screen window.
		* @param windowManager: The window manager pointer who created this instance.
		*/
		Window(WindowManager *windowManager);
		/**
		* Construct a window from the creation settings.
		* @param parameter: Window creation parameters.
		* @param windowManager: The window manager pointer who created this instance.
		*/
		Window(WindowManager *windowManager, const WindowParameter &parameter);

		/** Default virtual destructor.*/
		virtual ~Window();

		/**
		* @return Returns the window creation parameter.
		*/
		const WindowParameter &getParameters() const;

		/**
		* Move the window in the given position.
		* @param x: X coordinate of the new position.
		* @param y: Y coordinate of the new position.
		*/
		void setPosition(int32_t x, int32_t y);

		/**
		* Resize the window.
		* @param width: New width of the window.
		*/
		void setWidth(uint32_t width);

		/**@return Returns the width of the windows*/
		uint32_t getWidth() const;

		float getAspectRatio() const;

		/**
		* Resize the window.
		* @param height: New height of the window.
		*/
		void setHeight(uint32_t height);

		/**@return Returns the height of the windows*/
		uint32_t getHeight() const;

		/**
		* Resize the window.
		* @param width: New width of the window.
		* @param height: New height of the window.
		*/
		void setSize(uint32_t width, uint32_t height);

		/** @return Returns true if the window is full screen. */
		bool isFullScreen() const { return _fullScreen; }

		/**@return Returns the video driver of the window*/
		RenderContext* getRenderContext() const;

		/**Initilize the window with the given video driver*/
		void initRenderContext(std::unique_ptr<RenderContext>&&);

		/**
		* Updates the window and its events.
		*/
		void update();

		/** @return Returns the window's event manager.*/
		EventManager* getEventManager() const;

	protected:
		/** 
		* Setter for the window event manager.
		* It is set up during the window creation.
		* @param manager: This will be the event manager of the window.
		*/
		void setEventManager(std::unique_ptr<EventManager> &&manager);

		WindowManager *getWindowManager() const;
	private:

		/**
		* Repositioning the current window.
		* It's implementation is depend on the current library.
		* @param x: X coordinate of the new position.
		* @param y: Y coordinate of the new position.
		*/
		virtual void setPositionImp(int32_t x, int32_t y) = 0;
		/**
		* Resize the window.
		* It's implementation is depend on the current library.
		* @param width: New width of the window.
		*/
		virtual void setWidthImpl(uint32_t width) = 0;
		/**
		* Resize the window.
		* It's implementation is depend on the current library.
		* @param height: New height of the window.
		*/
		virtual void setHeightImpl(uint32_t height) = 0;
		/**
		* Resize the window.
		* It's implementation is depend on the current library.
		* @param width: New width of the window.
		* @param height: New height of the window.
		*/
		virtual void setSizeImpl(uint32_t width, uint32_t height) = 0;

	public:
		/** Signal is emitted when the window is closed. */
		engine::Signal<> windowClosed;
		/** Signal is emitted when the window's size is changed. */
		engine::Signal<uint32_t, uint32_t> windowSizeChanged;
		/** Signal is emitted when the window's frame buffer size is changed. */
		engine::Signal<uint32_t, uint32_t> windowFrameBufferSizeChanged;
		/** Signal is emitted when the window is moved in new position. */
		engine::Signal<int32_t, int32_t> windowMoved;
		/** Signal is emitted when the window get focus*/
		engine::Signal<> windowInFocus;
		/** Signal is emitted when the window lose the focus*/
		engine::Signal<> windowOutFocus;
	protected:
		/** Creation parameters.*/
		WindowParameter _parameters;
		/** Whether the window is in full screen mode.*/
		bool _fullScreen = false;

	private:
		/**PIMPL*/
		struct WindowPrivate *_members = nullptr;
	};
}
