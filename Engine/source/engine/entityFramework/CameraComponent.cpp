#include <stdafx.h>
#include <engine/entityFramework/CameraComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/OrthoProjectionComponent.h>
#include <engine/entityFramework/PerspProjectionComponent.h>
#include <engine/entityFramework/TransformationComponent.h>

#include <engine/render/RenderContext.h>
#include <engine/render/GlobalResourceMapping.h>

#include <engine/video/GlobalShaderResourceStorage.h>
#include <engine/video/GlobalShaderResource.h>

namespace
{

	struct DirtyFlag
	{
		enum
		{
			PVMatrix,
			InvPVMatrix,
			Num
		};
	};
}

namespace engine
{
	struct CameraComponentCache
	{
		mat4 PVMatrix;
		mat4 invPVMatrix;
		std::array<bool, DirtyFlag::Num> dirtFlags;
	};

	struct CameraComponentPrivate
	{
		std::unique_ptr<OrthoProjectionComponent> orthoComponent;
		std::unique_ptr<PerspProjectionComponent> perspComponent;
		bool isOrtho = false;
		mutable CameraComponentCache cache;
	};

	CameraComponent::CameraComponent()
		: _members(new CameraComponentPrivate())
	{
		_members->cache.dirtFlags.fill(true);
	}

	CameraComponent::CameraComponent(const vec3& worldPosition)
		: CameraComponent()
	{
		std::unique_ptr<TransformationComponent> position(new TransformationComponent());
		position->setLocalPosition(worldPosition);
		setTransformationComponent(std::move(position));
	}

	CameraComponent::CameraComponent(Window* window, const PerspectiveProjectionSettings& settings, const vec3& worldPosition)
		: CameraComponent(worldPosition)
	{
		std::unique_ptr<PerspProjectionComponent> perspectiveProj(new PerspProjectionComponent(window, settings));
		setPerspectiveProjection(std::move(perspectiveProj));
		forceActivatePerspectiveProjection();
	}

	CameraComponent::CameraComponent(Window* window, const OrthogonalProjectionSettings& settings, const vec3& worldPosition)
		: CameraComponent(worldPosition)
	{
		std::unique_ptr<OrthoProjectionComponent> orthographicProj(new OrthoProjectionComponent(window, settings));
		setOrthogonalProjection(std::move(orthographicProj));
		forceActivateOrthogonalProjection();
	}

	CameraComponent::CameraComponent(Window* window, const OrthogonalProjectionSettings& orthoSettings, const PerspectiveProjectionSettings& perspSettings, const vec3& worldPosition, bool isOrtho)
		: CameraComponent(worldPosition)
	{
		std::unique_ptr<PerspProjectionComponent> perspectiveProj(new PerspProjectionComponent(window, perspSettings));
		setPerspectiveProjection(std::move(perspectiveProj));

		std::unique_ptr<OrthoProjectionComponent> orthographicProj(new OrthoProjectionComponent(window, orthoSettings));
		setOrthogonalProjection(std::move(orthographicProj));
		if(isOrtho)
		{
			forceActivateOrthogonalProjection();
		}
		else
		{
			forceActivatePerspectiveProjection();
		}
	}

	CameraComponent::~CameraComponent()
	{
		delete _members;
	}

	void CameraComponent::setOrthogonalProjection(std::unique_ptr<OrthoProjectionComponent>&& projection)
	{
		_members->orthoComponent = std::move(projection);
	}

	void CameraComponent::setPerspectiveProjection(std::unique_ptr<PerspProjectionComponent>&& projection)
	{
		_members->perspComponent = std::move(projection);
	}

	void CameraComponent::registerOrthogonalProjection(std::unique_ptr<OrthoProjectionComponent>&& projection)
	{
		setOrthogonalProjection(std::move(projection));
		forceActivateOrthogonalProjection();
	}

	void CameraComponent::registerPerspectiveProjection(std::unique_ptr<PerspProjectionComponent>&& projection)
	{
		setPerspectiveProjection(std::move(projection));
		forceActivatePerspectiveProjection();
	}

	void CameraComponent::activatePerspectiveProjection()
	{
		if(_members->isOrtho)
		{
			forceActivatePerspectiveProjection();
		}
	}

	void CameraComponent::activateOrthogonalProjection()
	{
		if(!_members->isOrtho)
		{
			forceActivateOrthogonalProjection();
		}
	}

