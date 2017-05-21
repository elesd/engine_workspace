#include <stdafx.h>

#include <engine/view/Window.h>

///////////////////////////////////////////////////////////////////////////////

#include <engine/events/EventManager.h>

#include <engine/exceptions/LogicalErrors.h>

#include <engine/render/RenderContext.h>

namespace engine
{
	const std::string Window::EventSourceId = "Window";

	struct WindowPrivate
	{
		std::unique_ptr<RenderContext> renderContext;
		std::unique_ptr<EventManager> eventManager;
		WindowManager *windowManager = nullptr;
		WindowPrivate(WindowManager *m): windowManager(m){}
	};

	Window::Window(WindowManager *windowManager)
		: EventSourceBase(EventSourceId),
		_fullScreen(true),
		_members(new WindowPrivate(windowManager))
	{

	}

	Window::Window(WindowManager *windowManager, const WindowParameter &parameter)
		: EventSourceBase(EventSourceId),
		 _parameters(parameter),
		_members(new WindowPrivate(windowManager))
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

	RenderContext* Window::getRenderContext() const
	{
		return _members->renderContext.get();
	}

	void Window::initRenderContext(std::unique_ptr<RenderContext>&& context)
	{
		HARD_ASSERT(!_members->renderContext);
		_members->renderContext = std::move(context);
	}

	uint32_t Window::getHeight() const
	{
		return getParameters().height;
	}

	uint32_t Window::getWidth() const
	{
		return getParameters().width;
	}

	void Window::update()
	{
		_members->eventManager->update();
	}

	EventManager *Window::getEventManager() const
	{
		 return _members->eventManager.get();
	}

	void Window::setEventManager(std::unique_ptr<EventManager> &&manager)
	{
		_members->eventManager = std::move(manager);
	}

	WindowManager *Window::getWindowManager() const
	{
		return _members->windowManager;
	}
}
