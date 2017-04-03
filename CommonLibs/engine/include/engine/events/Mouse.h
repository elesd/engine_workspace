#pragma once

#include <engine/events/EventSourceBase.h>


#include <engine/signalSlot/Signal.h>
#include <engine/signalSlot/SlotHolder.h>

namespace engine
{
	/**Mouse buttons*/
	enum class MouseButton
	{
		Left,
		Right,
		Middle,
		EnumSize
	};
	///////////////////////////////////////////////////////////////////////
	/**State of the mouse button*/
	enum class MouseButtonState
	{
		Pressed,
		Released,
		Unknown
	};
	///////////////////////////////////////////////////////////////////////
	/**
	* Mouse implementation.
	*/
	class Mouse : public EventSourceBase,
		public SlotHolder
	{
	public:
		/**Event source id*/
		static const std::string EventSourceId;
	public:
		/**Default constructable*/
		Mouse();
		/**PIMPL*/
		~Mouse() override;

		/**@return Returns the stat of the given button*/
		MouseButtonState getButtonState(MouseButton) const;
		/**@return the signal manager of the eventManager.*/
		ISignalManager *getSignalManager() const override;
	protected:
		/**
		* Called right after the event happen in order to set the button state as soon as it is possible.
		* @param x: x coordinate of the cursor
		* @param y: y coordinate of the cursor
		*/
		void onLeftButtonPressed(int32_t x, int32_t y);
		/**
		* Called right after the event happen in order to set the button state as soon as it is possible.
		* @param x: x coordinate of the cursor
		* @param y: y coordinate of the cursor
		*/
		void onRightButtonPressed(int32_t x, int32_t y);
		/**
		* Called right after the event happen in order to set the button state as soon as it is possible.
		* @param x: x coordinate of the cursor
		* @param y: y coordinate of the cursor
		*/
		void onMiddleButtonPressed(int32_t x, int32_t y);
		/**
		* Called right after the event happen in order to set the button state as soon as it is possible.
		* @param x: x coordinate of the cursor
		* @param y: y coordinate of the cursor
		*/
		void onLeftButtonReleased(int32_t x, int32_t y);
		/**
		* Called right after the event happen in order to set the button state as soon as it is possible.
		* @param x: x coordinate of the cursor
		* @param y: y coordinate of the cursor
		*/
		void onRightButtonReleased(int32_t x, int32_t y);
		/**
		* Called right after the event happen in order to set the button state as soon as it is possible.
		* @param x: x coordinate of the cursor
		* @param y: y coordinate of the cursor
		*/
		void onMiddleButtonReleased(int32_t x, int32_t y);
	public:
		/**Signal emitted when the mouse moved*/
		Signal<int32_t /*x*/, int32_t /*y*/> moved;

		/**Signal emitted when the left mouse button pressed*/
		Signal<int32_t /*x*/, int32_t /*y*/> leftButtonPressed;
		/**Signal emitted when the right mouse button pressed*/
		Signal<int32_t /*x*/, int32_t /*y*/> rightButtonPressed;
		/**Signal emitted when the middle mouse button pressed*/
		Signal<int32_t /*x*/, int32_t /*y*/> middleButtonPressed;

		/**Signal emitted when the left mouse button released*/
		Signal<int32_t /*x*/, int32_t /*y*/> leftButtonReleased;
		/**Signal emitted when the right mouse button released*/
		Signal<int32_t /*x*/, int32_t /*y*/> rightButtonReleased;
		/**Signal emitted when the middle mouse button released*/
		Signal<int32_t /*x*/, int32_t /*y*/> middleButtonReleased;
		
		/**Signal emitted when the mouse wheel moved*/
		Signal<int32_t /*x*/, int32_t /*y*/, int32_t /*scrollAmount*/ > scrolled;
	private:
		/**PIMPL*/
		struct MousePrivate *_members = nullptr;
	};
}