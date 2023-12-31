#pragma once

#include <engine/video/DriverFeatures.h>

namespace engine
{
	template<engine::NDCType Type>
	struct ViewportCalculator;

	template<>
	struct ViewportCalculator<engine::NDCType::OpenGl>
	{
		static inline engine::vec3 normalScreenVectorToNDC(const engine::vec3& v)
		{
			// [0,1]^3 -> [-1,1]^3
			engine::vec3 result = v;
			result *= 2.0f;
			result -= engine::vec3(1.0f);
			return result;
		}

		static inline engine::vec3 ndcToNormalScreenVector(const engine::vec3& v)
		{
			// [-1,1]^3 -> [0,1]^3 
			engine::vec3 result = v;
			result += engine::vec3(1.0f);
			result /= 2.0f;
			return result;
		}

		static inline engine::mat4 adaptPorjectionMatrix(const engine::mat4& m)
		{
			return m;
		}
	};

	template<>
	struct ViewportCalculator<engine::NDCType::DirectX>
	{
		static inline engine::vec3 normalScreenVectorToNDC(const engine::vec3& v)
		{
			return v;
		}

		static inline engine::vec3 ndcToNormalScreenVector(const engine::vec3& v)
		{
			return v;
		}

		static inline engine::mat4 adaptPorjectionMatrix(const engine::mat4& m)
		{
			// [-1,1]^3 -> [-1,1]^2 x [0,1]
			//glm::scale(glm::vec3(1.0f, 1.0f, 0.5f)) * glm::translate(glm::vec3(1.0f, 1.0f, 1.0f)) * m;
			engine::mat4 result = glm::scale(vec3(1.0f, 1.0f, 0.5f));
			result *= glm::translate(engine::vec3(0.0f, 0.0f, 1.0f));
			result *= m;
			return result;
		}
	};
}