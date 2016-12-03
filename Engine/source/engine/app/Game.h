#pragma once
#include "stdafx.h"

#include "engine/app/Application.h"
#include "engine/stateStack/StateBase.h"

namespace engine
{
	class IApplicationParameter;
	class IMain;
	/**
	* A game is a special application which has a state machine inside on it.
	*/
	class Game : public Application
	{
	public:
		/**
		* @see Application::Application
		*/
		Game(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
		/**Destructor for PIMPL*/
		~Game();
		/**
		* Set the start state
		* @param startState: State which will be active when the game is started.
		*/
		void setStartState(std::unique_ptr<engine::StateBase> startState);
	private:
		/**PIMPL*/
		struct GamePrivate *_members = nullptr;
	};
}
