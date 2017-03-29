#pragma once

namespace engine
{
	/**
	 * All classes derived from this class are not
	 * copiable.
	 * @warning Only private inharitance allowed.
	 */
	struct NonCopyable
	{
		/** Default constructable from child classes */
		NonCopyable() = default;

		/** Non virtual destructor.*/
		~NonCopyable() {}

		/** forbid copy constructor */
		NonCopyable(const NonCopyable &) = delete;

		/** forbid copy assignment */
		NonCopyable &operator=(const NonCopyable &) = delete;

	};
}
