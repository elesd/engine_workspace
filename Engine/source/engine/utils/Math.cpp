#include <stdafx.h>
#include <engine/utils/Math.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	namespace math
	{
		template<>
		bool notEquals<float>(const float& a, const float& b, const float& epsilon)
		{
			return glm::epsilonNotEqual(a, b, epsilon);
		}

		template<>
		bool notEquals<double>(const double& a, const double& b, const double& epsilon)
		{
			return glm::epsilonNotEqual(a, b, epsilon);
		}
	}
}
