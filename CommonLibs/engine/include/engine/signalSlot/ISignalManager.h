#pragma once

namespace engine
{
	class ISignalTask;

	/**
	* Interface of the signal manager.
	* Signals are created task during emit, this interface is responsible to
	* manage these tasks.
	*/
	class ISignalManager
	{
	protected:
		/** Default constructor*/
		ISignalManager() = default;
		/** Default destructor*/
		virtual ~ISignalManager() {};

	public:
		/**
		* Assign a task to the manager.
		* It's called when a task is emitted.
		*/
		virtual void addTask(std::unique_ptr<ISignalTask> task) = 0;

		/**
		* Update the manager.
		* It's for manage the tasks of the assigned manager.
		*/
		virtual void update() = 0;
	};
}
