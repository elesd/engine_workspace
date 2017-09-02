#include <stdafx.h>
#include <engine/events/glfw/KeyboardImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLFW

#include <GLFW/glfw3.h>

namespace
{
	engine::KeyboardButton convertButton(int32_t glfwKeyCode)
	{
		engine::KeyboardButton result = engine::KeyboardButton::EnumSize;
		switch(glfwKeyCode)
		{
			case GLFW_KEY_SPACE:		  result = engine::KeyboardButton::Key_Space; break;
			case GLFW_KEY_APOSTROPHE:	  result = engine::KeyboardButton::Key_Apostrophe; break;
			case GLFW_KEY_COMMA:		  result = engine::KeyboardButton::Key_Comma; break;
			case GLFW_KEY_MINUS:		  result = engine::KeyboardButton::Key_Minus; break;
			case GLFW_KEY_PERIOD:		  result = engine::KeyboardButton::Key_Period; break;
			case GLFW_KEY_SLASH:		  result = engine::KeyboardButton::Key_Slash; break;
			case GLFW_KEY_0:
			case GLFW_KEY_1:
			case GLFW_KEY_2:
			case GLFW_KEY_3:
			case GLFW_KEY_4:
			case GLFW_KEY_5:
			case GLFW_KEY_6:
			case GLFW_KEY_7:
			case GLFW_KEY_8:
			case GLFW_KEY_9:			  result = engine::KeyboardButton(uint32_t(engine::KeyboardButton::Key_0) + (glfwKeyCode - GLFW_KEY_0)); break;
			case GLFW_KEY_SEMICOLON:	  result = engine::KeyboardButton::Key_Semicolon; break;
			case GLFW_KEY_EQUAL:		  result = engine::KeyboardButton::Key_Equal; break;
			case GLFW_KEY_A:
			case GLFW_KEY_B:
			case GLFW_KEY_C:
			case GLFW_KEY_D:
			case GLFW_KEY_E:
			case GLFW_KEY_F:
			case GLFW_KEY_G:
			case GLFW_KEY_H:
			case GLFW_KEY_I:
			case GLFW_KEY_J:
			case GLFW_KEY_K:
			case GLFW_KEY_L:
			case GLFW_KEY_M:
			case GLFW_KEY_N:
			case GLFW_KEY_O:
			case GLFW_KEY_P:
			case GLFW_KEY_Q:
			case GLFW_KEY_R:
			case GLFW_KEY_S:
			case GLFW_KEY_T:
			case GLFW_KEY_U:
			case GLFW_KEY_V:
			case GLFW_KEY_W:
			case GLFW_KEY_X:
			case GLFW_KEY_Y:
			case GLFW_KEY_Z:			  result = engine::KeyboardButton(uint32_t(engine::KeyboardButton::Key_A) + (glfwKeyCode - GLFW_KEY_A)); break;
			case GLFW_KEY_LEFT_BRACKET:	  result = engine::KeyboardButton::Key_LeftBracket; break;
			case GLFW_KEY_BACKSLASH:	  result = engine::KeyboardButton::Key_Backslash; break;
			case GLFW_KEY_RIGHT_BRACKET:  result = engine::KeyboardButton::Key_RightBracket; break;
			case GLFW_KEY_GRAVE_ACCENT:   result = engine::KeyboardButton::Key_GraveAccent; break;
			case GLFW_KEY_ESCAPE:		  result = engine::KeyboardButton::Key_Esc; break;
			case GLFW_KEY_ENTER:		  result = engine::KeyboardButton::Key_Enter; break;
			case GLFW_KEY_TAB:			  result = engine::KeyboardButton::Key_Tab; break;
			case GLFW_KEY_BACKSPACE:	  result = engine::KeyboardButton::Key_Backspace; break;
			case GLFW_KEY_INSERT:		  result = engine::KeyboardButton::Key_Insert; break;
			case GLFW_KEY_DELETE:		  result = engine::KeyboardButton::Key_Delete; break;
			case GLFW_KEY_RIGHT:		  result = engine::KeyboardButton::Key_Right; break;
			case GLFW_KEY_LEFT:			  result = engine::KeyboardButton::Key_Left; break;
			case GLFW_KEY_DOWN:			  result = engine::KeyboardButton::Key_Down; break;
			case GLFW_KEY_UP:			  result = engine::KeyboardButton::Key_Up; break;
			case GLFW_KEY_PAGE_UP:		  result = engine::KeyboardButton::Key_PageUp; break;
			case GLFW_KEY_PAGE_DOWN:	  result = engine::KeyboardButton::Key_PageDown; break;
			case GLFW_KEY_HOME:			  result = engine::KeyboardButton::Key_Home; break;
			case GLFW_KEY_END:			  result = engine::KeyboardButton::Key_End; break;
			case GLFW_KEY_CAPS_LOCK:	  result = engine::KeyboardButton::Key_CapsLock; break;
			case GLFW_KEY_SCROLL_LOCK:	  result = engine::KeyboardButton::Key_ScrollLock; break;
			case GLFW_KEY_NUM_LOCK:		  result = engine::KeyboardButton::Key_NumLock; break;
			case GLFW_KEY_PRINT_SCREEN:   result = engine::KeyboardButton::Key_PrintScreen; break;
			case GLFW_KEY_PAUSE:		  result = engine::KeyboardButton::Key_Pause; break;
			case GLFW_KEY_F1:
			case GLFW_KEY_F2:
			case GLFW_KEY_F3:
			case GLFW_KEY_F4:
			case GLFW_KEY_F5:
			case GLFW_KEY_F6:
			case GLFW_KEY_F7:
			case GLFW_KEY_F8:
			case GLFW_KEY_F9:
			case GLFW_KEY_F10:
			case GLFW_KEY_F11:
			case GLFW_KEY_F12:			  result = engine::KeyboardButton(uint32_t(engine::KeyboardButton::Key_F1) + (glfwKeyCode - GLFW_KEY_F1)); break;
			case GLFW_KEY_KP_0:
			case GLFW_KEY_KP_1:
			case GLFW_KEY_KP_2:
			case GLFW_KEY_KP_3:
			case GLFW_KEY_KP_4:
			case GLFW_KEY_KP_5:
			case GLFW_KEY_KP_6:
			case GLFW_KEY_KP_7:
			case GLFW_KEY_KP_8:
			case GLFW_KEY_KP_9:			  result = engine::KeyboardButton(uint32_t(engine::KeyboardButton::Key_Num0) + (glfwKeyCode - GLFW_KEY_KP_0)); break;
			case GLFW_KEY_KP_DECIMAL:	  result = engine::KeyboardButton::Key_NumDecimal; break;
			case GLFW_KEY_KP_DIVIDE:	  result = engine::KeyboardButton::Key_NumDevied; break;
			case GLFW_KEY_KP_MULTIPLY:	  result = engine::KeyboardButton::Key_NumMultiply; break;
			case GLFW_KEY_KP_SUBTRACT:	  result = engine::KeyboardButton::Key_NumMinus; break;
			case GLFW_KEY_KP_ADD:		  result = engine::KeyboardButton::Key_NumPlus; break;
			case GLFW_KEY_KP_ENTER:		  result = engine::KeyboardButton::Key_NumEnter; break;
			case GLFW_KEY_LEFT_SHIFT:	  result = engine::KeyboardButton::Key_LShift; break;
			case GLFW_KEY_LEFT_CONTROL:   result = engine::KeyboardButton::Key_LCtrl; break;
			case GLFW_KEY_LEFT_ALT:		  result = engine::KeyboardButton::Key_Alt; break;
			case GLFW_KEY_RIGHT_SHIFT:	  result = engine::KeyboardButton::Key_RShift; break;
			case GLFW_KEY_RIGHT_CONTROL:  result = engine::KeyboardButton::Key_RCtrl; break;
			case GLFW_KEY_RIGHT_ALT:	  result = engine::KeyboardButton::Key_Alt; break;
			default:					  result = engine::KeyboardButton::EnumSize; break;
		}
		return result;
	}
}

namespace engine
{
	namespace glfw
	{
		bool KeyboardImpl::handleKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mods)
		{
			bool result = false;
			switch(action)
			{
				case GLFW_PRESS: result = handleKeyDownEvent(key); break;
				case GLFW_RELEASE: result = handleKeyUpEvent(key); break;
			}
			return result;
		}

		bool KeyboardImpl::handleKeyUpEvent(int32_t key)
		{
			KeyboardButton button = convertButton(key);
			onKeyReleased(button);
			keyReleased.emit(button);
			return true;
		}

		bool KeyboardImpl::handleKeyDownEvent(int32_t key)
		{
			KeyboardButton button = convertButton(key);
			onKeyPressed(button);
			keyPressed.emit(button);
			return true;

		}
	}
}


#endif
