#include <stdafx.h>
#include <engine/stateStack/StateBase.h>
///////////////////////////////////////////////////////////////////////////////


#include <engine/app/Application.h>
#include <engine/view/WindowManager.h>

#include <engine/exceptions/LogicalErrors.h>
#include <engine/exceptions/RuntimeErrors.h>

#include <engine/render/RenderContext.h>

#include <engine/stateStack/StateStack.h>

#include <engine/Context.h>

namespace engine
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
		std::string name;
	};

	StateBase::~StateBase()
	{
		if(isInitialized())
		{
			try
			{
				destroy();
			}
			catch(const InitializationError &)
			{
				//FAIL("State destroy is failed");
			}
		}
		delete _members;
	}

	StateBase::StateBase(const std::string &name)
		:_members(new StateBasePrivate())
	{
		_members->name = name;
	}

	void StateBase::initialize(StateStack *stack)
	{
		if(isInitialized())
			throw InitializationError("State base already initialized");

		_members->stateStack = stack;
		initState();
		_members->status = StateBasePrivate::Status::Initialized;
	}

	void StateBase::destroy()
	{
		if(!isInitialized())
			throw InitializationError("State is not initialized but destroyed");
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
		if(isActive())
			throw WrongStateError("State is active, but resume is called");
		resumeState();
		_members->status = StateBasePrivate::Status::Active;
	}

	void StateBase::pause()
	{
		if(!isActive())
			throw WrongStateError("State is not active, but pause is called");
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
		// TODO swap all the buffers
		Context::getInstance()->getApplication()->getWindowManager()->getMainWindow()->getRenderContext()->swapBuffer();
	}

	void StateBase::changeState(std::unique_ptr<StateBase> nextState)
	{
		if(!isInitialized())
			throw InitializationError("State is not initialized, but try to change state");
		if(!isActive())
			throw WrongStateError("State is not active but try to change state");
		if(isLeaving())
			throw WrongStateError("State is already leaving but it is called a change state. Probobly try to exit 2 times");

		stateChanged.emit(nextState.get());
		_members->status = StateBasePrivate::Status::Leaving;
		_members->stateStack->pushState(std::move(nextState));
	}

	void StateBase::exitState()
	{
		if(!isInitialized())
			throw InitializationError("State is not initialized, but try to exit");
		if(!isActive())
			throw WrongStateError("State is not active but try to exit");
		if(isLeaving())
			throw WrongStateError("State is already leaving but it calls an exit. Probobly try to exit 2 times");
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
		os << "State basic info: [" << _members->name << "]status: " << statusStr;
	}

	Context* StateBase::getContext() const
	{
		return Context::getInstance();
	}

	Console* StateBase::getConsole() const
	{
		return Context::getInstance()->getConsole();
	}
}
