#include <stdafx.h>
#include <engine/render/Mesh.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/MaterialInstance.h>

#include <engine/render/RenderContext.h>

#include <engine/video/Geometry.h>
#include <engine/video/IndexBufferBase.h>
#include <engine/video/VertexBuffer.h>

namespace engine
{
	struct MeshPrivate
	{
		std::unique_ptr<Geometry> bufferContext;
		std::unique_ptr<MaterialInstance> material;
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

	void Mesh::load(std::unique_ptr<Geometry>&& bufferContext,
					std::unique_ptr<MaterialInstance>&& material)
	{
		_members->bufferContext = std::move(bufferContext);
		_members->material = std::move(material);
	}

	void Mesh::render(RenderContext* renderContext) 
	{
		_members->bufferContext->bindBuffers();
		renderContext->setMaterial(_members->material.get());
		renderContext->draw(_members->bufferContext.get());
	}

	const Geometry* Mesh::getGeometry() const
	{
		return _members->bufferContext.get();
	}

	const MaterialInstance* Mesh::getMaterial() const
	{
		return _members->material.get();
	}

	MaterialInstance* Mesh::getMaterial()
	{
		return _members->material.get();
	}

}
