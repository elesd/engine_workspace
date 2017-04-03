#pragma once

namespace engine
{
	/**
	* Default copy functionality for PIMPL classes
	* @tparam T: class with PIMPL
	* @warning implementation of copy with this class is slower - it can't use initialization list.
	* @warning no virtual destructor is available use private or protected inheritance
	*/
	template<class T>
	struct PIMPLCopyable
	{
		/** Default constructable*/
		PIMPLCopyable() = default;
		/**
		* Copy implementation.
		* @param o: other object
		*/
		PIMPLCopyable(const PIMPLCopyable &o)
		{
			static_cast<T*>(this)->_members = new std::remove_ptr(decltype(static_cast<T*>(this)->_members));
			*static_cast<T*>(this)->_members = static_cast<T&>(o)._members;
		}

		/**
		* Copy assign implementation.
		* @param o: other object
		* @return Returns with a reference to this.
		*/
		T& PIMPLCopyable::operator=(const PIMPLCopyable &o)
		{
			delete static_cast<T*>(this)->_members;
			static_cast<T*>(this)->_members = new std::remove_ptr(decltype(static_cast<T*>(this)->_members));
			*static_cast<T*>(this)->_members = static_cast<T&>(o)._members;
			return *static_cast<T*>(this);
		}
	};
}