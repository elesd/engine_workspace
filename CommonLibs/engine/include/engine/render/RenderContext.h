#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/video/Driver.h>

namespace engine
{
	class Render;
	class RenderTarget;
	class Material;
	class Driver;
	struct DriverInitParameters;
	class Window;
	class VertexBuffer;
	class IndexBuffer;
	class PipelineRendererBase;
	struct RenderContextParameters
	{
		DriverInitParameters driverParameters;
	};

	class RenderContext final
		: private NonCopyable
		, private NonMoveable
	{
		friend class Driver;
	public:
		RenderContext(std::unique_ptr<Driver>&& driver);
		~RenderContext();

		void init(const RenderContextParameters& params, Window *window);

		Render* createRender(const std::string& id, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer);
		bool removeRender(const std::string& id);
		Render* findRender(const std::string& id) const;
		bool hasRender(const std::string& id) const;

		void draw(const VertexBuffer* verticies, const IndexBuffer* indicies);
		void setViewPort(int32_t topX, int32_t topY, int32_t width, int32_t height);

		RenderTarget* getCurrentRenderTarget();
		Material* getCurrentMaterial();
	private:
		void setCurrentRenderTarget(RenderTarget* renderTarget);
		void setCurrentMaterial(Material* material);
	private:
		struct RenderContextPrivate* _members = nullptr;
	};
}