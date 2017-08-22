#include <stdafx.h>
#include <engine/render/Mesh.h>

#include <engine/video/Material.h>
#include <engine/render/RenderContext.h>

#include <engine/video/BufferContext.h>
#include <engine/video/IndexBufferBase.h>
#include <engine/video/VertexBuffer.h>

namespace engine
{
	struct MeshPrivate
	{
		std::unique_ptr<BufferContext> bufferContext;
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

	void Mesh::load(std::unique_ptr<BufferContext>&& bufferContext,
					std::unique_ptr<Material>&& material)
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

	const BufferContext* Mesh::getBufferContext() const
	{
		return _members->bufferContext.get();
	}

	const Material* Mesh::getMaterial() const
	{
		return _members->material.get();
	}

	Material* Mesh::getMaterial() 
	{
		return _members->material.get();
	}

}
