#pragma once

#include <engine/signalSlot/ISignalManager.h>
#include <engine/constraints/NonCopyable.h>

namespace engine
{
	struct SignalManagerPrivate;

	class IntermediateSignalManager
		: public ISignalManager
		, private NonCopyable
	{
	public:
		IntermediateSignalManager() = default;

		~IntermediateSignalManager() override {};

		void addTask(std::unique_ptr<ISignalTask> task) override;

		void update() override {};
	};
}
