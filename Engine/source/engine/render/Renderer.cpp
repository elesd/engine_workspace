#include <stdafx.h>
#include <engine/render/Renderer.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/CameraComponent.h>

#include <engine/Context.h>
#include <engine/view/Console.h>

#include <engine/render/PipelineRendererBase.h>
#include <engine/render/RenderContext.h>

namespace engine
{
	struct RenderPrivate
	{
		std::unique_ptr<PipelineRendererBase> pipelineRender;
		RenderContext* renderContext = nullptr;
		std::vector<CameraComponent*> cameraComponents;
		RenderPrivate(RenderContext* renderContext, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
			: pipelineRender(std::move(pipelineRenderer))
			, renderContext(renderContext)
		{
		}
	};

	Renderer::Renderer(RenderContext* renderContext, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
		: _members(new RenderPrivate(renderContext, std::move(pipelineRenderer)))
	{

	}

	Renderer::~Renderer()
	{
		delete _members;
		_members = nullptr;
	}

	void Renderer::render()
	{
		CameraComponent* activeCamera = findActiveCamera();
		if(activeCamera != nullptr)
		{
			activeCamera->onRender(_members->renderContext);
		}
		_members->pipelineRender->render();
	}

	void Renderer::addCamera(CameraComponent* camera)
	{
		_members->cameraComponents.push_back(camera);
	}

	CameraComponent* Renderer::findActiveCamera() const
	{
		CameraComponent* activeCamera = nullptr;
		for(CameraComponent* camera : _members->cameraComponents)
		{
			if(camera->isActive())
			{
				if(activeCamera != nullptr)
				{
					Context::console()->print("WARNING More than one active camera found!");
				}
				activeCamera = camera;
			}
		}
		return activeCamera;
	}

	PipelineRendererBase* Renderer::getPipelineImpl() const
	{
		return _members->pipelineRender.get();
	}
}