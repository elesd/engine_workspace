#pragma once

#include <engine/render/IRenderable.h>

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class BufferContext;
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

		void load(std::unique_ptr<BufferContext>&& bufferContext,
				  std::unique_ptr<Material>&& material); // TODO Move material to material library

		void render(RenderContext*) override;

		const BufferContext* getBufferContext() const;
		const Material* getMaterial() const;
		Material* getMaterial();
	private:
		struct MeshPrivate* _members = nullptr;
	};
}