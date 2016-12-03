#pragma once

namespace engine
{
	/**
	 * All classes derived from this class are not
	 * copiable.
	 */
	class NonCopyable
	{
	protected:
		/** Default constructable from child classes */
		NonCopyable() = default;

		virtual ~NonCopyable() {}

		/** forbid copy constructor */
		NonCopyable(const NonCopyable &) = delete;

		/** forbid copy assignment */
		NonCopyable &operator=(const NonCopyable &) = delete;

	};
}
