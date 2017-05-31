#include <stdafx.h>
#include <engine/render/Mesh.h>

#include <engine/render/Material.h>
#include <engine/render/RenderContext.h>


#include <engine/video/IndexBuffer.h>
#include <engine/video/VertexBuffer.h>

namespace engine
{
	struct MeshPrivate
	{
		std::unique_ptr<VertexBuffer> verticies;
		std::unique_ptr<IndexBuffer> indicies;
		Material* material;
	};

	Mesh::Mesh()
		: _members(new MeshPrivate())
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

	void Mesh::render(RenderContext* renderContext) 
	{
		renderContext->setMaterial(_members->material);
		//TODO renderContext->render(_members->verticies.get(), _members->indicies.get());
	}

	const VertexBuffer* Mesh::getVerticies() const
	{
		return _members->verticies.get();
	}

	const IndexBuffer* Mesh::getIndicies() const
	{
		return _members->indicies.get();
	}

	const Material* Mesh::getMaterial() const
	{
		return _members->material;
	}
}
