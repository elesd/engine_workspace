#include "stdafx.h"

#include "stateStack/StateStackTestSuite.h"

#include "engine/exceptions/LogicalErrors.h"
#include "engine/exceptions/RuntimeErrors.h"
#include "engine/stateStack/StateBase.h"
#include "engine/stateStack/StateStack.h"

namespace
{
}

namespace tests
{
	void StateStackTestSuite::pushStateTestOnePush()
	{
		engine::StateStack stack;
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		auto state = std::make_unique<engine::StateBase>("test");
		engine::StateBase *topState = state.get();
		stack.pushState(std::move(state));
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		stack.update();
		assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
		assertTrue(ASSERTION_PARAMETER(stack.topState() == topState));
	}

	void StateStackTestSuite::pushStateTestTwoPushes()
	{
		engine::StateStack stack;
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		auto state = std::make_unique<engine::StateBase>("test");
		stack.pushState(std::move(state));

		state = std::make_unique<engine::StateBase>("test2");
		engine::StateBase *topState = state.get();
		stack.pushState(std::move(state));

		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));
		stack.update();
		assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
		assertTrue(ASSERTION_PARAMETER(stack.topState() == topState));
	}

	void StateStackTestSuite::popStateTestOnePop()
	{
		engine::StateStack stack;
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		auto state = std::make_unique<engine::StateBase>("test");
		engine::StateBase *firstState = state.get();
		stack.pushState(std::move(state));

		state = std::make_unique<engine::StateBase>("test2");
		engine::StateBase *topState = state.get();
		stack.pushState(std::move(state));

		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));
		stack.update();
		assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
		assertTrue(ASSERTION_PARAMETER(stack.topState() == topState));

		stack.popState();
		stack.update();
		assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
		assertTrue(ASSERTION_PARAMETER(stack.topState() == firstState));
	}

	void StateStackTestSuite::popStateTestTwoPops()
	{
		engine::StateStack stack;
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		auto state = std::make_unique<engine::StateBase>("test");
		engine::StateBase *firstState = state.get();
		stack.pushState(std::move(state));

		state = std::make_unique<engine::StateBase>("test2");
		engine::StateBase *topState = state.get();
		stack.pushState(std::move(state));

		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));
		stack.update();
		assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
		assertTrue(ASSERTION_PARAMETER(stack.topState() == topState));

		stack.popState();
		stack.update();
		assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
		assertTrue(ASSERTION_PARAMETER(stack.topState() == firstState));

		stack.popState();
		assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
		assertTrue(ASSERTION_PARAMETER(stack.topState() == firstState));

		stack.update();
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

	}

	void StateStackTestSuite::popStateTestUnderflow()
	{
		engine::StateStack stack;
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		auto state = std::make_unique<engine::StateBase>("test");
		engine::StateBase *topState = state.get();
		stack.pushState(std::move(state));
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		stack.update();
		assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
		assertTrue(ASSERTION_PARAMETER(stack.topState() == topState));

		stack.popState();
		bool assertDone = false;
		try
		{
			stack.popState();
		}
		catch(const engine::ItemNotFound &)
		{
			assertDone = true;
		}
		assertTrue(ASSERTION_PARAMETER(assertDone));
	}

	void StateStackTestSuite::changeStateTest()
	{
		engine::StateStack stack;
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		auto state = std::make_unique<engine::StateBase>("test");
		engine::StateBase *currentState = state.get();
		stack.pushState(std::move(state));
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		stack.update();
		auto newState = std::make_unique<engine::StateBase>("test2");
		engine::StateBase *nextState = newState.get();
		currentState->changeState(std::move(newState));

		assertTrue(ASSERTION_PARAMETER(currentState->isLeaving()));
		assertTrue(ASSERTION_PARAMETER(currentState->isActive()));
		assertTrue(ASSERTION_PARAMETER(currentState == stack.topState()));

		stack.update();

		assertTrue(ASSERTION_PARAMETER(nextState == stack.topState()));

	}

	void StateStackTestSuite::changeStateTestDouble()
	{
		engine::StateStack stack;
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		auto state = std::make_unique<engine::StateBase>("test");
		engine::StateBase *currentState = state.get();
		stack.pushState(std::move(state));
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		stack.update();
		auto newState = std::make_unique<engine::StateBase>("test2");
		engine::StateBase *nextState = newState.get();
		currentState->changeState(std::move(newState));

		assertTrue(ASSERTION_PARAMETER(currentState->isLeaving()));
		assertTrue(ASSERTION_PARAMETER(currentState->isActive()));
		assertTrue(ASSERTION_PARAMETER(currentState == stack.topState()));

		auto newState2 = std::make_unique<engine::StateBase>("test3");
		bool assertionDone = false;
		try
		{
			currentState->changeState(std::move(newState2));
		}
		catch(engine::WrongStateError &)
		{
			assertionDone = true;
		}

		assertTrue(ASSERTION_PARAMETER(assertionDone));
	}

	void StateStackTestSuite::exitStateTest()
	{
		engine::StateStack stack;
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		auto state = std::make_unique<engine::StateBase>("test");
		engine::StateBase *currentState = state.get();
		stack.pushState(std::move(state));
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		stack.update();
		currentState->exitState();

		assertTrue(ASSERTION_PARAMETER(currentState->isLeaving()));
		assertTrue(ASSERTION_PARAMETER(currentState->isActive()));
		assertTrue(ASSERTION_PARAMETER(currentState == stack.topState()));

		stack.update();

		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));
	}

	void StateStackTestSuite::exitStateTestDouble()
	{
		engine::StateStack stack;
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		auto state = std::make_unique<engine::StateBase>("test");
		stack.pushState(std::move(state));

		state = std::make_unique<engine::StateBase>("test2");
		engine::StateBase *topState = state.get();
		stack.pushState(std::move(state));

		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));
		stack.update();
		assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
		assertTrue(ASSERTION_PARAMETER(stack.topState() == topState));
		topState->exitState();
		bool assertionDone = false;
		try
		{
			topState->exitState();
		}
		catch(engine::WrongStateError &)
		{
			assertionDone = true;
		}
		assertTrue(ASSERTION_PARAMETER(assertionDone));
	}

	void StateStackTestSuite::exitStateAndChangeState()
	{
		engine::StateStack stack;
		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

		auto state = std::make_unique<engine::StateBase>("test");
		stack.pushState(std::move(state));

		state = std::make_unique<engine::StateBase>("test2");
		engine::StateBase *topState = state.get();
		stack.pushState(std::move(state));

		assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));
		stack.update();
		assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
		assertTrue(ASSERTION_PARAMETER(stack.topState() == topState));
		topState->exitState();
		bool assertionDone = false;
		try
		{
			auto newState = std::make_unique<engine::StateBase>("test3");
			topState->changeState(std::move(newState));
		}
		catch(engine::WrongStateError &)
		{
			assertionDone = true;
		}
		assertTrue(ASSERTION_PARAMETER(assertionDone));
	}
}
