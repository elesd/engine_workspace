#pragma once

#include <engine/events/EventSourceBase.h>

#include <engine/constraints/NonCopyable.h>

#include <engine/signalSlot/Signal.h>
#include <engine/signalSlot/SignalManager.h>
namespace engine
{
	/**Key state of the keyboard*/
	enum class KeyState
	{
		Pressed,
		Released,
		Unknown
	};
	/**Buttons of the keyboard*/
	enum class KeyboardButton
	{
		Key_Esc,
		Key_Enter,
		Key_LCtrl,
		Key_LWindows,
		Key_RWindows,
		Key_Alt,
		Key_Space,
		Key_RCtrl,
		Key_LShift,
		Key_RShift,
		Key_CapsLock,
		Key_Backspace,
		Key_Tab,

		Key_PrintScreen,
		Key_ScrollLock,
		Key_Pause,

		Key_Insert,
		Key_Delete,
		Key_Home,
		Key_End,
		Key_PageUp,
		Key_PageDown,

		Key_NumLock,
		Key_NumDevied,		/* / */
		Key_NumMultiply,	/* * */
		Key_NumMinus,		/* - */
		Key_NumPlus,		/* + */
		Key_NumEnter,
		Key_NumDecimal,		/* . */
		Key_Num0,
		Key_Num1,
		Key_Num2,
		Key_Num3,
		Key_Num4,
		Key_Num5,
		Key_Num6,
		Key_Num7,
		Key_Num8,
		Key_Num9,

		Key_F1,
		Key_F2,
		Key_F3,
		Key_F4,
		Key_F5,
		Key_F6,
		Key_F7,
		Key_F8,
		Key_F9,
		Key_F10,
		Key_F11,
		Key_F12,

		Key_A,
		Key_B,
		Key_C,
		Key_D,
		Key_E,
		Key_F,
		Key_G,
		Key_H,
		Key_I,
		Key_J,
		Key_K,
		Key_L,
		Key_M,
		Key_N,
		Key_O,
		Key_P,
		Key_Q,
		Key_R,
		Key_S,
		Key_T,
		Key_U,
		Key_V,
		Key_W,
		Key_X,
		Key_Y,
		Key_Z,

		Key_0,
		Key_1,
		Key_2,
		Key_3,
		Key_4,
		Key_5,
		Key_6,
		Key_7,
		Key_8,
		Key_9,

		Key_GraveAccent,	/* ` */
		Key_Plus,			/* + */
		Key_Minus,			/* - */
		Key_Equal,			/* = */
		Key_LeftBracket,	/* [ */
		Key_RightBracket,	/* ] */
		Key_Apostrophe,		/* ' */
		Key_Semicolon,		/* ; */
		Key_Backslash,		/* \ */
		Key_Comma,			/* , */
		Key_Period,			/* . */
		Key_Slash,			/* / */

		Key_Up,
		Key_Down,
		Key_Left,
		Key_Right,

		EnumSize
	};		

	/**
	Base keyboard
	*/
	class Keyboard : public EventSourceBase,
					 public SlotHolder
	{
	public:
		/**Event source id for the event manager*/
		static const std::string EventSourceId;
		/**String conversion function for debug*/
		static std::string KeyboardButtonToString(KeyboardButton );
	public:
		/**PIMPL*/
		Keyboard();
		/**PIMPL*/
		~Keyboard() override;

		/**PIMPL*/
		Keyboard(Keyboard &&o);
		/**PIMPL*/
		Keyboard& operator=(Keyboard &&o);

		/**
		@return Returns the state of the given button
		*/
		KeyState getKeyState(KeyboardButton) const;

		/**
		@copydoc
		*/
		ISignalManager *getSignalManager() const override;

	protected:
		/**
		Slot for keyboard pressed to set keystate inmediatly
		*/
		void onKeyPressed(KeyboardButton);
		/**
		Slot for keyboard released to set keystate inmediatly
		*/
		void onKeyReleased(KeyboardButton);
	public:
		/**Emitted when a key is pressed*/
		Signal<KeyboardButton> keyPressed;
		/**Emitted when a key is released*/
		Signal<KeyboardButton> keyReleased;
	private:
		/**PIMPL*/
		struct KeyboardPrivate* _members = nullptr;
	};
}