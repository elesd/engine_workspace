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

		RenderTarget* getCurrentRenderTarget();
		Material* getCurrentMaterial();
	private:
		void setCurrentRenderTarget(RenderTarget* renderTarget);
		void setCurrentMaterial(Material* material);
	private:
		struct RenderContextPrivate* _members = nullptr;
	};
}