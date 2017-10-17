#pragma once

namespace engine
{
	class ShaderResourceStorage;

	class ShaderResourceStorageProxy final
	{
	public:
		ShaderResourceStorageProxy();
		~ShaderResourceStorageProxy();

		ShaderResourceStorageProxy(const ShaderResourceStorageProxy&);
		ShaderResourceStorageProxy(ShaderResourceStorageProxy&&);

		ShaderResourceStorageProxy operator=(const ShaderResourceStorageProxy&);
		ShaderResourceStorageProxy operator=(ShaderResourceStorageProxy&&);

		void setFloat(const std::string& resourceName, float);
		float getFloat(const std::string& resourceName) const;

		void setVec2(const std::string& resourceName, const vec2&);
		const vec2& getVec2(const std::string& resourceName) const;

		void setVec3(const std::string& resourceName, const vec3&);
		const vec3& getVec3(const std::string& resourceName) const;

		void setVec4(const std::string& resourceName, const vec4&);
		const vec4& getVec4(const std::string& resourceName) const;

		void setMat3(const std::string& resourceName, const mat3&);
		const mat3& getMat3(const std::string& resourceName) const;

		void setMat4(const std::string& resourceName, const mat4&);
		const mat4& getMat4(const std::string& resourceName) const;

	private:
		struct ShaderResourceStorageProxyPrivate* _members = nullptr;
	};
}