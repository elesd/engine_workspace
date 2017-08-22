#include <stdafx.h>
#include <engine/entityFramework/CameraComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/RenderContext.h>

#include <engine/view/Window.h>

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
	struct CameraComponentCache
	{
		glm::mat4 projectionMatrix;
		glm::mat4 invProjectionMatrix;
		std::array<bool, DirtyFlags::Num> dirtyFlags;
	};
}

namespace engine
{
	struct CameraComponentPrivate
	{
		Window* window;
		CameraSettings settings;
		CameraComponentCache cache;

		CameraComponentPrivate(Window* window, const CameraSettings& settings)
			: window(window)
			, settings(settings)
		{}
	};

	CameraComponent::CameraComponent(Window* window, const CameraSettings& settings)
		: _members(new CameraComponentPrivate(window, settings))
	{

	}

	CameraComponent::~CameraComponent()
	{
		delete _members;
		_members = nullptr;
	}

	const CameraSettings& CameraComponent::getSettings() const
	{
		return _members->settings;
	}

	void CameraComponent::setFov(float v)
	{
		_members->settings._fov = v;
		_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix] = true;
		_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix] = true;
	}

	void CameraComponent::setNearPlane(float v)
	{
		_members->settings._nearPlane = v;
		_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix] = true;
		_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix] = true;
	}

	void CameraComponent::setFarPlane(float v)
	{
		_members->settings._farPlane = v;
		_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix] = true;
		_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix] = true;
	}

	void CameraComponent::buildOrthographic()
	{

	}

	void CameraComponent::buildPerspective()
	{

	}

	glm::mat4 CameraComponent::getProjectionMatrix() const
	{
		updateProjectionMatrix();
		return _members->cache.projectionMatrix;
	}

	glm::vec3 CameraComponent::screenPointToWorldPoint(const glm::vec3& screenPosition) const
	{
		updateInvProjectionMatrix();
		const glm::vec3 dimension(_members->window->getWidth(),
								  _members->window->getHeight(), 
								  _members->settings.getFarPlane() - _members->settings.getNearPlane());
		// screen position to [0,1]
		glm::vec3 viewportPosition = screenPosition / dimension;
		std::pair<float, float> viewportRange = _members->window->getRenderContext()->getViewportRange();

		// depend on environment it goes to [-1,1] or [0,1] range
		viewportPosition = glm::lerp(viewportPosition, glm::vec3(viewportRange.first), glm::vec3(viewportRange.second));
		glm::vec4 result = _members->cache.invProjectionMatrix * glm::vec4(viewportPosition, 1.0f);
		result /= result.w;
		return glm::vec3(result);
	}

	glm::vec3 CameraComponent::worldPointToScreenPoint(const glm::vec3& worldPosition) const
	{
		updateProjectionMatrix();
		glm::vec4 viewportPosition = _members->cache.projectionMatrix * glm::vec4(worldPosition, 1.0f);
		viewportPosition /= viewportPosition.w;
		std::pair<float, float> viewportRange = _members->window->getRenderContext()->getViewportRange();
		TODO
	}

	glm::vec3 CameraComponent::screenPointToViewport(const glm::vec3& screenPosition) const
	{

	}

	glm::vec3 CameraComponent::viewportToScreenPoint(const glm::vec3& viewportPosition) const
	{

	}

	glm::vec3 CameraComponent::viewportToWorldPoint(const glm::vec3& viewportPosition) const
	{

	}

	glm::vec3 CameraComponent::WorldPointToViewport(const glm::vec3& worldPosition) const
	{

	}

	void CameraComponent::onRenderComponent(RenderContext*)
	{

	}

	void CameraComponent::onUpdateComponent()
	{

	}

	std::unique_ptr<Component> CameraComponent::cloneComponent() const
	{

	}
}
