#include <stdafx.h>
#include <engine/app/Application.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/app/IApplicationParameter.h>
#include <engine/app/IMain.h>

#include <engine/events/EventManagerFactory.h>
#include <engine/events/EventManager.h>

#include <engine/fileSystem/FileSystem.h>

#include <engine/render/RenderManager.h>

#include <engine/scene/SceneManager.h>

#include <engine/view/WindowManager.h>

namespace engine
{
	struct ApplicationPrivate
	{
		std::unique_ptr<IMain> main;
		std::unique_ptr<IApplicationParameter> arguments;
		std::unique_ptr<SceneManager> sceneManager;
		std::unique_ptr<RenderManager> renderManager;
		std::unique_ptr<WindowManager> windowManager;
        std::unique_ptr<EventManagerFactory> eventManagerFactory;
		std::unique_ptr<FileSystem> fileSystem;
		bool active = false;
	};


	Application::Application(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
		:_members(new ApplicationPrivate())
	{
		_members->main = std::move(main);
		_members->arguments = std::move(arguments);
		_members->sceneManager.reset(new SceneManager());
		_members->renderManager.reset(new RenderManager());
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
            _members->windowManager->update();
			_members->main->update();
			_members->sceneManager->update();
		}
	}

	void Application::render()
	{
		if(isActive())
		{
			std::vector<Window*> windows = _members->windowManager->getAllWindows();
			for(Window* window : windows)
			{
				_members->renderManager->render(window->getRenderContext(), _members->sceneManager->getActiveScenesRenderer());
			}
		}
	}

	bool Application::isActive() const
	{
		return _members->active;
	}

    EventManagerFactory* Application::getEventManagerFactory() const
    {
      return _members->eventManagerFactory.get();
    }

	const IApplicationParameter* Application::getArguments() const
	{
		return _members->arguments.get();
	}

	FileSystem* Application::getFileSystem() const
	{
		return _members->fileSystem.get();
	}

	SceneManager* Application::getSceneManager() const
	{
		return _members->sceneManager.get();
	}

	RenderManager* Application::getRenderManager() const
	{
		return _members->renderManager.get();
	}

	WindowManager *Application::getWindowManager() const
	{
		return _members->windowManager.get();
	}

	void Application::setWindowManager(std::unique_ptr<WindowManager> windowManager)
	{
		_members->windowManager = std::move(windowManager);
	}

    void Application::setEventManagerFactory(std::unique_ptr<EventManagerFactory> &&factory)
    {
        _members->eventManagerFactory = std::move(factory);
    }

	void Application::setFileSystem(std::unique_ptr<FileSystem> &&fileSystem)
	{
		_members->fileSystem = std::move(fileSystem);
	}

	void Application::run()
	{
		start();
		while(isActive())
		{
			update();
			render();
		}
	}
}
