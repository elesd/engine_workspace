#include "stdafx.h"

#include "stateStack/StateBaseTestSuit.h"

#include "engine/exceptions/LogicalErrors.h"
#include "engine/stateStack/StateBase.h"
#include "engine/stateStack/StateStack.h"



#include <engine/utils/StdUtils.h>
namespace
{
	struct TestState : engine::StateBase
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
			: StateBase("TestState"),
			action(point), type(type)
		{}

		void resumeState() override
		{
			if(action == ActionPoint::OnResume)
			{
				if(type == ActionType::Change)
				{
					changeState(std::make_unique<engine::StateBase>("test"));
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
					changeState(std::make_unique<engine::StateBase>("test"));
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
		engine::StateStack globalStack;
	};
	TestEnvironment testEnvironment;
}

namespace tests
{
	void StateBaseTestSuit::initTest01()
	{
		engine::StateBase state("test");
		assertTrue(ASSERTION_PARAMETER(!state.isInitialized()));
		state.initialize(&testEnvironment.globalStack);
		assertTrue(ASSERTION_PARAMETER(state.isInitialized()));
		assertTrue(ASSERTION_PARAMETER(!state.isActive()));
		state.destroy();
	}

	void StateBaseTestSuit::resumeTest()
	{
		engine::StateBase state("test");
		assertTrue(ASSERTION_PARAMETER(!state.isInitialized()));
		state.initialize(&testEnvironment.globalStack);
		assertTrue(ASSERTION_PARAMETER(state.isInitialized()));
		assertTrue(ASSERTION_PARAMETER(!state.isActive()));

		state.resume();
		assertTrue(ASSERTION_PARAMETER(state.isActive()));
		state.destroy();
	}

	void StateBaseTestSuit::pauseTest()
	{
		engine::StateBase state("test");
		assertTrue(ASSERTION_PARAMETER(!state.isInitialized()));
		state.initialize(&testEnvironment.globalStack);
		assertTrue(ASSERTION_PARAMETER(state.isInitialized()));
		assertTrue(ASSERTION_PARAMETER(!state.isActive()));

		state.resume();
		assertTrue(ASSERTION_PARAMETER(state.isActive()));

		state.pause();
		assertTrue(ASSERTION_PARAMETER(!state.isActive()));
		state.destroy();
	}

	void StateBaseTestSuit::exitDuringResum()
	{
		engine::StateStack stack;
		testEnvironment.globalStack.pushState(std::make_unique<TestState>(TestState::ActionPoint::OnResume, TestState::ActionType::Exit));
		bool hasException = false;
		try
		{
			testEnvironment.globalStack.update();
		}
		catch(engine::WrongStateError &)
		{
			hasException = true;
		}
		assertTrue(ASSERTION_PARAMETER(hasException));
	}

	void StateBaseTestSuit::changeDuringResum()
	{
		engine::StateStack stack;

		stack.pushState(std::make_unique<TestState>(TestState::ActionPoint::OnResume, TestState::ActionType::Exit));
		bool hasException = false;
		try
		{
			stack.update();
		}
		catch(engine::WrongStateError &)
		{
			hasException = true;
		}
		assertTrue(ASSERTION_PARAMETER(hasException));

	}

	void StateBaseTestSuit::exitDuringPause()
	{
		engine::StateStack stack;
		bool hasException = false;
		stack.pushState(std::make_unique<TestState>(TestState::ActionPoint::OnPause, TestState::ActionType::Change));
		stack.update();
		stack.popState();
		try
		{
			stack.update();
		}
		catch(engine::WrongStateError &)
		{
			hasException = true;
		}
		assertTrue(ASSERTION_PARAMETER(hasException));
	}

	void StateBaseTestSuit::changeDuringPause()
	{
		engine::StateStack stack;
		bool hasException = false;
		stack.pushState(std::make_unique<TestState>(TestState::ActionPoint::OnPause, TestState::ActionType::Change));
		stack.update();
		stack.popState();
		try
		{
			stack.update();
		}
		catch(engine::WrongStateError&)
		{
			hasException = true;
		}
		assertTrue(ASSERTION_PARAMETER(hasException));
	}
}
