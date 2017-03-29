#pragma once

#include <engine/events/EventSourceBase.h>


#include <engine/signalSlot/Signal.h>
#include <engine/signalSlot/SlotHolder.h>

namespace engine
{
	enum class MouseButton
	{
		Left,
		Right,
		Middle,
		EnumSize
	};
	///////////////////////////////////////////////////////////////////////
	enum class MouseButtonState
	{
		Pressed,
		Released,
		Unknown
	};
	///////////////////////////////////////////////////////////////////////
	class Mouse : public EventSourceBase,
		public SlotHolder
	{
	public:
		static const std::string EventSourceId;
	public:
		Mouse();
		~Mouse() override;

		MouseButtonState getButtonState(MouseButton) const;
		ISignalManager *getSignalManager() const override;
	protected:
		void onLeftButtonPressed(int32_t x, int32_t y);
		void onRightButtonPressed(int32_t x, int32_t y);
		void onMiddleButtonPressed(int32_t x, int32_t y);
		void onLeftButtonReleased(int32_t x, int32_t y);
		void onRightButtonReleased(int32_t x, int32_t y);
		void onMiddleButtonReleased(int32_t x, int32_t y);
	public:
		Signal<int32_t /*x*/, int32_t /*y*/> moved;

		Signal<int32_t /*x*/, int32_t /*y*/> leftButtonPressed;
		Signal<int32_t /*x*/, int32_t /*y*/> rightButtonPressed;
		Signal<int32_t /*x*/, int32_t /*y*/> middleButtonPressed;

		Signal<int32_t /*x*/, int32_t /*y*/> leftButtonReleased;
		Signal<int32_t /*x*/, int32_t /*y*/> rightButtonReleased;
		Signal<int32_t /*x*/, int32_t /*y*/> middleButtonReleased;
		
		Signal<int32_t /*x*/, int32_t /*y*/, int32_t /*scrollAmount*/ > scrolled;
	private:
		struct MousePrivate *_members = nullptr;
	};
}