#include <stdafx.h>
#include <engine/events/Keyboard.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/signalSlot/SignalManager.h>
#include <engine/Context.h>
#include <engine/app/Application.h>
#include <engine/events/EventManager.h>

namespace engine
{
	struct KeyboardPrivate
	{
		std::vector<KeyboardButton> pressedKeys;
	};

	const std::string Keyboard::EventSourceId = "Keyboard";

	std::string Keyboard::KeyboardButtonToString(KeyboardButton button)
	{
		static const std::vector<std::string> enumToString =
		{
			"Key_Esc",
			"Key_Enter",
			"Key_LCtrl",
			"Key_LWindows",
			"Key_RWindows",
			"Key_Alt",
			"Key_Space",
			"Key_RCtrl",
			"Key_LShift",
			"Key_RShift",
			"Key_CapsLock",
			"Key_Backspace",
			"Key_Tab",
			"Key_PrintScreen",
			"Key_ScrollLock",
			"Key_Pause",
			"Key_Insert",
			"Key_Delete",
			"Key_Home",
			"Key_End",
			"Key_PageUp",
			"Key_PageDown",
			"Key_NumLock",
			"Key_NumDevied",		/* / */
			"Key_NumMultiply",	/* * */
			"Key_NumMinus",		/* - */
			"Key_NumPlus",		/* + */
			"Key_NumEnter",
			"Key_NumDecimal",		/* . */
			"Key_Num0",
			"Key_Num1",
			"Key_Num2",
			"Key_Num3",
			"Key_Num4",
			"Key_Num5",
			"Key_Num6",
			"Key_Num7",
			"Key_Num8",
			"Key_Num9",
			"Key_F1",
			"Key_F2",
			"Key_F3",
			"Key_F4",
			"Key_F5",
			"Key_F6",
			"Key_F7",
			"Key_F8",
			"Key_F9",
			"Key_F10",
			"Key_F11",
			"Key_F12",
			"Key_A",
			"Key_B",
			"Key_C",
			"Key_D",
			"Key_E",
			"Key_F",
			"Key_G",
			"Key_H",
			"Key_I",
			"Key_J",
			"Key_K",
			"Key_L",
			"Key_M",
			"Key_N",
			"Key_O",
			"Key_P",
			"Key_Q",
			"Key_R",
			"Key_S",
			"Key_T",
			"Key_U",
			"Key_V",
			"Key_W",
			"Key_X",
			"Key_Y",
			"Key_Z",
			"Key_0",
			"Key_1",
			"Key_2",
			"Key_3",
			"Key_4",
			"Key_5",
			"Key_6",
			"Key_7",
			"Key_8",
			"Key_9",
			"Key_GraveAccent",	/* ` */
			"Key_Plus",			/* + */
			"Key_Minus",			/* - */
			"Key_Equal",			/* = */
			"Key_LeftBracket",	/* [ */
			"Key_RightBracket",	/* ] */
			"Key_Apostrophe",		/* ' */
			"Key_Semicolon",		/* ; */
			"Key_Backslash",		/* \ */
			"Key_Comma",			/* , */
			"Key_Period",			/* . */
			"Key_Slash",			/* / */
			"Key_Up",
			"Key_Down",
			"Key_Left",
			"Key_Right",
			"EnumSize"
		};
		return enumToString[size_t(button)];
	}

	Keyboard::Keyboard()
		: EventSourceBase(EventSourceId),
		_members(new KeyboardPrivate())
	{
	}

	Keyboard::~Keyboard()
	{
		delete _members;
		_members = nullptr;
	}

	Keyboard::Keyboard(Keyboard &&o)
		:EventSourceBase(EventSourceId),
		_members(o._members)
	{
		o._members = nullptr;
	}

	Keyboard& Keyboard::operator=(Keyboard &&o)
	{
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	ISignalManager *Keyboard::getSignalManager() const
	{
		return Context::getInstance()->getApplication()->getEventManager()->getEventsSignalManager();
	}

	void Keyboard::onKeyPressed(KeyboardButton button)
	{
		auto it = std::find(_members->pressedKeys.begin(),
							_members->pressedKeys.end(),
							button);
		// cannot emit 2 times the press event for the same key.
		_members->pressedKeys.push_back(button);
	}

	void Keyboard::onKeyReleased(KeyboardButton button)
	{
		auto it = std::find(_members->pressedKeys.begin(),
							_members->pressedKeys.end(),
							button);
		if(it != _members->pressedKeys.end())
		{
			_members->pressedKeys.erase(it);
		}
	}

	KeyState Keyboard::getKeyState(KeyboardButton button) const
	{
		auto it = std::find(_members->pressedKeys.begin(),
							_members->pressedKeys.end(),
							button);
		return it != _members->pressedKeys.end()
						? KeyState::Pressed 
						: KeyState::Released;
	}
}