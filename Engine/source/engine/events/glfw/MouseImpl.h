#pragma once

#include <engine/events/Mouse.h>


namespace engine
{
	namespace glfw
	{
		/**Glfw mouse implementation.*/
		class MouseImpl : public Mouse
		{
		public:
			/**Default constructable.*/
			MouseImpl() = default;
			/**Ensure polimorphsm.*/
			~MouseImpl() override {};

			/**
			* Handle move event.
			* @param x: x coordinate of the cursor.
			* @param y: y coordinate of the cursor.
			* @see engine::glfw::EventManagerImpl::mouseMovedCallback
			*/
			void handleMoveEvent(float x, float y);
			/**
			* Handle click event.
			* @param button: pressed button.
			* @param action: Action of the event.
			* @param mods: modification bitset.
			* @see engine::glfw::EventManagerImpl::mouseButtonCallback
			*/
			void handleClickEvent(int32_t button, int32_t action, int32_t mods);
			/**
			* Hanlde scroll event.
			* @param xoffset: The scroll offset along the x-axis.
			* @param yoffset: The scroll offset along the y-axis.
			* @see engine::glfw::EventManagerImpl::mouseScrolledCallback
			*/
			void handleScollEvent(float xoffset, float yoffset);
		private:
			/**
			* Handle the press event.
			* @param button: pressed button.
			*/
			void handlePressEvent(int32_t button);
			/**
			* Handle the release event.
			* @param button: pressed button.
			*/
			void handleReleaseEvent(int32_t button);
		};
	}
}
