#pragma once

#include <engine/constraints/NonCopyable.h>

#include <engine/video/GlobalShaderResource.h>

namespace engine
{
	class ShaderResourceHandler;
	class ShaderResourceDescription;
	class ShaderResourceDescription;
	class GlobalResourceMapping;
	enum class GPUMemberType;

	class GlobalShaderResourceStorage final
		: private NonCopyable
	{
	public:
		GlobalShaderResourceStorage(GlobalShaderResourceStorage* parentStorage = nullptr);
		GlobalShaderResourceStorage(GlobalShaderResourceStorage&&);
		~GlobalShaderResourceStorage();

		void initGlobalResources(const GlobalResourceMapping&);

		GlobalShaderResourceStorage& operator=(GlobalShaderResourceStorage&&);

		void addResource(const ShaderResourceDescription& desc);
		bool hasResource(const std::string& resourceName, GPUMemberType type) const;

		void calculateAggregatedResources();

		std::vector<ShaderResourceDescription> collectResources() const;

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

		GlobalShaderResource<GPUMemberType::Float>* findFloatResource(const std::string& name) const;
		GlobalShaderResource<GPUMemberType::Vec2>* findVec2Resource(const std::string& name) const;
		GlobalShaderResource<GPUMemberType::Vec3>* findVec3Resource(const std::string& name) const;
		GlobalShaderResource<GPUMemberType::Vec4>* findVec4Resource(const std::string& name) const;
		GlobalShaderResource<GPUMemberType::Mat3>* findMat3Resource(const std::string& name) const;
		GlobalShaderResource<GPUMemberType::Mat4>* findMat4Resource(const std::string& name) const;
	private:
		struct GlobalShaderResourceStoragePrivate* _members = nullptr;
	};


}