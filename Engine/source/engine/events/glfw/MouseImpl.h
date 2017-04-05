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
			void handleClickEvent(int button, int action, int mods);
			void handleScollEvent(float xoffset, float yoffset);
		};
	}
}