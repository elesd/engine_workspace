#pragma once

namespace engine
{
	enum class GlobalResource
	{
		WorldMatrix,
		InvWorldMatrix,
		ViewMatrix,
		ProjectionMatrix,
		InvProjectionMatrix,
		ProjectionViewWorldMatrix,
		invProjectionViewWorldMatrix,
		CameraPosition
	};

	class GlobalResourceMapping
	{
	public:
		GlobalResourceMapping() = default;
		explicit GlobalResourceMapping(const std::map<GlobalResource, std::string>& mapping);
		~GlobalResourceMapping();
		
		GlobalResourceMapping(const GlobalResourceMapping&);
		GlobalResourceMapping(GlobalResourceMapping&&);

		GlobalResourceMapping& operator=(const GlobalResourceMapping&);
		GlobalResourceMapping& operator=(GlobalResourceMapping&&);

		const std::string& operator[](GlobalResource resource) const;
	private:
		struct GlobalResourceMappingPrivate* _members = nullptr;
	};
}