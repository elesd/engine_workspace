#include <stdafx.h>

#include "engine/app/Game.h"
///////////////////////////////////////////////
#include "engine/stateStack/StateStack.h"
#include "engine/app/IMain.h"

namespace engine
{
	namespace app
	{
		struct GamePrivate
		{
			engine::stateStack::StateStack stack;
		};

		Game::Game(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main)
			: Application(std::move(arguments), std::move(main)),
			_members(new GamePrivate())
		{

		}

		Game::~Game()
		{
			delete _members;
		}

		void Game::setStartState(std::unique_ptr<engine::stateStack::StateBase> startState)
		{
			ASSERT(_members->stack.isEmpty());
			_members->stack.pushState(std::move(startState));
		}
	}
}
