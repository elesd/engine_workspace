#pragma once

#include <engine/render/IRenderable.h>

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class VertexBuffer;
	class IndexBuffer;
	class Material;

	class Mesh 
		: public IRenderable
		, NonCopyable
	{
	public:
		Mesh();
		Mesh(Mesh&&);

		~Mesh() override;

		Mesh &operator=(Mesh&&);

		void render(Driver*) override;

		const VertexBuffer* getVerticies() const;
		const IndexBuffer* getIndicies() const;
		const Material* getMaterial() const;
	private:
		struct MeshPrivate* _members = nullptr;
	};
}