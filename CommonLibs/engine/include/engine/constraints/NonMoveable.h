#pragma once

namespace engine
{
	namespace constraints
	{
		/**
		* All classes derived from this class are not
		* moveable.
		*/
		class NonMoveable
		{
		protected:
			/** Default constructable from child classes */
			NonMoveable() = default;

			virtual ~NonMoveable() {}
			/** forbid move constructor */
			NonMoveable(NonMoveable &&) = delete;
			/** forbid move assignment */
			NonMoveable &operator=(NonMoveable &&) = delete;

		};
	}
}
