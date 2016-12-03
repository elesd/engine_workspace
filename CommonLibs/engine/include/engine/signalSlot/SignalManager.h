#pragma once

#include "engine/signalSlot/ISignalManager.h"

namespace engine
{
	struct SignalManagerPrivate;

	/**
	* Simple signal manager implementation.
	* This manager has a container of tasks. During update of the manager the tasks are fired.
	* @see ISignalManager
	*/
	class SignalManager : public ISignalManager
	{
	public:
		/** Default constructor, extension because of the PIMPL idiom.*/
		SignalManager();

		/** Default destructor, extension because of the PIMPL idiom.*/
		~SignalManager()  override;

		SignalManager(const SignalManager &o) = delete;
		SignalManager(SignalManager &&o) = delete;
		SignalManager operator=(const SignalManager &o) = delete;

		/**
		* Add a task to the container of this manager.
		*/
		void addTask(std::unique_ptr<ISignalTask> task) override;

		/**
		* All the tasks which are still valid will be executed.
		*/
		void update() override;
	private:
		/** private members*/
		SignalManagerPrivate *_members = nullptr;
	};
}
