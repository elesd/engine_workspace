#pragma once

#include <engine/entityFramework/VisualComponent.h>

namespace engine
{
	class Mesh;

	class MeshComponent
		: public VisualComponent
	{
	public:
		explicit MeshComponent(Mesh*);
		~MeshComponent() override;

		const Geometry* getGeometry() const;
		const Material* getMaterial() const;
	private:
		std::vector<Material*> collectMaterialsImpl() const override;
		void onRenderVisualComponent(RenderContext*) override;
		void onUpdateVisualComponent() override;
		std::unique_ptr<Component> cloneVisualComponent() const override;

	private:
		struct MeshComponentPrivate* _members = nullptr;
	};
}