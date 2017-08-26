#include <stdafx.h>
#include <engine/entityFramework/TransformationComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/GlobalResourceMapping.h>
#include <engine/render/RenderContext.h>

#include <engine/video/GlobalShaderResourceStorage.h>
namespace
{
	struct DirtyFlag
	{
		enum 
		{
			Position,
			Rotation,
			Num
		};
	};
	struct TransformationCache
	{
		mat4 transformation;
		std::array<bool, DirtyFlag::Num> dirtyFlags;
	};
}

namespace engine
{
	struct TransformationComponentPrivate
	{
		vec3 position;
		quat rotation;
		mutable TransformationCache cache;
	};

	TransformationComponent::TransformationComponent()
		: _members(new TransformationComponentPrivate())
	{

	}

	TransformationComponent::~TransformationComponent()
	{
		delete _members;
		_members = nullptr;
	}

	const vec3& TransformationComponent::getPosition() const
	{
		return _members->position;
	}

	const quat& TransformationComponent::getRotation() const
	{
		return _members->rotation;
	}

	const mat4& TransformationComponent::getTransformation() const
	{
		recalclateTransformation();
		return _members->cache.transformation;
	}

	void TransformationComponent::setPosition(const glm::vec3& position)
	{
		_members->position = position;
		_members->cache.dirtyFlags[DirtyFlag::Position] = true;
	}

	void TransformationComponent::setRotation(const glm::quat& rotation)
	{
		_members->rotation = rotation;
		_members->cache.dirtyFlags[DirtyFlag::Rotation] = true;
	}

	void TransformationComponent::recalclateTransformation() const
	{
		if(_members->cache.dirtyFlags[DirtyFlag::Position]
		   || _members->cache.dirtyFlags[DirtyFlag::Rotation])
		{
			_members->cache.transformation = glm::translate(_members->position);
			_members->cache.transformation *= (mat4)_members->rotation;
		}
	}

	void TransformationComponent::onRenderComponent(RenderContext* renderContext)
	{
		recalclateTransformation();
		const std::string& worldRes = renderContext->getResourceMapping()[GlobalResource::WorldMatrix];
		renderContext->getGlobalResources()->setMat4(worldRes, _members->cache.transformation);
	}

	void TransformationComponent::onUpdateComponent()
	{
	}

	std::unique_ptr<Component> TransformationComponent::cloneComponent() const
	{
		std::unique_ptr<TransformationComponent> result(new TransformationComponent());

		result->setPosition(getPosition());
		result->setRotation(getRotation());

		return common::static_unique_ptr_cast<Component>(std::move(result));
	}

}