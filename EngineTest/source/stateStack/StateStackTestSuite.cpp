#include "stdafx.h"

#include "stateStack/StateStackTestSuite.h"
#include "engine/stateStack/StateBase.h"
#include "engine/stateStack/StateStack.h"

namespace
{
}

namespace tests
{
	namespace stateStack
	{
		void StateStackTestSuite::pushStateTestOnePush()
		{
			engine::stateStack::StateStack stack;
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			auto state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *topState = state.get();
			stack.pushState(std::move(state));
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			stack.update();
			assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
			assertTrue(ASSERTION_PARAMETER(stack.topState() == topState));
		}

		void StateStackTestSuite::pushStateTestTwoPushes()
		{
			engine::stateStack::StateStack stack;
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			auto state = std::make_unique<engine::stateStack::StateBase>();
			stack.pushState(std::move(state));

			state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *topState = state.get();
			stack.pushState(std::move(state));

			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));
			stack.update();
			assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
			assertTrue(ASSERTION_PARAMETER(stack.topState() == topState));
		}

		void StateStackTestSuite::popStateTestOnePop()
		{
			engine::stateStack::StateStack stack;
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			auto state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *firstState = state.get();
			stack.pushState(std::move(state));

			state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *topState = state.get();
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
			engine::stateStack::StateStack stack;
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			auto state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *firstState = state.get();
			stack.pushState(std::move(state));

			state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *topState = state.get();
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
			engine::stateStack::StateStack stack;
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			auto state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *topState = state.get();
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
			catch(const engine::test::GameAssertException &)
			{
				assertDone = true;
			}
			assertTrue(ASSERTION_PARAMETER(assertDone));
		}

		void StateStackTestSuite::changeStateTest()
		{
			engine::stateStack::StateStack stack;
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			auto state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *currentState = state.get();
			stack.pushState(std::move(state));
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			stack.update();
			auto newState = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *nextState = newState.get();
			currentState->changeState(std::move(newState));

			assertTrue(ASSERTION_PARAMETER(currentState->isLeaving()));
			assertTrue(ASSERTION_PARAMETER(currentState->isActive()));
			assertTrue(ASSERTION_PARAMETER(currentState == stack.topState()));

			stack.update();

			assertTrue(ASSERTION_PARAMETER(nextState == stack.topState()));

		}

		void StateStackTestSuite::changeStateTestDouble()
		{
			engine::stateStack::StateStack stack;
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			auto state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *currentState = state.get();
			stack.pushState(std::move(state));
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			stack.update();
			auto newState = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *nextState = newState.get();
			currentState->changeState(std::move(newState));

			assertTrue(ASSERTION_PARAMETER(currentState->isLeaving()));
			assertTrue(ASSERTION_PARAMETER(currentState->isActive()));
			assertTrue(ASSERTION_PARAMETER(currentState == stack.topState()));

			auto newState2 = std::make_unique<engine::stateStack::StateBase>();
			bool assertionDone = false;
			try
			{
				currentState->changeState(std::move(newState2));
			}
			catch(engine::test::GameAssertException &)
			{
				assertionDone = true;
			}

			assertTrue(ASSERTION_PARAMETER(assertionDone));
		}

		void StateStackTestSuite::exitStateTest()
		{
			engine::stateStack::StateStack stack;
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			auto state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *currentState = state.get();
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
			engine::stateStack::StateStack stack;
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			auto state = std::make_unique<engine::stateStack::StateBase>();
			stack.pushState(std::move(state));

			state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *topState = state.get();
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
			catch(engine::test::GameAssertException &)
			{
				assertionDone = true;
			}
			assertTrue(ASSERTION_PARAMETER(assertionDone));
		}

		void StateStackTestSuite::exitStateAndChangeState()
		{
			engine::stateStack::StateStack stack;
			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));

			auto state = std::make_unique<engine::stateStack::StateBase>();
			stack.pushState(std::move(state));

			state = std::make_unique<engine::stateStack::StateBase>();
			engine::stateStack::StateBase *topState = state.get();
			stack.pushState(std::move(state));

			assertTrue(ASSERTION_PARAMETER(stack.isEmpty()));
			stack.update();
			assertTrue(ASSERTION_PARAMETER(!stack.isEmpty()));
			assertTrue(ASSERTION_PARAMETER(stack.topState() == topState));
			topState->exitState();
			bool assertionDone = false;
			try
			{
				auto newState = std::make_unique<engine::stateStack::StateBase>();
				topState->changeState(std::move(newState));
			}
			catch(engine::test::GameAssertException &)
			{
				assertionDone = true;
			}
			assertTrue(ASSERTION_PARAMETER(assertionDone));
		}
	}
}
