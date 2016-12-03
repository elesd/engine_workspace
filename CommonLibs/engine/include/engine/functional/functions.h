#pragma once

namespace engine
{
	/**
	 * Functional for equality check in standard algorithms.
	 */
	template<typename T>
	struct EqualTo
	{
		/**
		 * Create the function from the given value to check.
		 * @param v: value to check the equality
		 */
		explicit EqualTo(const T &v) : _value(v){}

		/**
		 * Check whether the given object equals to our one.
		 * @param o: object to check whether equals to the stored value.
		 * @return Returns true if the given object equals to the stored one.
		 */
		bool operator()(const T &o) { return o == _value; }

	private:
		/** Stored pointer */
		T _value;
	};

	/**
	* Functional for equality check in standard algorithms for different
	* pointer types.
	*/
	template<typename T>
	struct PointerEqualTo
	{
		/** Type without pointer */
		using ValueType = typename std::remove_pointer<T>::type;
		/** Raw pointer type*/
		using RawPointerType = ValueType*;
		/** Unique pointer type*/
		using UniquePointerType = std::unique_ptr < ValueType > ;
		/** Shared pointer type*/
		using SharedPointerType = std::shared_ptr < ValueType > ;
		/** Weak pointer type*/
		using WeakPointerType = std::weak_ptr < ValueType > ;

		/**
		 * Construct the equality check
		 * @param v: pointer to check
		 */
		PointerEqualTo(const RawPointerType &v) : _value(v) {}



		/**
		* Check whether the given object equals to our one.
		* @param o: object to check whether equals to the stored value.
		* @return Returns true if the given object equals to the stored one.
		*/
		bool operator()(const RawPointerType &o) { return o == _value; }
		/**
		* Check whether the given object equals to our one.
		* @param o: object to check whether equals to the stored value.
		* @return Returns true if the given object equals to the stored one.
		*/
		bool operator()(const UniquePointerType &o) { return o.get() == _value; }
		/**
		* Check whether the given object equals to our one.
		* @param o: object to check whether equals to the stored value.
		* @return Returns true if the given object equals to the stored one.
		*/
		bool operator()(const SharedPointerType &o) { return o.get() == _value; }
		/**
		* Check whether the given object equals to our one.
		* @param o: object to check whether equals to the stored value.
		* @return Returns true if the given object equals to the stored one.
		*/
		bool operator()(const WeakPointerType &o)
		{
			if(o.expired())
				return false;

			SharedPointerType otmp = o.lock();
			return PointerEqualTo::operator()(otmp);
		}

	private:
		/** Stored pointer */
		RawPointerType _value;
	};
}