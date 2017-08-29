#pragma once

#include <engine/signalSlot/SlotHolder.h>

namespace engine
{
	class ISignalManager;
	class ISignal;

	class IntermediateSlotHolder
		: public SlotHolder
	{
	public:
		IntermediateSlotHolder();
		IntermediateSlotHolder(const IntermediateSlotHolder&);
		IntermediateSlotHolder(IntermediateSlotHolder&&);
		~IntermediateSlotHolder() override;

		IntermediateSlotHolder& operator=(const IntermediateSlotHolder&);
		IntermediateSlotHolder& operator=(IntermediateSlotHolder&&);

		ISignalManager* getSignalManager() const override;

	private:
		/** PIMPL */
		struct IntermediateSlotHolderPrivate *_members = nullptr;
	};
}