	void CameraComponent::forceActivateOrthogonalProjection()
	{
		ASSERT(hasOrthogonalProjection());
		ProjectionComponent* projection = getActiveProjection();
		DISCONNECT_SIGNAL(projection, projectionChanged, this, whenProjectionChanged);
		_members->isOrtho = true;
		projection = getActiveProjection();
		CONNECT_SIGNAL(projection, projectionChanged, this, whenProjectionChanged);
		whenProjectionChanged();
	}
	void CameraComponent::forceActivatePerspectiveProjection()
	{
		ASSERT(hasPerspectiveProjection());
		ProjectionComponent* projection = getActiveProjection();
		DISCONNECT_SIGNAL(projection, projectionChanged, this, whenProjectionChanged);
		_members->isOrtho = false;
		projection = getActiveProjection();
		CONNECT_SIGNAL(projection, projectionChanged, this, whenProjectionChanged);
		whenProjectionChanged();
	}

	const OrthoProjectionComponent* CameraComponent::getOrthogonalProjection() const
	{
		return _members->orthoComponent.get();
	}

	OrthoProjectionComponent* CameraComponent::getOrthogonalProjection()
	{
		return _members->orthoComponent.get();
	}

	const PerspProjectionComponent* CameraComponent::getPerspectiveProjection() const
	{
		return _members->perspComponent.get();
	}

	PerspProjectionComponent* CameraComponent::getPerspectiveProjection()
	{
		return _members->perspComponent.get();
	}

	bool CameraComponent::hasOrthogonalProjection() const
	{
		return _members->orthoComponent != nullptr;
	}

	bool CameraComponent::hasPerspectiveProjection() const
	{
		return _members->perspComponent != nullptr;
	}

	bool CameraComponent::isOrthographic() const
	{
		return _members->isOrtho;
	}

	vec3 CameraComponent::screenPointToWorldPoint(const ScreenSpacePosition& screenPosition, float depth) const
	{
		const ProjectionComponent* activeProjection = getActiveProjection();
		vec3 viewportPosition = screenPointToViewport(screenPosition, depth);
		vec3 worldPosition = viewportToWorldPoint(viewportPosition);
		return worldPosition;
	}

	ScreenSpacePosition CameraComponent::worldPointToScreenPoint(const vec3& worldPosition) const
	{
		vec3 viewportPosition = WorldPointToViewport(worldPosition);
		ScreenSpacePosition result = viewportToScreenPoint(viewportPosition);
		return result;
	}

	vec3 CameraComponent::screenPointToViewport(const ScreenSpacePosition& screenPosition, float depth) const
	{
		return getActiveProjection()->screenPointToViewport(screenPosition, depth);
	}

	ScreenSpacePosition CameraComponent::viewportToScreenPoint(const vec3& viewportPosition) const
	{
		return getActiveProjection()->viewportToScreenPoint(viewportPosition);
	}

	vec3 CameraComponent::viewportToWorldPoint(const glm::vec3& viewportPosition) const
	{
		recalculateInvPVTransformation();
		vec4 worldPosition = _members->cache.invPVMatrix * vec4(viewportPosition, 1.0f);
		worldPosition /= worldPosition.w;
		return worldPosition;
	}

	vec3 CameraComponent::WorldPointToViewport(const glm::vec3& worldPosition) const
	{
		recalculatePVTransformation();
		vec4 viewportPosition = _members->cache.PVMatrix * vec4(worldPosition, 1.0f);
		viewportPosition /= viewportPosition.w;
		return viewportPosition;
	}

	void CameraComponent::recalculatePVTransformation() const
	{
		if(!isValidComponent())
			return;

		if(_members->cache.dirtFlags[DirtyFlag::PVMatrix])
		{
			_members->cache.PVMatrix = getActiveProjection()->getProjectionMatrix() * getTransformationComponent()->getInvWorldTransformation();
			_members->cache.dirtFlags[DirtyFlag::PVMatrix] = false;
		}
	}

	void CameraComponent::recalculateInvPVTransformation() const
	{
		if(!isValidComponent())
			return;

		if(_members->cache.dirtFlags[DirtyFlag::InvPVMatrix])
		{
			recalculatePVTransformation();
			_members->cache.invPVMatrix = glm::inverse(_members->cache.PVMatrix);
			_members->cache.dirtFlags[DirtyFlag::InvPVMatrix] = false;
		}
	}

	const ProjectionComponent* CameraComponent::getActiveProjection() const
	{
		const ProjectionComponent* currentProjection = isOrthographic()
			? static_cast<const ProjectionComponent*>(getOrthogonalProjection())
			: static_cast<const ProjectionComponent*>(getPerspectiveProjection());
		return currentProjection;
	}

