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
	public:
		Mesh(const std::string& name);
		Mesh(Mesh&&);

		~Mesh() override;

		Mesh &operator=(Mesh&&);

		void load(std::unique_ptr<GeometryInstance>&& bufferContext,
				  std::unique_ptr<MaterialInstance>&& material); // TODO Move material to material library

		void render(RenderContext*) override;

		const GeometryInstance* getGeometry() const;
		const MaterialInstance* getMaterial() const;
		MaterialInstance* getMaterial();
	private:
		struct MeshPrivate* _members = nullptr;
	};
}