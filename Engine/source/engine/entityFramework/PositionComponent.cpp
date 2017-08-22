#include <stdafx.h>
#include <engine/entityFramework/PositionComponent.h>
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
		glm::mat4 transformation;
		std::array<bool, DirtyFlag::Num> dirtyFlags;
	};
}

namespace engine
{
	struct PositionComponentPrivate
	{
		glm::vec3 position;
		glm::quat rotation;
		mutable TransformationCache cache;
	};

	PositionComponent::PositionComponent()
		: _members(new PositionComponentPrivate())
	{

	}

	PositionComponent::~PositionComponent()
	{
		delete _members;
		_members = nullptr;
	}

	const glm::vec3& PositionComponent::getPosition() const
	{
		return _members->position;
	}

	const glm::quat& PositionComponent::getRotation() const
	{
		return _members->rotation;
	}

	const glm::mat4& PositionComponent::getTransformation() const
	{
		recalclateTransformation();
		return _members->cache.transformation;
	}

	void PositionComponent::setPosition(const glm::vec3& position)
	{
		_members->position = position;
		_members->cache.dirtyFlags[DirtyFlag::Position] = true;
	}

	void PositionComponent::setRotation(const glm::quat& rotation)
	{
		_members->rotation = rotation;
		_members->cache.dirtyFlags[DirtyFlag::Rotation] = true;
	}

	void PositionComponent::recalclateTransformation() const
	{
		if(_members->cache.dirtyFlags[DirtyFlag::Position]
		   || _members->cache.dirtyFlags[DirtyFlag::Rotation])
		{
			_members->cache.transformation = glm::translate(_members->position);
			_members->cache.transformation *= (glm::mat4)_members->rotation;
		}
	}

	void PositionComponent::onRenderComponent(RenderContext* renderContext)
	{
		recalclateTransformation();
		const std::string& worldRes = renderContext->getResourceMapping()[GlobalResource::WorldMatrix];
		renderContext->getGlobalResources()->setMat4(worldRes, _members->cache.transformation);
	}

	void PositionComponent::onUpdateComponent()
	{
	}

	std::unique_ptr<Component> PositionComponent::cloneComponent() const
	{
		std::unique_ptr<PositionComponent> result(new PositionComponent());

		result->setPosition(getPosition());
		result->setRotation(getRotation());

		return common::static_unique_ptr_cast<Component>(std::move(result));
	}

}