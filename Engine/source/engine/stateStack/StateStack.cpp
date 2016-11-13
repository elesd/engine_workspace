#include "stdafx.h"

#include "engine/stateStack/StateStack.h"
#include "engine/stateStack/StateBase.h"

#include "engine/functional/functions.h"

namespace engine
{
	namespace stateStack
	{
		struct StateStackPrivate
		{
			std::list<std::unique_ptr<StateBase>> memory;
			StateStack::StateList states;
			StateStack::StateList history;
			bool statesDirty = false;
		};

		StateStack::StateStack()
			: _members(new StateStackPrivate())
		{
		}

		StateStack::~StateStack()
		{
			delete _members;
		}

		void StateStack::render()
		{
			if(!isEmpty())
			{
				topState()->render();
			}
		}

		void StateStack::update()
		{
			while(_members->statesDirty)
			{
				processModifications();
			}
			if(!isEmpty())
			{
				topState()->update();
			}
		}

		bool StateStack::isEmpty() const
		{
			return _members->history.empty();
		}

		StateBase *StateStack::topState()
		{
			return _members->history.back();
		}

		void StateStack::pushState(std::unique_ptr<StateBase> state)
		{
			_members->states.push_back(state.get());
			_members->memory.push_back(std::move(state));
			_members->statesDirty = true;
		}

		void StateStack::popState()
		{
			ASSERT(!_members->states.empty());
			_members->states.pop_back();
			_members->statesDirty = true;
		}

		void StateStack::processModifications()
		{
			if(!isEmpty())
			{
				topState()->pause();
			}

			StateList droppedStates = getStateDifference(_members->history, _members->states);
			for(StateBase *state : droppedStates)
			{
				auto it = std::find_if(_members->memory.begin(), _members->memory.end(), functional::PointerEqualTo<StateBase>(state));
				HARD_ASSERT(it != _members->memory.end());
				(*it)->destroy();

				_members->memory.erase(it);
			}

			_members->history = _members->states;
			_members->statesDirty = false;

			if(!isEmpty())
			{
				StateBase *top = topState();
				if(!top->isInitialized())
				{
					top->initialize(this);
				}
				top->resume();
			}
		}

		StateStack::StateList StateStack::getStateDifference(const StateList &a, const StateList &b) const
		{
			StateList result;
			for(StateBase *state : a)
			{
				bool isIn = std::any_of(b.begin(), b.end(),	functional::EqualTo<StateBase*>(state));
				if(!isIn)
				{
					result.push_back(state);
				}
			}
			return result;
		}

		void StateStack::trace(std::ostream &os) const
		{
			os << "current state:" << std::endl;
			for(const StateBase *state : _members->history)
			{
				state->trace(os);
				os << std::endl;
			}
			os << "future state:" << std::endl;
			for(const StateBase *state : _members->states)
			{
				state->trace(os);
				os << std::endl;
			}
		}

	}
}
