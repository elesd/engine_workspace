#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class CameraComponent;
	class Driver;
	class PipelineRendererBase;
	class RenderContext;

	class Renderer 
		: private NonCopyable
		, private NonMoveable
	{
	public:
		Renderer(RenderContext* renderContext, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer);
		virtual ~Renderer();

		void render();

		void addCamera(CameraComponent* camera);

		template<class PIPELINE_RENDERER>
		PIPELINE_RENDERER* getPipeline() const;
		// TODO:
		// SetViewPort
		// SetRenderTarget
		CameraComponent* findActiveCamera() const;
	private:
		PipelineRendererBase* getPipelineImpl() const;
	private:
		struct RenderPrivate* _members = nullptr;
	};

	template<class PIPELINE_RENDERER>
	PIPELINE_RENDERER* Renderer::getPipeline() const
	{
		return static_cast<PIPELINE_RENDERER*>(getPipelineImpl());
	}
}