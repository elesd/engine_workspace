#include <stdafx.h>
#include <engine/entityFramework/MeshComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/Mesh.h>

namespace engine
{

	struct MeshComponentPrivate
	{
		Mesh* mesh = nullptr;
		explicit MeshComponentPrivate(Mesh* mesh)
			: mesh(mesh)
		{}
	};

	MeshComponent::MeshComponent(Mesh* mesh)
		: _members(new MeshComponentPrivate(mesh))
	{

	}

	MeshComponent::~MeshComponent()
	{
		delete _members;
		_members = nullptr;
	}

	Mesh* MeshComponent::getMesh() const
	{
		return _members->mesh;
	}

	std::vector<Material*> MeshComponent::collectMaterialsImpl() const
	{
		std::vector<Material*> result = { _members->mesh->getMaterial() };
		return result;
	}

	void MeshComponent::onRenderVisualComponent(RenderContext* renderContext) 
	{
		_members->mesh->render(renderContext);
	}
	
	void MeshComponent::onUpdateVisualComponent()
	{
	}

	std::unique_ptr<Component> MeshComponent::cloneVisualComponent() const
	{
		std::unique_ptr<MeshComponent> result(new MeshComponent(_members->mesh));
		return common::static_unique_ptr_cast<Component>(std::move(result));
	}
}