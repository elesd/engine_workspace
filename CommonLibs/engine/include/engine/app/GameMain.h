#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/view/Window.h>

namespace engine
{
	class StateBase;
	class WindowManager;
	/**
	* Base class for core logic of an application
	*/
	class GameMain 
		: private NonCopyable
		, private NonMoveable
	{
	protected:
		class WindowCreationParameter
		{
			friend class GameMain;
		public:
			static WindowCreationParameter createForFullScreen(const uint32_t width, const uint32_t height, const std::string &title, uint32_t monitorId);
			static WindowCreationParameter create(WindowParameter creationParams, const std::string& title);
		private:
			WindowParameter creationParams;
			bool isFullScreened = false;
			uint32_t monitorId;
			std::string title;
		};

	protected:
		GameMain();
	public:
		virtual ~GameMain();
		void load(WindowManager* windowManager);
		void update();
	private:
		virtual void updateGame() {};
		virtual void loadGame() {};
		virtual WindowCreationParameter getWindowCreationParameters() = 0;
		virtual std::unique_ptr<StateBase> createStartState(Window* mainWindow) = 0;
	private:
		struct GameMainPrivate* _members = nullptr;
	};
}
