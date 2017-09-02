#include <stdafx.h>
#include <engine/entityFramework/ProjectionComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/RenderContext.h>
#include <engine/render/GlobalResourceMapping.h>

#include <engine/view/Window.h>

#include <engine/video/DriverFeatures.h>
#include <engine/video/GlobalShaderResourceStorage.h>
#include <engine/utils/ViewportCalculator.h>

#include <engine/Context.h>
#include <engine/view/Console.h>

namespace
{
	struct DirtyFlags
	{
		enum
		{
			ProjectionMatrix,
			InvProjectionMatrix,
			Num
		};
	};
	struct ProjectionComponentCache
	{
		glm::mat4 projectionMatrix;
		glm::mat4 invProjectionMatrix;
		std::array<bool, DirtyFlags::Num> dirtyFlags;
		ProjectionComponentCache()
		{
			dirtyFlags.fill(true);
		}

	};


}

namespace engine
{
	struct ProjectionComponentPrivate
	{
		Window* window = nullptr;
		ProjectionComponentCache cache;
		float nearPlane = 0.0f;
		float farPlane = 0.0f;

		ProjectionComponentPrivate(Window* window, float nearPlane, float farPlane)
			: window(window)
			, nearPlane(nearPlane)
			, farPlane(farPlane)
		{
		}
	};

	ProjectionComponent::ProjectionComponent(Window* window, float nearPlane, float farPlane)
		: _members(new ProjectionComponentPrivate(window, nearPlane, farPlane))
	{

	}

	ProjectionComponent::~ProjectionComponent()
	{
		delete _members;
		_members = nullptr;
	}


	void ProjectionComponent::setNearPlane(float v)
	{
		if(glm::epsilonNotEqual(v, _members->nearPlane, glm::epsilon<float>()))
		{
			_members->nearPlane = v;
			setProjectionMatrixDirty();
		}
	}

	void ProjectionComponent::setFarPlane(float v)
	{
		if(glm::epsilonNotEqual(v, _members->farPlane, glm::epsilon<float>()))
		{
			_members->farPlane = v;
			setProjectionMatrixDirty();
		}
	}

	glm::mat4 ProjectionComponent::getProjectionMatrix() const
	{
		recalculateProjectionMatrix();
		return _members->cache.projectionMatrix;
	}

	glm::mat4 ProjectionComponent::getInvProjectionMatrix() const
	{
		recalculateInvProjectionMatrix();
		return _members->cache.invProjectionMatrix;
	}

	void ProjectionComponent::recalculateProjectionMatrix() const
	{
		if(_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix])
		{
			_members->cache.projectionMatrix = buildProjectionMatrix();
			_members->cache.projectionMatrix = ViewportCalculator<CurrentDriverFeatures::ndcType>::adaptPorjectionMatrix(_members->cache.projectionMatrix);
			_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix] = false;
		}
	}

	void ProjectionComponent::recalculateInvProjectionMatrix() const
	{
		if(_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix])
		{
			recalculateProjectionMatrix();
			_members->cache.invProjectionMatrix = glm::inverse(_members->cache.projectionMatrix);
			_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix] = false;
		}
	}

	void ProjectionComponent::setProjectionMatrixDirty()
	{
		_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix] = true;
		_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix] = true;
		projectionChanged.emit();
	}

	Window* ProjectionComponent::getWindow() const
	{
		return _members->window;
	}

	float ProjectionComponent::getNearPlane() const
	{
		return _members->nearPlane;
	}

	float ProjectionComponent::getFarPlane() const
	{
		return _members->farPlane;
	}

	vec3 ProjectionComponent::screenPointToViewport(const ScreenSpacePosition& screenPosition, float depth) const
	{
		recalculateInvProjectionMatrix();
		const glm::vec3 dimension(_members->window->getWidth(),
								  _members->window->getHeight(),
								  getFarPlane() - getNearPlane());
		// screen position to [0,1]
		glm::vec3 viewportPosition = vec3(screenPosition, depth) / dimension;
		viewportPosition = ViewportCalculator<CurrentDriverFeatures::ndcType>::normalScreenVectorToNDC(viewportPosition);
		return viewportPosition;
	}

	ScreenSpacePosition ProjectionComponent::viewportToScreenPoint(const vec3& viewportPosition) const
	{
		glm::vec3 screenSpacePosition3D = ViewportCalculator<CurrentDriverFeatures::ndcType>::ndcToNormalScreenVector(viewportPosition);
		const glm::vec3 dimension(_members->window->getWidth(),
								  _members->window->getHeight(),
								  getFarPlane() - getNearPlane());
		screenSpacePosition3D *= dimension;
		return screenSpacePosition3D;
	}

	void ProjectionComponent::onRenderComponent(RenderContext* renderContext)
	{
		const std::string& projectionName = renderContext->getResourceMapping()[GlobalResource::ProjectionMatrix];
		GlobalShaderResource<GPUMemberType::Mat4>* projParameter = renderContext->getGlobalResources()->findMat4Resource(projectionName);
		if(projParameter)
		{
			recalculateProjectionMatrix();
			projParameter->setValue(_members->cache.projectionMatrix);
		}

		const std::string& invProjectionName = renderContext->getResourceMapping()[GlobalResource::InvProjectionMatrix];
		GlobalShaderResource<GPUMemberType::Mat4>* invProjParameter = renderContext->getGlobalResources()->findMat4Resource(invProjectionName);
		if(invProjParameter)
		{
			recalculateInvProjectionMatrix();
			invProjParameter->setValue(_members->cache.invProjectionMatrix);
		}
	}

	void ProjectionComponent::onUpdateComponent()
	{

	}

	std::unique_ptr<Component> ProjectionComponent::cloneComponent() const
	{
		std::unique_ptr<Component> result = cloneProjectionComponent();
		ProjectionComponent* tmp = static_cast<ProjectionComponent*>(result.get());
		tmp->setFarPlane(getFarPlane());
		tmp->setNearPlane(getNearPlane());
		return result;
	}

}
