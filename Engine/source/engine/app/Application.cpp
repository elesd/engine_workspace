#include <stdafx.h>

#include <engine/app/Application.h>
#include <engine/app/IApplicationParameter.h>
#include <engine/app/IMain.h>

#include <engine/events/EventManager.h>

#include <engine/view/WindowManager.h>

namespace engine
{
	struct ApplicationPrivate
	{
		std::unique_ptr<IMain> main;
		std::unique_ptr<IApplicationParameter> arguments;
		std::unique_ptr<EventManager> eventManager;
		std::unique_ptr<WindowManager> windowManager;
		bool active = false;
	};


	Application::Application(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
		:_members(new ApplicationPrivate())
	{
		_members->main = std::move(main);
		_members->arguments = std::move(arguments);
	}

	Application::~Application()
	{
		delete _members;
	}

	void Application::start()
	{
		_members->main->load();
		_members->active = true;
	}

	void Application::stop()
	{
		_members->active = false;
	}

	void Application::update()
	{
		if(isActive())
		{
			updateImpl();
			_members->eventManager->update();
			_members->main->update();
		}
	}

	void Application::render()
	{
		if(isActive())
		{
			_members->main->render();
		}
	}

	bool Application::isActive() const
	{
		return _members->active;
	}

	const IApplicationParameter* Application::getArguments() const
	{
		return _members->arguments.get();
	}

	EventManager *Application::getEventManager() const
	{
		return _members->eventManager.get();
	}

	WindowManager *Application::getWindowManager() const
	{
		return _members->windowManager.get();
	}

	void Application::setEventManager(std::unique_ptr<EventManager> eventManager)
	{
		_members->eventManager = std::move(eventManager);
	}

	void Application::setWindowManager(std::unique_ptr<WindowManager> windowManager)
	{
		_members->windowManager = std::move(windowManager);
	}

}
