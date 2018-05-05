#include <stdafx.h>
#include <engine/render/Mesh.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/MaterialInstance.h>
#include <engine/libraries/GeometryInstance.h>

#include <engine/render/RenderContext.h>

#include <engine/video/Geometry.h>

#include <engine/video/IndexBufferBase.h>
#include <engine/video/VertexBuffer.h>

namespace engine
{
	struct MeshPrivate
	{
		std::string name;
		std::unique_ptr<GeometryInstance> geometry;
		std::unique_ptr<MaterialInstance> material;
		explicit MeshPrivate(const std::string& name, std::unique_ptr<GeometryInstance>&& geometry, std::unique_ptr<MaterialInstance>&& material)
			: name(name)
			, geometry(std::move(geometry))
			, material(std::move(material))
		{ }
	};

	Mesh::Mesh(const std::string& name, std::unique_ptr<GeometryInstance>&& geometry, std::unique_ptr<MaterialInstance>&& material)
		: _members(new MeshPrivate(name, std::move(geometry), std::move(material)))
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
		renderContext->bindGeometryBuffers(_members->geometry.get());
		renderContext->setMaterial(_members->material.get());
		renderContext->draw(_members->geometry.get());
	}

	const GeometryInstance* Mesh::getGeometry() const
	{
		return _members->geometry.get();
	}

	const MaterialInstance* Mesh::getMaterial() const
	{
		return _members->material.get();
	}

	MaterialInstance* Mesh::getMaterial()
	{
		return _members->material.get();
	}

	std::unique_ptr<Mesh> Mesh::clone() const
	{
		std::unique_ptr<MaterialInstance> material = _members->material->clone();
		std::unique_ptr<GeometryInstance> geometry = _members->geometry->clone();
		std::unique_ptr<Mesh> result(new Mesh(_members->name, std::move(geometry), std::move(material)));
		return result;
	}

}
