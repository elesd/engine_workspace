#pragma once

namespace engine
{
	/**Small hack for identity*/
	template<class T>
	struct DeclTypeToType
	{
		/**Result of the meta function*/
		using Value = T;
	};
}