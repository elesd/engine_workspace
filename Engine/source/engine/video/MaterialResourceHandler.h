#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Material;

	class MaterialResourceHandler final
		: private NonCopyable
		, private NonMoveable
	{
	public:
		explicit MaterialResourceHandler(Material* material);
		~MaterialResourceHandler();

		void setFloat(const std::string& resourceName, float value);
		void setVec2(const std::string& resourceName, const vec2& value);
		void setVec3(const std::string& resourceName, const vec3& value);
		void setVec4(const std::string& resourceName, const vec4& value);
		void setMat3(const std::string& resourceName, const mat3& value);
		void setMat4(const std::string& resourceName, const mat4& value);
	private:
		struct MaterialResourceHandlerPrivate* _members = nullptr;
	};
}