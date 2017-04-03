#pragma once

namespace engine
{
	/**
	* Default move functionality for PIMPL classes
	* @tparam T: class with PIMPL
	* @warning implementation of move with this class is slower - it can't use initialization list.
	* @warning no virtual destructor is available use private or protected inheritance
	*/
	template<class T>
	struct PIMPLMoveable
	{
		/** Default constructable*/
		PIMPLMoveable() = default;

		/**
		* Move implementation.
		* @param o: other object
		*/
		PIMPLMoveable(PIMPLMoveable &&o)
		{
			static_cast<T*>(this)->_members = static_cast<T&&>(o)._members;
			static_cast<T&&>(o)._members = nullptr;
		}

		/**
		* Move assign implementation.
		* @param o: other object
		* @return Returns with a reference to this.
		*/
		T& PIMPLMoveable::operator=(PIMPLMoveable &&o)
		{
			static_cast<T*>(this)->_members = static_cast<T&&>(o)._members;
			static_cast<T&&>(o)._members = nullptr;
			return *static_cast<T*>(this);
		}
	};
}