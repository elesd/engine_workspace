#include <stdafx.h>
#include <engine/render/Render.h>
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

	Render::Render(RenderContext* renderContext, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
		: _members(new RenderPrivate(renderContext, std::move(pipelineRenderer)))
	{

	}

	Render::~Render()
	{
		delete _members;
		_members = nullptr;
	}

	void Render::render()
	{
		CameraComponent* activeCamera = findActiveCamera();
		if(activeCamera != nullptr)
		{
			activeCamera->onRender();
		}
		_members->pipelineRender->render();
	}

	void Render::addCamera(CameraComponent* camera)
	{
		_members->cameraComponents.push_back(camera);
	}

	CameraComponent* Render::findActiveCamera() const
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

	PipelineRendererBase* Render::getPipelineImpl() const
	{
		return _members->pipelineRender.get();
	}
}