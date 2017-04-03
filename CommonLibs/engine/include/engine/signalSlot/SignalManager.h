#pragma once

#include <engine/signalSlot/ISignalManager.h>
#include <engine/constraints/NonCopyable.h>

namespace engine
{
	struct SignalManagerPrivate;

	/**
	* Simple signal manager implementation.
	* This manager has a container of tasks. During update of the manager the tasks are fired.
	* @see ISignalManager
	* @warning: not thread safe
	*/
	class SignalManager : public ISignalManager,
						  private NonCopyable
	{
	public:
		/** Default constructor, extension because of the PIMPL idiom.*/
		SignalManager();

		/** Default destructor, extension because of the PIMPL idiom.*/
		~SignalManager()  override;

		/**Moveable but not copyable*/
		SignalManager(SignalManager &&);
		/**Moveable but not copyable*/
		SignalManager &operator=(SignalManager &&);

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
