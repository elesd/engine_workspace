#include <stdafx.h>

#if ENGINE_USE_WINAPI
#include <engine/events/winapi/KeyboardImpl.h>

namespace
{
	struct KeyParam
	{
		unsigned int repeatCount : 16;
		unsigned int scanCode : 8;
		unsigned int isExtended : 1, :4;
		unsigned int contextCode : 1;
		unsigned int prevKeyState : 1;
		unsigned int transitionState : 1;
	};

	KeyParam parseParam(uint32_t param)
	{
		KeyParam keyParam;
		memcpy(&keyParam, &param, sizeof(KeyParam));
		return keyParam;
	}

	engine::KeyboardButton parseButton(WPARAM wParam, bool isExtended)
	{
		using engine::KeyboardButton;
		KeyboardButton result = KeyboardButton::EnumSize;
		switch(wParam)
		{
			case 0x08: result = KeyboardButton::Key_Backspace; break;
			case 0x09: result = KeyboardButton::Key_Tab; break;
			case 0x0D: result = KeyboardButton::Key_Enter; break;
			case 0x10: result = isExtended ? KeyboardButton::Key_RShift : KeyboardButton::Key_LShift; break;
			case 0x11: result = isExtended ? KeyboardButton::Key_RCtrl : KeyboardButton::Key_LCtrl; break;
			case 0x12: result = KeyboardButton::Key_Alt; break;
			case 0x13: result = KeyboardButton::Key_Pause; break;
			case 0x14: result = KeyboardButton::Key_CapsLock; break;
			case 0x1B: result = KeyboardButton::Key_Esc; break;
			case 0x20: result = KeyboardButton::Key_Space; break;
			case 0x21: result = KeyboardButton::Key_PageUp; break;
			case 0x22: result = KeyboardButton::Key_PageDown; break;
			case 0x23: result = KeyboardButton::Key_End; break;
			case 0x24: result = KeyboardButton::Key_Home; break;
			case 0x25: result = KeyboardButton::Key_Left; break;
			case 0x26: result = KeyboardButton::Key_Up; break;
			case 0x27: result = KeyboardButton::Key_Right; break;
			case 0x28: result = KeyboardButton::Key_Down; break;
			case 0x2C: result = KeyboardButton::Key_PrintScreen; break;
			case 0x2D: result = KeyboardButton::Key_Insert; break;
			case 0x2E: result = KeyboardButton::Key_Delete; break;
			case 0x30:
			case 0x31:
			case 0x32:
			case 0x33:
			case 0x34:
			case 0x35:
			case 0x36:
			case 0x37:
			case 0x38:
			case 0x39:
				result = KeyboardButton(uint32_t(KeyboardButton::Key_0) + (wParam - 0x30));	break;
			case 0x41:
			case 0x42:
			case 0x43:
			case 0x44:
			case 0x45:
			case 0x46:
			case 0x47:
			case 0x48:
			case 0x49:
			case 0x4A:
			case 0x4B:
			case 0x4C:
			case 0x4D:
			case 0x4E:
			case 0x4F:
			case 0x50:
			case 0x51:
			case 0x52:
			case 0x53:
			case 0x54:
			case 0x55:
			case 0x56:
			case 0x57:
			case 0x58:
			case 0x59:
			case 0x5A:
				result = KeyboardButton(uint32_t(KeyboardButton::Key_A) + (wParam - 0x41));	break;
			case 0x5B: result = KeyboardButton::Key_LWindows; break;
			case 0x5C: result = KeyboardButton::Key_RWindows; break;
			case 0x60:
			case 0x61:
			case 0x62:
			case 0x63:
			case 0x64:
			case 0x65:
			case 0x66:
			case 0x67:
			case 0x68:
			case 0x69:
				result = KeyboardButton(uint32_t(KeyboardButton::Key_Num0) + (wParam - 0x60));	break;
			case 0x6A: result = KeyboardButton::Key_NumMultiply; break;
			case 0x6B: result = KeyboardButton::Key_NumPlus; break;
			case 0x6D: result = KeyboardButton::Key_NumMinus; break;
			case 0x6E: result = KeyboardButton::Key_NumDecimal; break;
			case 0x6F: result = KeyboardButton::Key_NumDevied; break;
			case 0x70:
			case 0x71:
			case 0x72:
			case 0x73:
			case 0x74:
			case 0x75:
			case 0x76:
			case 0x77:
			case 0x78:
			case 0x79:
			case 0x7A:
			case 0x7B:
				result = KeyboardButton(uint32_t(KeyboardButton::Key_F1) + (wParam - 0x70));	break;
			case 0x90: result = KeyboardButton::Key_NumLock; break;
			case 0x91: result = KeyboardButton::Key_ScrollLock; break;
			case 0xA0: result = KeyboardButton::Key_LShift; break;
			case 0xA1: result = KeyboardButton::Key_RShift; break;
			case 0xA2: result = KeyboardButton::Key_LCtrl; break;
			case 0xA3: result = KeyboardButton::Key_RCtrl; break;
			case 0xA4: result = KeyboardButton::Key_Alt; break;
			case 0xBA: result = KeyboardButton::Key_Semicolon; break;
			case 0xBB: result = KeyboardButton::Key_Plus; break;
			case 0xBC: result = KeyboardButton::Key_Comma; break;
			case 0xBD: result = KeyboardButton::Key_Minus; break;
			case 0xBE: result = KeyboardButton::Key_Period; break;
			case 0xBF: result = KeyboardButton::Key_Slash; break;
			case 0xC0: result = KeyboardButton::Key_GraveAccent; break;
			case 0xDB: result = KeyboardButton::Key_LeftBracket; break;
			case 0xDC: result = KeyboardButton::Key_Backslash; break;
			case 0xDD: result = KeyboardButton::Key_RightBracket; break;
			case 0xDE: result = KeyboardButton::Key_Apostrophe; break;
			case 0xDF: result = KeyboardButton::Key_Equal; break;
		}
		return result;
	}
}

namespace engine
{
	namespace winapi
	{
		bool KeyboardImpl::handleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			bool handled = false;
			switch(message)
			{
				case WM_SYSKEYDOWN:
				case WM_KEYDOWN: handled = handleKeyDown(hWnd, wParam, lParam); break;
				case WM_SYSKEYUP:
				case WM_KEYUP: handled = handleKeyUp(hWnd, wParam, lParam); break;
			}
			return handled;
		}

		bool KeyboardImpl::handleKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			KeyParam parameters = parseParam(lParam);
			// Parameters are handled in that way we are ignoring it
			if(parameters.prevKeyState != 0)
				return false;
			
			bool handled = false;
			KeyboardButton button = parseButton(wParam, parameters.isExtended);
			if(button != KeyboardButton::EnumSize)
			{
				keyPressed.emit(button);
				onKeyPressed(button);
				handled = true;
			}
			return handled;
		}

		bool KeyboardImpl::handleKeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
		{
			KeyParam parameters = parseParam(lParam);
			KeyboardButton button = parseButton(wParam, parameters.isExtended);
			if(button != KeyboardButton::EnumSize)
			{
				keyReleased.emit(button);
				onKeyReleased(button);
				return true;
			}
			return false;
		}
	}
}
#else 

#include <engine/events/winapi/empty/KeyboardImpl.cpp>

#endif