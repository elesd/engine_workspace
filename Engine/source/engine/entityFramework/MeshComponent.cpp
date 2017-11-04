#include <stdafx.h>
#include <engine/entityFramework/MeshComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/Mesh.h>
#include <engine/render/RenderContext.h>

namespace engine
{

	struct MeshComponentPrivate
	{
		std::unique_ptr<Mesh> mesh = nullptr;
		explicit MeshComponentPrivate(std::unique_ptr<Mesh>&&  mesh)
			: mesh(std::move(mesh))
		{}
	};

	MeshComponent::MeshComponent(std::unique_ptr<Mesh>&&  mesh)
		: _members(new MeshComponentPrivate(std::move(mesh)))
	{

	}

	MeshComponent::~MeshComponent()
	{
		delete _members;
		_members = nullptr;
	}

	const GeometryInstance* MeshComponent::getGeometry() const
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
		std::unique_ptr<MeshComponent> result(new MeshComponent(_members->mesh->clone()));
		return common::static_unique_ptr_cast<Component>(std::move(result));
	}
}