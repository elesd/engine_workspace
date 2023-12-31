#pragma once

#include <engine/constraints/NonCopyable.h>

#include <engine/signalSlot/Signal.h>
#include <engine/signalSlot/SlotHolder.h>

namespace engine
{
	class StateStack;
	class Context;
	class Console;
	class Applicaiton;
	class Window;

	/**
	 * Base class for game states. This class is managed by the
	 * state stack.
	 */
	class StateBase 
		: public engine::NonCopyable
		, public SlotHolder
	{
	protected:
		/**
		 * Construct a state.
		 * The object must not been initialized by the constructor,
		 * it can be done during initialization.
		 * @see initState
		 */
		StateBase(const std::string &name, Window* windowOnOperate);

	public:
		/**
		 * Destroy the state.
		 * The object also can be destroyed by other function simirary
		 * as it was in constructed.
		 * @see destroyState
		 */
		virtual ~StateBase();

		/**
		 * This function initialize this state.
		 * A state can change the stack and can go another states.
		 * It has two possible way push a new state to the stack
		 * or remove the current state from the stack. To do this
		 * the state must know the corresponding stack.
		 * @param stack: corresponding stack.
		 */
		void initialize(StateStack *stack);

		/**
		 * Destory this state;
		 */
		void destroy();

		/**
		 * Resume is called when a state becomes active so when it
		 * is on the top of the stack.
		 * Only initialized states can be resumed.
		 */
		void resume();

		/**
		* Pause is called when a state becomes inactive so when it
		* is not on the top of the stack.
		* It can be done in two way someone is pushed above this
		* state or the current state is popped from the stack.
		* Only initialized states can be paused.
		* @see changeState
		* @see exitState
		*/
		void pause();

		/**
		 * The active state is updated in each frame.
		 */
		void update();

		/**
		 * @return true when the state is initialized and not destroyed.
		 */
		bool isInitialized() const;

		/**
		 * trace informations about this state.
		 */
		void trace(std::ostream &) const;

		ISignalManager* getSignalManager() const override final;
	protected:
		Window* getWindow() const;

		Context* getContext() const;

		Console* getConsole() const;

		/**
		 * A state is active when the resume is called on the state
		 * but the pause isn't yet.
		 */
		bool isActive() const;

		/**
		 * When a state is leaving it's active but in the next frame
		 * it won't be at the top of the stack.
		 * @return Returns true when exit or change state has been called already.
		 */
		bool isLeaving() const;

		/**
		 * Push an other state to top of the corresponding state stack.
		 * @param nextState: state which is pushed on the top of the stack.
		 */
		void changeState(std::unique_ptr<StateBase> nextState);

		/**
		 * Remove this state from the stack.
		 * @warning Only the active state can call this function.
		 */
		void exitState();
	private:
		/** Initialization function for the derived state */
		virtual void initState() {};
		/** Destroy function for the derived state */
		virtual void destroyState() {};

		/** Resume function for the derived state */
		virtual void resumeState() {};
		/** Pause function for the derived state */
		virtual void pauseState() {};

		/** Update function for the derived state */
		virtual void updateState() {};
	protected:
		/**
		 * Signal for state changes to a next state.
		 * The parameter is a pointer to the next state.
		 * @see changeState
		 */
		Signal<StateBase*> stateChanged;
		/** Signal for state exit. @see exitState*/
		Signal<> stateTerminated;
	private:
		/** PIMPL */
		struct StateBasePrivate *_members = nullptr;
	};
}
