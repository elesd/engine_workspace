#include <stdafx.h>
#include <engine/libraries/MeshLibrary.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/Mesh.h>

namespace engine
{
	struct MeshLibraryPrivate
	{
		// TODO replace shared_ptr
		std::map<std::string, std::unique_ptr<Mesh>> meshes;
	};

	MeshLibrary::MeshLibrary()
		: _members(new MeshLibraryPrivate())
	{

	}

	MeshLibrary::~MeshLibrary()
	{
		delete _members;
		_members = nullptr;
	}


	void MeshLibrary::addMesh(const std::string& name, std::unique_ptr<GeometryInstance>&& geometry, std::unique_ptr<MaterialInstance>&& material)
	{
		std::unique_ptr<Mesh> mesh(new Mesh(name, std::move(geometry), std::move(material)));
		_members->meshes[name] = std::move(mesh);
	}

	std::unique_ptr<Mesh> MeshLibrary::getMesh(const std::string& name) const
	{
		auto it = _members->meshes.find(name);
		ASSERT(it != _members->meshes.end());
		return it->second->clone();
	}

	bool MeshLibrary::hasMesh(const std::string& name) const
	{
		auto it = _members->meshes.find(name);
		return it != _members->meshes.end();
	}

}