#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class GeometryInstance;
	class MaterialInstance;
	class Mesh;

	class MeshLibrary final
		: private NonCopyable
		, private NonMoveable
	{
	public:
		MeshLibrary();
		~MeshLibrary();
		
		void addMesh(const std::string& name, std::unique_ptr<GeometryInstance>&& geometry, std::unique_ptr<MaterialInstance>&& material);
		std::unique_ptr<Mesh> getMesh(const std::string& name) const;
		bool hasMesh(const std::string& name) const;

	private:
		struct MeshLibraryPrivate* _members = nullptr;
	};
}