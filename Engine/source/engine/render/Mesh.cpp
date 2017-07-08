#include <stdafx.h>
#include <engine/render/Mesh.h>

#include <engine/video/Material.h>
#include <engine/render/RenderContext.h>


#include <engine/video/IndexBufferBase.h>
#include <engine/video/VertexBuffer.h>

namespace engine
{
	struct MeshPrivate
	{
		std::unique_ptr<VertexBuffer> verticies;
		std::unique_ptr<IndexBufferBase> indicies;
		std::unique_ptr<Material> material;
		std::string name;
		explicit MeshPrivate(const std::string& name)
			: name(name)
		{ }
	};

	Mesh::Mesh(const std::string& name)
		: _members(new MeshPrivate(name))
	{

	}
	Mesh::Mesh(Mesh&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	Mesh::~Mesh() 
	{
		delete _members;
		_members = nullptr;
	}

	Mesh& Mesh::operator=(Mesh&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	void Mesh::load(std::unique_ptr<VertexBuffer>&& verticies, // TODO create Mesh library
					std::unique_ptr<IndexBufferBase>&& indexBuffer,
					std::unique_ptr<Material>&& material)
	{
		_members->verticies = std::move(verticies);
		_members->indicies = std::move(indexBuffer);
		_members->material = std::move(material);
	}

	void Mesh::render(RenderContext* renderContext) 
	{
		renderContext->setMaterial(_members->material.get());
		renderContext->draw(_members->verticies.get(), _members->indicies.get());
	}

	const VertexBuffer* Mesh::getVerticies() const
	{
		return _members->verticies.get();
	}

	const IndexBufferBase* Mesh::getIndicies() const
	{
		return _members->indicies.get();
	}

	const Material* Mesh::getMaterial() const
	{
		return _members->material.get();
	}
}
