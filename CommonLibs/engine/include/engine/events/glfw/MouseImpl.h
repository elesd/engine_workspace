#pragma once

#include <engine/events/Mouse.h>


namespace engine
{
	namespace glfw
	{
		class MouseImpl : public Mouse
		{

		public:
			MouseImpl() = default;
			~MouseImpl() override {};
			void handleMoveEvent(float x, float y);
			void handleClickEvent(int32_t button, int32_t action, int32_t mods);
			void handleScollEvent(float xoffset, float yoffset);
		private:
			void handlePressEvent(int32_t button);
			void handleReleaseEvent(int32_t button);
		};
	}
}
