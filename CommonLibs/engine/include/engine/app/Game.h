#pragma once
#include "stdafx.h"

#include "engine/app/Application.h"
#include "engine/stateStack/StateBase.h"

namespace engine
{
	namespace app
	{
		class IApplicationParameter;
		class IMain;
		class Game: public Application
		{
		public:
			Game(std::unique_ptr<IApplicationParameter> arguments, std::unique_ptr<IMain> main);
			~Game() ;
			void setStartState(std::unique_ptr<engine::stateStack::StateBase> startState);
		private:
			struct GamePrivate *_members = nullptr;
		};
	}
}
