#pragma once

namespace engine
{
	class GlobalShaderResourceStorage;

	enum class GlobalResource
	{
		WorldMatrix,
		InvWorldMatrix,
		ViewMatrix,
		InvViewMatrix,
		ProjectionViewMatrix,
		InvProjectionViewMatrix,
		ProjectionMatrix,
		InvProjectionMatrix,
		ProjectionViewWorldMatrix,
		InvProjectionViewWorldMatrix,
		ViewWorldMatrix,
		InvViewWorldMatrix,
		CameraPosition
	};

	class GlobalResourceMapping
	{
	public:
		static const std::vector<GlobalResource>& getFloatResources();
		static const std::vector<GlobalResource>& getVec2Resources();
		static const std::vector<GlobalResource>& getVec3Resources();
		static const std::vector<GlobalResource>& getVec4Resources();
		static const std::vector<GlobalResource>& getMat3Resources();
		static const std::vector<GlobalResource>& getMat4Resources();
	public:
		GlobalResourceMapping() = default;
		explicit GlobalResourceMapping(const std::map<GlobalResource, std::string>& mapping);
		~GlobalResourceMapping();
		
		GlobalResourceMapping(const GlobalResourceMapping&);
		GlobalResourceMapping(GlobalResourceMapping&&);

		GlobalResourceMapping& operator=(const GlobalResourceMapping&);
		GlobalResourceMapping& operator=(GlobalResourceMapping&&);

		const std::string& operator[](GlobalResource resource) const;
		bool hasResource(GlobalResource resource) const;
		bool isInitialized() const;
	private:
		struct GlobalResourceMappingPrivate* _members = nullptr;
	};


}