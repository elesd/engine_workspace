#pragma once

#include <engine/render/IRenderable.h>

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class VertexBuffer;
	class IndexBufferBase;
	class Material;

	class Mesh 
		: public IRenderable
		, NonCopyable
	{
	public:
		Mesh(const std::string& name);
		Mesh(Mesh&&);

		~Mesh() override;

		Mesh &operator=(Mesh&&);

		void load(std::unique_ptr<VertexBuffer>&& verticies, // TODO create Mesh library
				  std::unique_ptr<IndexBufferBase>&& indexBuffer,
				  std::unique_ptr<Material>&& material); // TODO Move material to material library

		void render(RenderContext*) override;

		const VertexBuffer* getVerticies() const;
		const IndexBufferBase* getIndicies() const;
		const Material* getMaterial() const;
	private:
		struct MeshPrivate* _members = nullptr;
	};
}