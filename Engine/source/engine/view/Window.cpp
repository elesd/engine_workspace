#include "stdafx.h"

#include "engine/view/Window.h"

///////////////////////////////////////////////////////////////////////////////

#include "engine/video/Driver.h"

namespace engine
{
	namespace view
	{
		struct WindowPrivate
		{
			std::unique_ptr<video::Driver> driver;
		};

		Window::Window()
			:_fullScreen(true),
			_members(new WindowPrivate())
			 
		{
			
		}

		Window::Window(const view::WindowParameter &parameter)
			: _parameters(parameter),
			_members(new WindowPrivate())
		{

		}

		Window::~Window()
		{
			delete _members;
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

		video::Driver *Window::getDriver() const
		{
			return _members->driver.get();
		}

		void Window::initDriver(std::unique_ptr<video::Driver> driver)
		{
			HARD_ASSERT(!_members->driver);
			_members->driver = std::move(driver);
		}
	}
}
