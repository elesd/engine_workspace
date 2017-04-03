#pragma once

namespace engine
{
	class SlotHolder;
	/**
	* Type independent signal
	*/
	class ISignal
	{
		friend class SlotHolder;
	public:
		virtual ~ISignal() {};
	private:
		/**
		* Disconnect all signal from the slot.
		* It is necessary for the slot holder destructor;
		*/
		virtual void disconnectAllSlot(SlotHolder *slotHolder) = 0;
	};
}
