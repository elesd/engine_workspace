#pragma once

namespace engine
{
	namespace math
	{
		template<typename T>
		bool notEquals(const T& a, const T& b, const T& epsilon);

		template<>
		bool notEquals<float>(const float& a, const float& b, const float& epsilon);
	
		template<>
		bool notEquals<double>(const double& a, const double& b, const double& epsilon);

		template<glm::length_t L, typename T, glm::precision P, template<glm::length_t, typename, glm::precision> class vecType>
		bool notEquals(const vecType<L, T, P>& a, const vecType<L, T, P>& b, const T& epsilon);

		template<glm::length_t L, typename T, glm::precision P, template<glm::length_t, glm::length_t, typename, glm::precision> class matType>
		bool notEquals(const matType<L, L, T, P>& a, const matType<L, L, T, P>& b, const T& epsilon);
	}
}

#include <engine/utils/Math.hpp>
