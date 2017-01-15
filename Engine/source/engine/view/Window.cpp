#include "stdafx.h"

#include "engine/view/Window.h"

///////////////////////////////////////////////////////////////////////////////

#include "engine/exceptions/LogicalErrors.h"

#include "engine/video/Driver.h"

namespace engine
{
	struct WindowPrivate
	{
		std::unique_ptr<Driver> driver;
	};

	Window::Window()
		:_fullScreen(true),
		_members(new WindowPrivate())

	{

	}

	Window::Window(const WindowParameter &parameter)
		: _parameters(parameter),
		_members(new WindowPrivate())
	{

	}

	Window::~Window()
	{
		delete _members;
	}

	const WindowParameter &Window::getParameters() const
	{
		return _parameters;
	}

	void Window::setPosition(int32_t x, int32_t y)
	{
		if(isFullScreen())
			throw WrongStateError("Set position is called on window but it is in fullscreen mode");
		_parameters.x = x;
		_parameters.y = y;
		setPositionImp(x, y);
	}

	void Window::setHeight(uint32_t height)
	{
		if(isFullScreen())
			throw WrongStateError("Set position is called on window but it is in fullscreen mode");
		_parameters.height = height;
		setHeightImpl(height);
	}

	void Window::setWidth(uint32_t width)
	{
		if(isFullScreen())
			throw WrongStateError("Set position is called on window but it is in fullscreen mode");
		_parameters.width = width;
		setWidthImpl(width);
	}

	void Window::setSize(uint32_t width, uint32_t height)
	{
		if(isFullScreen())
			throw WrongStateError("Set position is called on window but it is in fullscreen mode");
		_parameters.height = height;
		_parameters.width = width;
		setSizeImpl(width, height);
	}

	Driver *Window::getDriver() const
	{
		return _members->driver.get();
	}

	void Window::initDriver(std::unique_ptr<Driver> driver)
	{
		HARD_ASSERT(!_members->driver);
		_members->driver = std::move(driver);
	}

	uint32_t Window::getHeight() const
	{
		return getParameters().width;
	}

	uint32_t Window::getWidth() const
	{
		return getParameters().width;
	}
}
