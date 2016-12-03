#include <stdafx.h>

#include "engine/app/Game.h"
///////////////////////////////////////////////
#include "engine/stateStack/StateStack.h"
#include "engine/app/IMain.h"

#include "engine/exceptions/LogicalErrors.h"

namespace engine
{
	struct GamePrivate
	{
		engine::StateStack stack;
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

	void Game::setStartState(std::unique_ptr<engine::StateBase> startState)
	{
		if(!_members->stack.isEmpty())
			throw InitializationError("Stack state has already a start state");
		_members->stack.pushState(std::move(startState));
	}
}
