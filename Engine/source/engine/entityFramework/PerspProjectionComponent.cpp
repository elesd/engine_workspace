#include <stdafx.h>
#include <engine/entityFramework/PerspProjectionComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/view/Window.h>

namespace engine
{
	struct PerspProjectionComponentPrivate
	{
		explicit PerspProjectionComponentPrivate(float fov)
			: fov(fov)
		{ }

		float fov;
	};

	PerspProjectionComponent::PerspProjectionComponent(Window* window, const PerspectiveProjectionSettings& settings)
		: ProjectionComponent(window, settings.nearPlane, settings.farPlane)
		, _members(new PerspProjectionComponentPrivate(settings.fov))
	{

	}

	PerspProjectionComponent::~PerspProjectionComponent()
	{
		delete _members;
		_members = nullptr;
	}

	float PerspProjectionComponent::getFov() const
	{
		return _members->fov;
	}

	void PerspProjectionComponent::setFov(float v)
	{
		_members->fov = v;
		setProjectionMatrixDirty();
	}

	mat4 PerspProjectionComponent::buildProjectionMatrix() const
	{
		mat4 proj = glm::perspectiveFov(_members->fov,
										float(getWindow()->getWidth()),
										float(getWindow()->getHeight()),
										getNearPlane(),
										getFarPlane());
		return proj;
	}

	std::unique_ptr<Component> PerspProjectionComponent::cloneProjectionComponent() const
	{
		PerspectiveProjectionSettings settings(getFov(), getNearPlane(), getFarPlane());
		std::unique_ptr<Component> result(new PerspProjectionComponent(getWindow(), settings));
		return result;
	}
}