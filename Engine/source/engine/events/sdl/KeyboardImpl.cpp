#include <stdafx.h>
#include <engine/events/sdl/KeyboardImpl.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_SDL

#include <SDL2/SDL.h>

namespace
{
	engine::KeyboardButton convertButton(int32_t sdlKeyCode)
	{
		engine::KeyboardButton result = engine::KeyboardButton::EnumSize;
		switch(sdlKeyCode)
		{
			case SDLK_RETURN: result = engine::KeyboardButton::Key_Enter; break;
			case SDLK_ESCAPE: result = engine::KeyboardButton::Key_Esc; break;
			case SDLK_BACKSPACE:  result = engine::KeyboardButton::Key_Backspace; break;
			case SDLK_TAB: result = engine::KeyboardButton::Key_Tab; break;
			case SDLK_SPACE: result = engine::KeyboardButton::Key_Space; break;
			case SDLK_QUOTE: result = engine::KeyboardButton::Key_Apostrophe; break;
			case SDLK_COMMA: result = engine::KeyboardButton::Key_Comma; break;
			case SDLK_PERIOD: result = engine::KeyboardButton::Key_Period; break;
			case SDLK_SLASH: result = engine::KeyboardButton::Key_Slash; break;
			case SDLK_0: result = engine::KeyboardButton::Key_0; break;
			case SDLK_1: result = engine::KeyboardButton::Key_1; break;
			case SDLK_2: result = engine::KeyboardButton::Key_2; break;
			case SDLK_3: result = engine::KeyboardButton::Key_3; break;
			case SDLK_4: result = engine::KeyboardButton::Key_4; break;
			case SDLK_5: result = engine::KeyboardButton::Key_5; break;
			case SDLK_6: result = engine::KeyboardButton::Key_6; break;
			case SDLK_7: result = engine::KeyboardButton::Key_7; break;
			case SDLK_8: result = engine::KeyboardButton::Key_8; break;
			case SDLK_9: result = engine::KeyboardButton::Key_9; break;
			case SDLK_SEMICOLON: result = engine::KeyboardButton::Key_Semicolon; break;
			case SDLK_EQUALS: result = engine::KeyboardButton::Key_Equal; break;
			case SDLK_LEFTBRACKET: result = engine::KeyboardButton::Key_LeftBracket; break;
			case SDLK_BACKSLASH: result = engine::KeyboardButton::Key_Backslash; break;
			case SDLK_RIGHTBRACKET: result = engine::KeyboardButton::Key_RightBracket; break;
			case SDLK_BACKQUOTE: result = engine::KeyboardButton::Key_GraveAccent; break;
			case SDLK_a: result = engine::KeyboardButton::Key_A; break;
			case SDLK_b: result = engine::KeyboardButton::Key_B; break;
			case SDLK_c: result = engine::KeyboardButton::Key_C; break;
			case SDLK_d: result = engine::KeyboardButton::Key_D; break;
			case SDLK_e: result = engine::KeyboardButton::Key_E; break;
			case SDLK_f: result = engine::KeyboardButton::Key_F; break;
			case SDLK_g: result = engine::KeyboardButton::Key_G; break;
			case SDLK_h: result = engine::KeyboardButton::Key_H; break;
			case SDLK_i: result = engine::KeyboardButton::Key_I; break;
			case SDLK_j: result = engine::KeyboardButton::Key_J; break;
			case SDLK_k: result = engine::KeyboardButton::Key_K; break;
			case SDLK_l: result = engine::KeyboardButton::Key_L; break;
			case SDLK_m: result = engine::KeyboardButton::Key_M; break;
			case SDLK_n: result = engine::KeyboardButton::Key_N; break;
			case SDLK_o: result = engine::KeyboardButton::Key_O; break;
			case SDLK_p: result = engine::KeyboardButton::Key_P; break;
			case SDLK_q: result = engine::KeyboardButton::Key_Q; break;
			case SDLK_r: result = engine::KeyboardButton::Key_R; break;
			case SDLK_s: result = engine::KeyboardButton::Key_S; break;
			case SDLK_t: result = engine::KeyboardButton::Key_T; break;
			case SDLK_u: result = engine::KeyboardButton::Key_U; break;
			case SDLK_v: result = engine::KeyboardButton::Key_V; break;
			case SDLK_w: result = engine::KeyboardButton::Key_W; break;
			case SDLK_x: result = engine::KeyboardButton::Key_X; break;
			case SDLK_y: result = engine::KeyboardButton::Key_Y; break;
			case SDLK_z: result = engine::KeyboardButton::Key_Z; break;
			case SDLK_CAPSLOCK: result = engine::KeyboardButton::Key_CapsLock; break;
			case SDLK_F1: result = engine::KeyboardButton::Key_F1; break;
			case SDLK_F2: result = engine::KeyboardButton::Key_F2; break;
			case SDLK_F3: result = engine::KeyboardButton::Key_F3; break;
			case SDLK_F4: result = engine::KeyboardButton::Key_F4; break;
			case SDLK_F5: result = engine::KeyboardButton::Key_F5; break;
			case SDLK_F6: result = engine::KeyboardButton::Key_F6; break;
			case SDLK_F7: result = engine::KeyboardButton::Key_F7; break;
			case SDLK_F8: result = engine::KeyboardButton::Key_F8; break;
			case SDLK_F9: result = engine::KeyboardButton::Key_F9; break;
			case SDLK_F10: result = engine::KeyboardButton::Key_F10; break;
			case SDLK_F11: result = engine::KeyboardButton::Key_F11; break;
			case SDLK_F12: result = engine::KeyboardButton::Key_F12; break;
			case SDLK_PRINTSCREEN: result = engine::KeyboardButton::Key_PrintScreen; break;
			case SDLK_SCROLLLOCK: result = engine::KeyboardButton::Key_ScrollLock; break;
			case SDLK_PAUSE:  result = engine::KeyboardButton::Key_Pause; break;
			case SDLK_INSERT: result = engine::KeyboardButton::Key_Insert; break;
			case SDLK_HOME:  result = engine::KeyboardButton::Key_Home; break;
			case SDLK_PAGEUP:  result = engine::KeyboardButton::Key_PageUp; break;
			case SDLK_DELETE: result = engine::KeyboardButton::Key_Delete; break;
			case SDLK_END: result = engine::KeyboardButton::Key_End; break;
			case SDLK_PAGEDOWN:  result = engine::KeyboardButton::Key_PageDown; break;
			case SDLK_RIGHT: result = engine::KeyboardButton::Key_Right; break;
			case SDLK_LEFT:  result = engine::KeyboardButton::Key_Left; break;
			case SDLK_DOWN: result = engine::KeyboardButton::Key_Down; break;
			case SDLK_UP: result = engine::KeyboardButton::Key_Up; break;
			case SDLK_NUMLOCKCLEAR: result = engine::KeyboardButton::Key_NumLock; break;
			case SDLK_KP_DIVIDE: result = engine::KeyboardButton::Key_NumDevied; break;
			case SDLK_KP_MULTIPLY:  result = engine::KeyboardButton::Key_NumMultiply; break;
			case SDLK_KP_MINUS: result = engine::KeyboardButton::Key_NumMinus; break;
			case SDLK_KP_PLUS: result = engine::KeyboardButton::Key_NumPlus; break;
			case SDLK_KP_ENTER: result = engine::KeyboardButton::Key_NumEnter; break;
			case SDLK_KP_1: result = engine::KeyboardButton::Key_Num1; break;
			case SDLK_KP_2: result = engine::KeyboardButton::Key_Num2; break;
			case SDLK_KP_3: result = engine::KeyboardButton::Key_Num3; break;
			case SDLK_KP_4: result = engine::KeyboardButton::Key_Num4; break;
			case SDLK_KP_5: result = engine::KeyboardButton::Key_Num5; break;
			case SDLK_KP_6: result = engine::KeyboardButton::Key_Num6; break;
			case SDLK_KP_7: result = engine::KeyboardButton::Key_Num7; break;
			case SDLK_KP_8: result = engine::KeyboardButton::Key_Num8; break;
			case SDLK_KP_9: result = engine::KeyboardButton::Key_Num9; break;
			case SDLK_KP_0: result = engine::KeyboardButton::Key_Num0; break;
			case SDLK_KP_PERIOD: result = engine::KeyboardButton::Key_NumDecimal; break;
			case SDLK_LCTRL: result = engine::KeyboardButton::Key_LCtrl; break;
			case SDLK_LSHIFT: result = engine::KeyboardButton::Key_LShift; break;
			case SDLK_LALT: result = engine::KeyboardButton::Key_Alt; break;
			case SDLK_RCTRL: result = engine::KeyboardButton::Key_RCtrl; break;
			case SDLK_RSHIFT: result = engine::KeyboardButton::Key_RShift; break;
			case SDLK_RALT: result = engine::KeyboardButton::Key_Alt; break;
		}
		return result;
	}
}

namespace engine
{
	namespace sdl
	{
		void KeyboardImpl::handleEvent(const SDL_KeyboardEvent &event)
		{
			KeyboardButton button = convertButton(event.keysym.sym);
			if(event.repeat == 0)
			{
				if(event.type == SDL_KEYDOWN)
				{
					onKeyPressed(button);
					keyPressed.emit(button);
				}
				else if(event.type == SDL_KEYUP)
				{
					onKeyReleased(button);
					keyReleased.emit(button);
				}
			}
		}

	}
}

#endif
