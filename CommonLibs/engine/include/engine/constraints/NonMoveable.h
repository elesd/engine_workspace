#pragma once

namespace engine
{
	/**
	* All classes derived from this class are not
	* moveable.
	* @warning Only private inheritance allowed.
	*/
	struct NonMoveable
	{
		/** Default constructable from child classes */
		NonMoveable() = default;

		~NonMoveable() {}
		/** forbid move constructor */
		NonMoveable(NonMoveable &&) = delete;
		/** forbid move assignment */
		NonMoveable &operator=(NonMoveable &&) = delete;

	};
}
