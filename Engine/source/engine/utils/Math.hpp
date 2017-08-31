
namespace engine
{
	namespace math
	{
		template<glm::length_t L, typename T, glm::precision P, template<glm::length_t, typename, glm::precision> class vecType>
		bool notEquals(const vecType<L, T, P>& a, const vecType<L, T, P>& b, const T& epsilon)
		{
			return glm::any(glm::epsilonNotEqual(a, b, epsilon));
		}

		template<glm::length_t L, typename T, glm::precision P, template<glm::length_t, glm::length_t, typename, glm::precision> class matType>
		bool notEquals(const matType<L, L, T, P>& a, const matType<L, L, T, P>& b, const T& epsilon)
		{
			bool equal = true;
			for(glm::length_t i = 0; i < L && equal; ++i)
			{
				equal = equal && notEquals(a[i], b[i], epsilon) == false;
			}
			return !equal;
		}
	}
}