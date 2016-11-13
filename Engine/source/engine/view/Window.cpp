#include "stdafx.h"

#include "engine/view/Window.h"

namespace engine
{
	namespace view
	{
		Window::Window()
			:_fullScreen(true)
		{

		}

		Window::Window(const view::WindowParameter &parameter)
			: _parameters(parameter)
		{

		}

		const view::WindowParameter &Window::getParameters() const
		{
			return _parameters;
		}

		void Window::setPosition(int32_t x, int32_t y)
		{
			ASSERT(!_fullScreen);
			_parameters.x = x;
			_parameters.y = y;
			setPositionImp(x, y);
		}

		void Window::setHeight(uint32_t height)
		{
			ASSERT(!_fullScreen);
			_parameters.height = height;
			setHeightImpl(height);
		}

		void Window::setWidth(uint32_t width)
		{
			ASSERT(!_fullScreen);
			_parameters.width = width;
			setWidthImpl(width);
		}

		void Window::setSize(uint32_t width, uint32_t height)
		{
			ASSERT(!_fullScreen);
			_parameters.height = height;
			_parameters.width = width;
			setSizeImpl(width, height);
		}

	}
}