	ProjectionComponent* CameraComponent::getActiveProjection() 
	{
		ProjectionComponent* currentProjection = isOrthographic()
			? static_cast<ProjectionComponent*>(getOrthogonalProjection())
			: static_cast<ProjectionComponent*>(getPerspectiveProjection());
		return currentProjection;
	}

	bool CameraComponent::isValidComponent() const
	{
		return ((isOrthographic() && hasOrthogonalProjection()) || (!isOrthographic() && hasPerspectiveProjection()));
	}

	void CameraComponent::onTransformationComponentSet()
	{
		TransformationComponent* currentComponent = getTransformationComponent();
		if(currentComponent)
		{
			CONNECT_SIGNAL(currentComponent, transformationChanged, this, whenTransformationChanged);
		}
	}

	void CameraComponent::onRenderSceneComponent(RenderContext* renderContext)
	{
		if(!isValidComponent())
			return;

		{
			const std::string& resName = renderContext->getResourceMapping()[GlobalResource::ProjectionViewMatrix];
			GlobalShaderResource<GPUMemberType::Mat4>* resource = renderContext->getGlobalResources()->findMat4Resource(resName);
			if(resource && resource->hasAttachement())
			{
				recalculateInvPVTransformation();
				resource->setValue(_members->cache.PVMatrix);
			}
		}

		{
			const std::string& resName = renderContext->getResourceMapping()[GlobalResource::InvProjectionViewMatrix];
			GlobalShaderResource<GPUMemberType::Mat4>* resource = renderContext->getGlobalResources()->findMat4Resource(resName);
			if(resource && resource->hasAttachement())
			{
				recalculateInvPVTransformation();
				resource->setValue(_members->cache.invPVMatrix);
			}
		}

		{
			const std::string& resName = renderContext->getResourceMapping()[GlobalResource::ViewMatrix];
			GlobalShaderResource<GPUMemberType::Mat4>* resource = renderContext->getGlobalResources()->findMat4Resource(resName);
			if(resource && resource->hasAttachement())
			{
				resource->setValue(getTransformationComponent()->getInvWorldTransformation());
			}
		}

		{
			const std::string& resName = renderContext->getResourceMapping()[GlobalResource::InvViewMatrix];
			GlobalShaderResource<GPUMemberType::Mat4>* resource = renderContext->getGlobalResources()->findMat4Resource(resName);
			if(resource && resource->hasAttachement())
			{
				resource->setValue(getTransformationComponent()->getWorldTransformation());
			}
		}

		{
			const std::string& resName = renderContext->getResourceMapping()[GlobalResource::CameraPosition];
			GlobalShaderResource<GPUMemberType::Vec3>* resource = renderContext->getGlobalResources()->findVec3Resource(resName);
			if(resource && resource->hasAttachement())
			{
				resource->setValue(getTransformationComponent()->getWorldPosition());
			}
		}
		getActiveProjection()->onRender(renderContext);
	}

	void CameraComponent::onUpdateSceneComponent()
	{
		getActiveProjection()->onUpdate();
	}

	std::unique_ptr<Component> CameraComponent::cloneSceneComponent() const
	{
		std::unique_ptr<Component> result(new CameraComponent());
		CameraComponent* clone = static_cast<CameraComponent*>(result.get());
		
		clone->setTransformationComponent(common::static_unique_ptr_cast<TransformationComponent>(getTransformationComponent()->clone()));
		
		if(hasOrthogonalProjection())
		{
			clone->setOrthogonalProjection(common::static_unique_ptr_cast<OrthoProjectionComponent>(getOrthogonalProjection()->clone()));
		}
		if(hasPerspectiveProjection())
		{
			clone->setPerspectiveProjection(common::static_unique_ptr_cast<PerspProjectionComponent>(getPerspectiveProjection()->clone()));
		}
		if(isOrthographic())
		{
			clone->activateOrthogonalProjection();
		}
		else
		{
			clone->activatePerspectiveProjection();
		}
		return result;
	}

	void CameraComponent::whenTransformationChanged()
	{
		_members->cache.dirtFlags[DirtyFlag::PVMatrix] = true;
		_members->cache.dirtFlags[DirtyFlag::InvPVMatrix] = true;
	}

	void CameraComponent::whenProjectionChanged()
	{
		_members->cache.dirtFlags[DirtyFlag::PVMatrix] = true;
		_members->cache.dirtFlags[DirtyFlag::InvPVMatrix] = true;
	}

}