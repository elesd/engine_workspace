#pragma once

#include <engine/render/IRenderable.h>

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class GeometryInstance;
	class MaterialInstance;

	class Mesh 
		: public IRenderable
		, NonCopyable
	{
		friend class MeshLibrary;
	public:
		Mesh(const std::string& name, std::unique_ptr<GeometryInstance>&& geometry, std::unique_ptr<MaterialInstance>&& material);
		Mesh(Mesh&&);

		~Mesh() override;

		Mesh &operator=(Mesh&&);

		void render(RenderContext*) override;

		const GeometryInstance* getGeometry() const;
		const MaterialInstance* getMaterial() const;
		MaterialInstance* getMaterial();

		std::unique_ptr<Mesh> clone() const;
	private:
		struct MeshPrivate* _members = nullptr;
	};
}