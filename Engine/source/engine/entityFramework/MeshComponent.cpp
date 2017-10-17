#include <stdafx.h>
#include <engine/entityFramework/MeshComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/Mesh.h>
#include <engine/render/RenderContext.h>

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

	const Geometry* MeshComponent::getGeometry() const
	{
		return _members->mesh->getGeometry();
	}

	const MaterialInstance* MeshComponent::getMaterial() const
	{
		return _members->mesh->getMaterial();
	}

	std::vector<MaterialInstance*> MeshComponent::collectMaterialsImpl() const
	{
		std::vector<MaterialInstance*> result = { _members->mesh->getMaterial() };
		return result;
	}

	void MeshComponent::onRenderVisualComponent(RenderContext* renderContext) 
	{
		renderContext->setMaterial(_members->mesh->getMaterial());
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