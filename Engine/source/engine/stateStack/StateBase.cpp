#include "stdafx.h"

#include "engine/stateStack/StateBase.h"
#include "engine/stateStack/StateStack.h"

namespace engine
{
	namespace stateStack
	{
		struct StateBasePrivate
		{
			enum class Status
			{
				Null,
				Initialized,
				Active,
				Leaving
			};
			Status status = Status::Null;
			StateStack *stateStack = nullptr;
		};

		StateBase::~StateBase()
		{
			delete _members;
		}

		StateBase::StateBase()
			:_members(new StateBasePrivate())
		{		}

		void StateBase::initialize(StateStack *stack)
		{
			ASSERT(!isInitialized());
			ASSERT(_members->stateStack == nullptr);
			_members->stateStack = stack;
			initState();
			_members->status = StateBasePrivate::Status::Initialized;
		}

		void StateBase::destroy()
		{
			ASSERT(isInitialized());
			destroyState();
			_members->stateStack = nullptr;
			_members->status = StateBasePrivate::Status::Null;
		}

		bool StateBase::isInitialized() const
		{
			return _members->status != StateBasePrivate::Status::Null;
		}

		bool StateBase::isActive() const
		{
			return _members->status == StateBasePrivate::Status::Active
				|| isLeaving();
		}

		bool StateBase::isLeaving() const
		{
			return _members->status == StateBasePrivate::Status::Leaving;
		}


		void StateBase::resume()
		{
			ASSERT(!isActive());
			resumeState();
			_members->status = StateBasePrivate::Status::Active;
		}

		void StateBase::pause()
		{
			ASSERT(isActive());
			_members->status = StateBasePrivate::Status::Initialized;
			pauseState();
		}

		void StateBase::update()
		{
			ASSERT(isActive());
			updateState();
		}

		void StateBase::render()
		{
			ASSERT(isActive());
			renderState();
		}

		void StateBase::changeState(std::unique_ptr<StateBase> nextState)
		{
			ASSERT(isInitialized());
			ASSERT(isActive());
			ASSERT(!isLeaving());
			stateChanged.emit(nextState.get());
			_members->status = StateBasePrivate::Status::Leaving;
			_members->stateStack->pushState(std::move(nextState));
		}

		void StateBase::exitState()
		{
			ASSERT(isInitialized());
			ASSERT(isActive());
			ASSERT(!isLeaving());
			stateTerminated.emit();
			_members->status = StateBasePrivate::Status::Leaving;
			_members->stateStack->popState();
		}

		void StateBase::trace(std::ostream &os) const
		{

			std::string statusStr = "UNKNOWN";
			switch(_members->status)
			{
				case StateBasePrivate::Status::Active:		statusStr = "ACTIVE"; break;
				case StateBasePrivate::Status::Initialized: statusStr = "INITIALIZED"; break;
				case StateBasePrivate::Status::Leaving:		statusStr = "LEAVING"; break;
				case StateBasePrivate::Status::Null:		statusStr = "NULL"; break;
				default:	break;
			}
			os << "State basic info: status: " << statusStr;
		}
	}
}
