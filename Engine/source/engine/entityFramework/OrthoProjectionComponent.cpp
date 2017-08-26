#include <stdafx.h>
#include <engine/entityFramework/OrthoProjectionComponent.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct OrthoProjectionComponentPrivate
	{
		float left = 0.0f;
		float right = 0.0f;
		float top = 0.0f;
		float bottom = 0.0f;
		OrthoProjectionComponentPrivate(float left, float right, float top, float bottom)
			: left(left)
			, right(right)
			, top(top)
			, bottom(bottom)
		{ }
	};

	OrthoProjectionComponent::OrthoProjectionComponent(Window* window, const OrthogonalProjectionSettings& settings)
		: ProjectionComponent(window, settings.nearPlane, settings.farPlane)
		, _members(new OrthoProjectionComponentPrivate(settings.left, settings.right, settings.top, settings.bottom))
	{

	}

	OrthoProjectionComponent::~OrthoProjectionComponent()
	{
		delete _members;
		_members = nullptr;
	}

	float OrthoProjectionComponent::getLeft() const
	{
		return _members->left;
	}

	void OrthoProjectionComponent::setLeft(float v)
	{
		if(glm::epsilonNotEqual(v, _members->left, glm::epsilon<float>()))
		{
			_members->left = v;
			setProjectionMatrixDirty();
		}
	}
	
	float OrthoProjectionComponent::getRight() const
	{
		return _members->right;
	}

	void OrthoProjectionComponent::setRight(float v)
	{
		if(glm::epsilonNotEqual(v, _members->right, glm::epsilon<float>()))
		{
			_members->right = v;
			setProjectionMatrixDirty();
		}
	}

	float OrthoProjectionComponent::getTop() const
	{
		return _members->top;
	}

	void OrthoProjectionComponent::setTop(float v)
	{
		if(glm::epsilonNotEqual(v, _members->top, glm::epsilon<float>()))
		{
			_members->top = v;
			setProjectionMatrixDirty();
		}
	}

	float OrthoProjectionComponent::getBottom() const
	{
		return _members->bottom;
	}

	void OrthoProjectionComponent::setBottom(float v)
	{
		if(glm::epsilonNotEqual(v, _members->bottom, glm::epsilon<float>()))
		{
			_members->bottom = v;
			setProjectionMatrixDirty();
		}
	}

	mat4 OrthoProjectionComponent::buildProjectionMatrix() const
	{
		mat4 proj = glm::ortho(_members->left, _members->right, _members->bottom, _members->top);
		return proj;
	}

	std::unique_ptr<Component> OrthoProjectionComponent::cloneProjectionComponent() const
	{
		OrthogonalProjectionSettings settings(getLeft(),
											  getRight(),
											  getTop(), 
											  getBottom(),
											  getNearPlane(),
											  getFarPlane());
		std::unique_ptr<Component> result(new OrthoProjectionComponent(getWindow(), settings));
		return result;
	}
}