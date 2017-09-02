#include <stdafx.h>
#include <engine/app/GameMain.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/stateStack/StateStack.h>
#include <engine/stateStack/StateBase.h>

#include <engine/view/WindowManager.h>

namespace engine
{
	GameMain::WindowCreationParameter GameMain::WindowCreationParameter::createForFullScreen(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId)
	{
		WindowCreationParameter params;
		params.creationParams.width = width;
		params.creationParams.height = height;
		params.creationParams.x = 0; // won't be used
		params.creationParams.x = 0; // won't be used
		params.isFullScreened = true;
		params.monitorId = monitorId;
		params.title = title;
		return params;
	}

	GameMain::WindowCreationParameter GameMain::WindowCreationParameter::create(WindowParameter creationParams, const std::string& title)
	{
		WindowCreationParameter params;
		params.creationParams = creationParams;
		params.isFullScreened = false;
		params.monitorId = 0; // won't be used
		params.title = title;
		return params;
	}

	struct GameMainPrivate
	{
		std::unique_ptr<StateStack> stateStack;
		Window* mainWindow = nullptr;
	};

	GameMain::GameMain()
		: _members(new GameMainPrivate())
	{

	}

	GameMain::~GameMain()
	{
		delete _members;
		_members = nullptr;
	}

	void GameMain::load(WindowManager* windowManager)
	{
		WindowCreationParameter windowParam = getWindowCreationParameters();
		if(windowParam.isFullScreened)
		{
			_members->mainWindow = windowManager->createFullScreenMainWindow(windowParam.creationParams.width,
																			 windowParam.creationParams.height,
																			 windowParam.title,
																			 windowParam.monitorId);
		}
		else
		{
			_members->mainWindow = windowManager->createMainWindow(windowParam.creationParams, windowParam.title);

		}
		_members->stateStack = std::make_unique<engine::StateStack>();
		std::unique_ptr<StateBase> firstState = createStartState(_members->mainWindow);
		_members->stateStack->pushState(std::move(firstState));
		loadGame();
	}

	void GameMain::update()
	{
		_members->stateStack->update();
		updateGame();
	}
}