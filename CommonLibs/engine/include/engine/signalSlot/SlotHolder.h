#pragma once

/**
 * @file SlotHolder.h
 * Interface for slot holders
 */

namespace engine
{
	class ISignalManager;
	class ISignal;
	/**
	* To handle emitted signals a kind of Signal Manager is necessary.
	* To fix the interface inherit your slot holders from this class.
	*/
	class SlotHolder
	{
	public:
		SlotHolder();
		// Disconnect from all signal
		virtual ~SlotHolder();

		/**
		* @return Returns the corresponding SignalManager, who will manage the tasks.
		*/
		virtual ISignalManager* getSignalManager() const = 0;

		/**
		* Assign a signal to this slot.
		* It is necessery because when this object is destroyed, it must tell to
		* the signal that's not alived.
		*/
		void assignSignal(ISignal *signal);

		/**
		* Remove signal from this slots.
		*/
		void removeSignal(ISignal *signal);

	private:
		/** PIMPL */
		struct SlotHolderPrivate *_members = nullptr;
	};
}
