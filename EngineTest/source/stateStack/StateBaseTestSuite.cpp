#include "stdafx.h"

#include "stateStack/StateBaseTestSuite.h"
#include "engine/stateStack/StateBase.h"
#include "engine/stateStack/StateStack.h"


#include <engine/utils/StdUtils.h>
namespace
{
	struct TestState : engine::stateStack::StateBase
	{
		enum class ActionPoint
		{
			OnResume,
			OnPause
		};

		enum class ActionType
		{
			Exit,
			Change
		};
		TestState(ActionPoint point, ActionType type)
			:action(point), type(type)
		{}

		void resumeState() override
		{
			if(action == ActionPoint::OnResume)
			{
				if(type == ActionType::Change)
				{
					changeState(std::make_unique<engine::stateStack::StateBase>());
				}
				else
				{
					exitState();
				}
			}
		}

		void pauseState() override
		{
			if(action == ActionPoint::OnPause)
			{
				if(type == ActionType::Change)
				{
					changeState(std::make_unique<engine::stateStack::StateBase>());
				}
				else
				{
					exitState();
				}
			}
		}

		ActionPoint action;
		ActionType type;

	};
	struct TestEnvironment
	{
		engine::stateStack::StateStack globalStack;
	};
	TestEnvironment testEnvironment;
}

namespace tests
{
	namespace stateStack
	{
		void StateBaseTestSuite::initTest01()
		{
			engine::stateStack::StateBase state;
			assertTrue(ASSERTION_PARAMETER(!state.isInitialized()));
			state.initialize(&testEnvironment.globalStack);
			assertTrue(ASSERTION_PARAMETER(state.isInitialized()));
			assertTrue(ASSERTION_PARAMETER(!state.isActive()));
		}

		void StateBaseTestSuite::resumeTest()
		{
			engine::stateStack::StateBase state;
			assertTrue(ASSERTION_PARAMETER(!state.isInitialized()));
			state.initialize(&testEnvironment.globalStack);
			assertTrue(ASSERTION_PARAMETER(state.isInitialized()));
			assertTrue(ASSERTION_PARAMETER(!state.isActive()));

			state.resume();
			assertTrue(ASSERTION_PARAMETER(state.isActive()));
		}

		void StateBaseTestSuite::pauseTest()
		{
			engine::stateStack::StateBase state;
			assertTrue(ASSERTION_PARAMETER(!state.isInitialized()));
			state.initialize(&testEnvironment.globalStack);
			assertTrue(ASSERTION_PARAMETER(state.isInitialized()));
			assertTrue(ASSERTION_PARAMETER(!state.isActive()));

			state.resume();
			assertTrue(ASSERTION_PARAMETER(state.isActive()));

			state.pause();
			assertTrue(ASSERTION_PARAMETER(!state.isActive()));
		}

		void StateBaseTestSuite::exitDuringResum()
		{
			engine::stateStack::StateStack stack;
			testEnvironment.globalStack.pushState(std::make_unique<TestState>(TestState::ActionPoint::OnResume, TestState::ActionType::Exit));
			bool hasException = false;
			try
			{
				testEnvironment.globalStack.update();
			}
			catch(engine::test::GameAssertException &)
			{
				hasException = true;
			}
			assertTrue(ASSERTION_PARAMETER(hasException));
		}

		void StateBaseTestSuite::changeDuringResum()
		{
			engine::stateStack::StateStack stack;

			stack.pushState(std::make_unique<TestState>(TestState::ActionPoint::OnResume, TestState::ActionType::Exit));
			bool hasException = false;
			try
			{
				stack.update();
			}
			catch(engine::test::GameAssertException &)
			{
				hasException = true;
			}
			assertTrue(ASSERTION_PARAMETER(hasException));

		}

		void StateBaseTestSuite::exitDuringPause()
		{
			engine::stateStack::StateStack stack;
			bool hasException = false;
			stack.pushState(std::make_unique<TestState>(TestState::ActionPoint::OnPause, TestState::ActionType::Change));
			stack.update();
			stack.popState();
			try
			{
				stack.update();
			}
			catch(engine::test::GameAssertException &)
			{
				hasException = true;
			}
			assertTrue(ASSERTION_PARAMETER(hasException));
		}

		void StateBaseTestSuite::changeDuringPause()
		{
			engine::stateStack::StateStack stack;
			bool hasException = false;
			stack.pushState(std::make_unique<TestState>(TestState::ActionPoint::OnPause, TestState::ActionType::Change));
			stack.update();
			stack.popState();
			try
			{
				stack.update();
			}
			catch(engine::test::GameAssertException &)
			{
				hasException = true;
			}
			assertTrue(ASSERTION_PARAMETER(hasException));
		}
	}
}
