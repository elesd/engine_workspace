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
		std::vector<std::pair<std::string, float>> clearChangesInFloats();

		void setVec2(const std::string& resourceName, const vec2&);
		const vec2& getVec2(const std::string& resourceName) const;
		std::vector<std::pair<std::string, vec2>> clearChangesInVec2();

		void setVec3(const std::string& resourceName, const vec3&);
		const vec3& getVec3(const std::string& resourceName) const;
		std::vector<std::pair<std::string, vec3>> clearChangesInVec3();

		void setVec4(const std::string& resourceName, const vec4&);
		const vec4& getVec4(const std::string& resourceName) const;
		std::vector<std::pair<std::string, vec4>> clearChangesInVec4();

		void setMat3(const std::string& resourceName, const mat3&);
		const mat3& getMat3(const std::string& resourceName) const;
		std::vector<std::pair<std::string, mat3>> clearChangesInMat3();

		void setMat4(const std::string& resourceName, const mat4&);
		const mat4& getMat4(const std::string& resourceName) const;
		std::vector<std::pair<std::string, mat4>> clearChangesInMat4();

	private:
		struct ShaderResourceStorageProxyPrivate* _members = nullptr;
	};
}