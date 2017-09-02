#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class GlobalShaderResourceStorage;
	class ShaderResourceBinding;
	class ShaderResourceDescription;
	class ShaderResourceHandler;
	enum class GPUMemberType;

	class ShaderResourceStorage final
		: private NonCopyable
	{
	public:
		ShaderResourceStorage(std::unique_ptr<ShaderResourceHandler>&& resourceHandler, GlobalShaderResourceStorage* parentStorage = nullptr);
		ShaderResourceStorage(ShaderResourceStorage&&);
		~ShaderResourceStorage();
		
		ShaderResourceStorage& operator=(ShaderResourceStorage&&);

		void addResource(const ShaderResourceDescription& description);
		bool hasResource(const std::string& resourceName, GPUMemberType type) const;

		std::vector<ShaderResourceDescription> collectDescriptions() const;
		void setResourceBinding(std::vector<std::pair<ShaderResourceDescription, std::unique_ptr<ShaderResourceBinding>>>&& resourceBinding);

		void setFloat(const std::string& resourceName, float);
		float getFloat(const std::string& resourceName) const;

		void setVec2(const std::string& resourceName, const glm::vec2&);
		const glm::vec2& getVec2(const std::string& resourceName) const;

		void setVec3(const std::string& resourceName, const glm::vec3&);
		const glm::vec3& getVec3(const std::string& resourceName) const;

		void setVec4(const std::string& resourceName, const glm::vec4&);
		const glm::vec4& getVec4(const std::string& resourceName) const;

		void setMat3(const std::string& resourceName, const glm::mat3&);
		const glm::mat3& getMat3(const std::string& resourceName) const;

		void setMat4(const std::string& resourceName, const glm::mat4&);
		const glm::mat4& getMat4(const std::string& resourceName) const;

		void commitResources();
	private:
		void removeUnboundResources();
	private:
		struct ShaderResourceStoragePrivate* _members = nullptr;
	};
}
