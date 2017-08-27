#pragma once

#include <engine/utils/Math.h>
namespace engine
{
	namespace math
	{
		template<glm::length_t L, typename T, glm::precision P, template<glm::length_t, typename, glm::precision> class vecType>
		bool notEquals(const vecType<L, T, P>& a, const vecType<L, T, P>& b, const T& epsilon)
		{
			return glm::all(glm::epsilonNotEqual(a, b, epsilon));
		}

		template<glm::length_t L, typename T, glm::precision P, template<glm::length_t, glm::length_t, typename, glm::precision> class matType>
		bool notEquals(const matType<L, L, T, P>& a, const matType<L, L, T, P>& b, const T& epsilon)
		{
			bool notEqual = true;
			for(glm::length_t i = 0; i < L && notEqual; ++i)
			{
				notEqual = notEqual && notEquals(a[i], b[i], epsilon);
			}
			return notEqual;
		}
	}
}