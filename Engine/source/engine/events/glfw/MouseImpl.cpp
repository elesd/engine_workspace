#include <stdafx.h>
#include <engine/events/glfw/MouseImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if ENGINE_USE_GLFW
#include <engine/Context.h>
#include <engine/events/EventManager.h>

#include <GLFW/glfw3.h>

namespace engine
{
	namespace glfw
	{
		void MouseImpl::handleMoveEvent(float x, float y)
		{
			onMouseMoved(int32_t(x), int32_t(y));
			moved.emit(int32_t(x), int32_t(y));
		}

		void MouseImpl::handleClickEvent(int32_t button, int32_t action, int32_t mods)
		{
			switch(action)
			{
				case GLFW_PRESS:   handlePressEvent(button); break;
				case GLFW_RELEASE: handleReleaseEvent(button); break;
			}
		}

		void MouseImpl::handleScollEvent(float xoffset, float yoffset)
		{
			ScreenSpacePosition pos = getPosition();
			scrolled.emit(pos.x, pos.y, int32_t(yoffset));
		}

		void MouseImpl::handlePressEvent(int32_t button)
		{
			ScreenSpacePosition pos = getPosition();
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					onLeftButtonPressed();
					leftButtonPressed.emit(pos.x, pos.y);
					break;
				case GLFW_MOUSE_BUTTON_RIGHT:
					onRightButtonPressed();
					rightButtonPressed.emit(pos.x, pos.y);
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					onMiddleButtonPressed();
					middleButtonPressed.emit(pos.x, pos.y);
					break;
			}
		}

		void MouseImpl::handleReleaseEvent(int32_t button)
		{
			ScreenSpacePosition pos = getPosition();
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					onLeftButtonReleased();
					leftButtonReleased.emit(pos.x, pos.y);
					break;
				case GLFW_MOUSE_BUTTON_RIGHT:
					onRightButtonReleased();
					rightButtonReleased.emit(pos.x, pos.y);
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					onMiddleButtonReleased();
					middleButtonReleased.emit(pos.x, pos.y);
					break;
			}
		}
	}
}
#else 

#include <engine/events/glfw/empty/MouseImpl.cpp>

#endif
