#include <stdafx.h>
#include <engine/signalSlot/IntermediateSlotHolder.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/signalSlot/IntermediateSignalManager.h>

namespace engine
{

	struct IntermediateSlotHolderPrivate
	{
		IntermediateSignalManager signalManager;
	};

	IntermediateSlotHolder::IntermediateSlotHolder()
		: _members(new IntermediateSlotHolderPrivate())
	{

	}

	IntermediateSlotHolder::IntermediateSlotHolder(const IntermediateSlotHolder& o)
		: SlotHolder(o)
		, _members(new IntermediateSlotHolderPrivate())
	{

	}

	IntermediateSlotHolder::IntermediateSlotHolder(IntermediateSlotHolder&& o)
		: SlotHolder(o)
		, _members(new IntermediateSlotHolderPrivate())
	{

	}

	IntermediateSlotHolder::~IntermediateSlotHolder()
	{
		delete _members;
		_members = nullptr;
	}

	IntermediateSlotHolder& IntermediateSlotHolder::operator=(const IntermediateSlotHolder& o)
	{
		SlotHolder::operator=(o);
		return *this;
	}

	IntermediateSlotHolder& IntermediateSlotHolder::operator=(IntermediateSlotHolder&& o)
	{
		SlotHolder::operator=(o);
		return *this;
	}

	ISignalManager* IntermediateSlotHolder::getSignalManager() const
	{
		return &_members->signalManager;
	}
}