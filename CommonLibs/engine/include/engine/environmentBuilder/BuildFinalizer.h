#pragma once

#include "engine/environmentBuilder/BaseBuilder.h"

namespace engine
{
	/**
	* Last build step.
	* Ensure that the build process reaches the end of the creation.
	* Without this build phase the context cannot be used.
	*/
	class BuildFinalizer : public BaseBuilder
	{
	public:
		/**Defualt constructor*/
		BuildFinalizer() = default;
		/**Moveable*/
		BuildFinalizer(BuildFinalizer &&) {}

		/** Finish building process, no more step left. */
		void build();
	};
}
