#pragma once

#include <engine/events/EventSourceBase.h>

#include <engine/constraints/NonCopyable.h>

#include <engine/signalSlot/Signal.h>
#include <engine/signalSlot/SignalManager.h>
namespace engine
{
	enum class KeyState
	{
		Pressed,
		Released,
		Unknown
	};
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


	class Keyboard : public EventSourceBase,
					 public SlotHolder
	{
	public:
		static const std::string EventSourceId;
		static std::string KeyboardButtonToString(KeyboardButton button);
	public:
		Keyboard();
		~Keyboard() override;

		Keyboard(Keyboard &&o);
		Keyboard& operator=(Keyboard &&o);

		KeyState getKeyState(KeyboardButton button) const;
		ISignalManager *getSignalManager() const override;

	protected:
		void onKeyPressed(KeyboardButton);
		void onKeyReleased(KeyboardButton);
	public:
		Signal<KeyboardButton> keyPressed;
		Signal<KeyboardButton> keyReleased;
	private:
		struct KeyboardPrivate* _members = nullptr;
	};
}