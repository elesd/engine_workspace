#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>


namespace engine
{
	class StateBase;
	/**
	 * This class is responsible to handle game state changes.
	 * This stack has 2 face, one is not midified during the current
	 * frame execution, the other one is changing when push or pop
	 * is called. At the begining of the frame the update of the stack
	 * is called and it applies the modification what was done in the
	 * previous frame.
	 */
	class StateStack final :
		private engine::NonCopyable,
		private engine::NonMoveable
	{
	public:
		/** Container for states*/
		using StateList = std::list < StateBase* > ;

	public:
		/** Default constuctor*/
		StateStack();
		/**
		 * Non virtual destructor.
		 * Further inheritance is not allowed.
		 */
		~StateStack();

		/**
		 * Update the stack.
		 * All the modifications from the previous frame will be applied
		 * in this function, and calls the top state's update.
		 */
		void update();

		/**
		 * Render the top state if it exists.
		 */
		void render();

		/**
		 * Pushes a new state to the top of the stack.
		 * @param state: State to push to the top.
		 * @warning This function will be applied only in the next frame.
		 */
		void pushState(std::unique_ptr<StateBase> state);

		/**
		 * Pops the top from the stack.
		 * @warning This function will be applied only in the next frame.
		 */
		void popState();

		/**
		 * Trace the states in the container.
		 * @param os: stream where data will dumped.
		 */
		void trace(std::ostream &os) const;

		/**
		* @return Returns true if it is empty.
		* @warning The stack is constant in the frame, so pop end push functions
		*			are ignored and this function returns the top of the previous frame.
		*/
		bool isEmpty() const;
	private:
		/**
		 * @return Returns the top state
		 * @warning The stack is constant in the frame, so pop end push functions
		 *			are ignored and this function returns the top of the previous frame.
		 */
		StateBase *topState();


		/**
		 * Processes the state manipulations in the previous states.
		 * First it pauses the current top state. After it applies the manipulations
		 * if it is neccessary call the destroy function on states which are removed from
		 * the stack.
		 * Finally it initialize the top state if it wasn't initialized and after call the
		 * resum function on it.
		 */
		void processModifications();

		/**
		 * @param a: Collection of states in left hand side parameter of set difference
		 * @param b: Collection of states in right hand side parameter of set difference
		 * @return Collect those states which are in a but not in b (a \ b)
		 */
		StateList getStateDifference(const StateList &a, const StateList &b) const;
	private:
		/** PIMPL */
		struct StateStackPrivate *_members = nullptr;
	};
}
