#include <stdafx.h>
#include <engine/app/Application.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/app/IApplicationParameter.h>
#include <engine/app/GameMain.h>

#include <engine/events/EventManagerFactory.h>
#include <engine/events/EventManager.h>

#include <engine/fileSystem/FileSystem.h>

#include <engine/libraries/ShaderLibrary.h>

#include <engine/render/RenderManager.h>

#include <engine/servicies/LibraryService.h>
#include <engine/servicies/SceneService.h>

#include <engine/scene/SceneManager.h>

#include <engine/view/WindowManager.h>

namespace engine
{
	struct ApplicationPrivate
	{
		std::unique_ptr<GameMain> main;
		std::unique_ptr<IApplicationParameter> arguments;
		std::unique_ptr<SceneManager> sceneManager;
		std::unique_ptr<LibraryService> libraryService;
		std::unique_ptr<SceneService> sceneService;
		std::unique_ptr<RenderManager> renderManager;
		std::unique_ptr<WindowManager> windowManager;
        std::unique_ptr<EventManagerFactory> eventManagerFactory;
		std::unique_ptr<FileSystem> fileSystem;
		bool active = false;
	};


	Application::Application(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<GameMain> main)
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
		_members->main->load(_members->windowManager.get());
		_members->active = true;
		loadServicies();
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

			_members->sceneManager->syncScenes();
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

	RenderManager* Application::getRenderManager() const
	{
		return _members->renderManager.get();
	}

	LibraryService* Application::getLibraryService() const
	{
		return _members->libraryService.get();
	}

	SceneService* Application::getSceneService() const
	{
		return _members->sceneService.get();
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

	void Application::loadServicies()
	{
		ASSERT(_members->windowManager);
		_members->libraryService.reset(new LibraryService(_members->windowManager->getMainWindow()->getRenderContext()));
		_members->sceneService.reset(new SceneService(_members->sceneManager.get(), _members->windowManager->getMainWindow()->getRenderContext()));
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
