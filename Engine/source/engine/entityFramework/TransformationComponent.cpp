#include <stdafx.h>
#include <engine/entityFramework/TransformationComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/GlobalResourceMapping.h>
#include <engine/render/RenderContext.h>

#include <engine/video/GlobalShaderResource.h>
#include <engine/video/GlobalShaderResourceStorage.h>
namespace
{
	struct DirtyFlag
	{
		enum 
		{
			LocalTransformation,
			InvLocalTransformation,
			WorldTransformation,
			InvWorldTransformation,
			WorldPosition,
			WorldRotation,
			Num
		};
	};
	struct TransformationCache
	{
		engine::vec3 worldPosition;
		engine::quat worldRotation;
		engine::mat4 localTransformation;
		engine::mat4 worldTransformation;
		engine::mat4 invWorldTransformation;
		engine::mat4 invLocalTransformation;
		std::array<bool, DirtyFlag::Num> dirtyFlags;

		TransformationCache()
		{
			dirtyFlags.fill(true);
		}
	};
}

namespace engine
{

	//////////////////////////////////////////////////////////////////////////////
	class TransformationComponentAttachment
		: private NonCopyable
	{
	public:
		TransformationComponentAttachment(TransformationComponent* parent, TransformationComponent* child);
		TransformationComponentAttachment() = default;
		TransformationComponentAttachment(TransformationComponentAttachment&&);
		~TransformationComponentAttachment();

		TransformationComponentAttachment& operator=(TransformationComponentAttachment&&o);
		void reset();
		void detach();

		TransformationComponent* getChild() const;
	private:
		TransformationComponent* _parent = nullptr;
		TransformationComponent* _child = nullptr;
	};

	TransformationComponentAttachment::TransformationComponentAttachment(TransformationComponent* parent, TransformationComponent* child)
		: _parent(parent)
		, _child(child)
	{
		_parent->accessChildren().push_back(child);
		if(_child->hasParentComponent())
		{
			_child->getParentComponent()->detachComponent(_child);
		}
		_child->setParent(_parent);
		_child->onParentTransformationChanged();
	}

	TransformationComponentAttachment::TransformationComponentAttachment(TransformationComponentAttachment&& o)
		: _child(o._child)
		, _parent(o._parent)
	{
		o._child = nullptr;
		o._parent = nullptr;
	}

	TransformationComponentAttachment::~TransformationComponentAttachment()
	{
		detach();
	}

	void TransformationComponentAttachment::detach()
	{
		if(_parent && _child)
		{
			std::vector<TransformationComponent*>& children = _parent->accessChildren();
			auto it = std::remove(children.begin(),
								  children.end(),
								  _child);
			ASSERT(it != children.end());
			children.erase(it, children.end());
			_child->setParent(nullptr);
			_child->onParentTransformationChanged();
			_parent = nullptr;
			_child = nullptr;
		}
	}

	TransformationComponentAttachment& TransformationComponentAttachment::operator=(TransformationComponentAttachment&& o)
	{
		detach();
		_child = o._child;
		_parent = o._parent;
		o._child = nullptr;
		o._parent = nullptr;
	}

	void TransformationComponentAttachment::reset()
	{
		_parent = nullptr;
		_child = nullptr;
	}

	TransformationComponent* TransformationComponentAttachment::getChild() const
	{
		return _child;
	}

	//////////////////////////////////////////////////////////////////////////////
	struct TransformationComponentPrivate
	{
		vec3 localPosition;
		quat localRotation;
		mutable TransformationCache cache;
		std::vector<TransformationComponentAttachment> attachments;
		std::vector<TransformationComponent*> children;
		TransformationComponent* parent = nullptr;
	};

	TransformationComponent::TransformationComponent()
		: _members(new TransformationComponentPrivate())
	{

	}

	TransformationComponent::~TransformationComponent()
	{
		if(hasParentComponent())
		{
			getParentComponent()->detachComponent(this);
		}
		delete _members;
		_members = nullptr;
	}


	TransformationComponent* TransformationComponent::getParentComponent() const
	{
		return _members->parent;
	}

	bool TransformationComponent::hasParentComponent() const
	{
		return _members->parent != nullptr;
	}

	const std::vector<TransformationComponent*>& TransformationComponent::getChildrenComponent() const
	{
		return _members->children;
	}

	void TransformationComponent::attachComponent(TransformationComponent* component)
	{
		_members->attachments.push_back(TransformationComponentAttachment(this, component));
	}

	void TransformationComponent::detachComponent(TransformationComponent* component)
	{
		auto it = std::remove_if(_members->attachments.begin(),
								 _members->attachments.end(),
								 [component](const TransformationComponentAttachment& a)->bool
		{
			return a.getChild() == component;
		});
		_members->attachments.erase(it, _members->attachments.end());
	}

	const vec3& TransformationComponent::getWorldPosition() const
	{
		recalculateWorldPosition();
		return _members->cache.worldPosition;
	}

	void TransformationComponent::setWorldPosition(const vec3& position)
	{
		recalclateInvWorldTransformation();
		const vec3 newLocal = _members->cache.invWorldTransformation * vec4(position, 1.0f);
		setLocalPosition(newLocal);

		_members->cache.worldPosition = position;
		_members->cache.dirtyFlags[DirtyFlag::WorldPosition] = false;
	}

	const quat& TransformationComponent::getWorldRotation() const
	{
		recalculateWorldRotation();
		return _members->cache.worldRotation;
	}

	void TransformationComponent::setWorldRotation(const quat& rotation)
	{
		recalclateInvWorldTransformation();
		glm::quat invRotation = glm::quat_cast(_members->cache.invWorldTransformation);
		glm::quat newLocal = invRotation * rotation;
		setLocalRotation(rotation);

		_members->cache.worldRotation = rotation;
		_members->cache.dirtyFlags[DirtyFlag::WorldRotation] = false;
	}

	const mat4& TransformationComponent::getWorldTransformation() const
	{
		recalclateWorldTransformation();
		return _members->cache.worldTransformation;
	}

	const mat4& TransformationComponent::getInvWorldTransformation() const
	{
		recalclateInvWorldTransformation();
		return _members->cache.invWorldTransformation;
	}

	const vec3& TransformationComponent::getLocalPosition() const
	{
		return _members->localPosition;
	}

	const quat& TransformationComponent::getLocalRotation() const
	{
		return _members->localRotation;
	}

	const mat4& TransformationComponent::getLocalTransformation() const
	{
		recalclateLocalTransformation();
		return _members->cache.localTransformation;
	}

	const mat4& TransformationComponent::getInvLocalTransformation() const
	{
		recalclateInvLocalTransformation();
		return _members->cache.invLocalTransformation;
	}

	void TransformationComponent::setLocalPosition(const glm::vec3& position)
	{
		if(glm::all(glm::epsilonNotEqual(position, _members->localPosition, glm::epsilon<float>())))
		{
			_members->localPosition = position;
			_members->cache.dirtyFlags[DirtyFlag::InvLocalTransformation] = true;
			_members->cache.dirtyFlags[DirtyFlag::InvWorldTransformation] = true;
			_members->cache.dirtyFlags[DirtyFlag::LocalTransformation] = true;
			_members->cache.dirtyFlags[DirtyFlag::WorldPosition] = true;
			_members->cache.dirtyFlags[DirtyFlag::WorldTransformation] = true;
			onTransformationChanged();
		}
	}

	void TransformationComponent::setLocalRotation(const glm::quat& rotation)
	{
		if(glm::all(glm::epsilonNotEqual(rotation, _members->localRotation, glm::epsilon<float>())))
		{
			_members->localRotation = rotation;
			_members->cache.dirtyFlags[DirtyFlag::InvLocalTransformation] = true;
			_members->cache.dirtyFlags[DirtyFlag::InvWorldTransformation] = true;
			_members->cache.dirtyFlags[DirtyFlag::LocalTransformation] = true;
			_members->cache.dirtyFlags[DirtyFlag::WorldRotation] = true;
			_members->cache.dirtyFlags[DirtyFlag::WorldTransformation] = true;
			onTransformationChanged();
		}
	}

	void TransformationComponent::recalclateLocalTransformation() const
	{
		if(_members->cache.dirtyFlags[DirtyFlag::LocalTransformation])
		{
			_members->cache.localTransformation = glm::translate(_members->localPosition);
			_members->cache.localTransformation *= (mat4)_members->localRotation;
		}
	}

	void TransformationComponent::recalclateInvLocalTransformation() const
	{
		if(_members->cache.dirtyFlags[DirtyFlag::InvLocalTransformation])
		{
			recalclateLocalTransformation();
			_members->cache.invLocalTransformation = glm::inverse(_members->cache.localTransformation);
			_members->cache.dirtyFlags[DirtyFlag::InvLocalTransformation] = false;
		}
	}

	void TransformationComponent::recalclateWorldTransformation() const
	{
		if(_members->cache.dirtyFlags[DirtyFlag::WorldTransformation])
		{
			recalclateLocalTransformation();
			if(hasParentComponent())
			{
				//!! Recursion code here. getWorldTransformation calls recalculateWorldTransformation
				_members->cache.worldTransformation = getParentComponent()->getWorldTransformation();
			}
			else
			{
				_members->cache.worldTransformation = mat4();
			}
			_members->cache.worldTransformation *= _members->cache.localTransformation;
			_members->cache.dirtyFlags[DirtyFlag::WorldTransformation] = false;
		}
	}

	void TransformationComponent::recalclateInvWorldTransformation() const
	{
		if(_members->cache.dirtyFlags[DirtyFlag::InvWorldTransformation])
		{
			recalclateWorldTransformation();
			_members->cache.invWorldTransformation = glm::inverse(_members->cache.worldTransformation);
			_members->cache.dirtyFlags[DirtyFlag::InvWorldTransformation] = false;
		}
	}

	void TransformationComponent::recalculateWorldRotation() const
	{
		if(_members->cache.dirtyFlags[DirtyFlag::WorldRotation])
		{
			if(hasParentComponent())
			{
				//!! Recursion code here. getWorldRotation calls recalculateWorldRotation
				_members->cache.worldRotation = getParentComponent()->getWorldRotation();
			}
			else
			{
				_members->cache.worldRotation = quat();
			}
			_members->cache.worldRotation *= _members->localRotation;
			_members->cache.dirtyFlags[DirtyFlag::WorldRotation] = false;
		}
	}

	void TransformationComponent::recalculateWorldPosition() const
	{
		if(_members->cache.dirtyFlags[DirtyFlag::WorldPosition])
		{
			recalclateWorldTransformation();
			_members->cache.worldPosition = _members->cache.worldTransformation * vec4(_members->localPosition, 1.0);
			_members->cache.dirtyFlags[DirtyFlag::WorldPosition] = false;
		}
	}

	void TransformationComponent::onTransformationChanged()
	{
		transformationChanged.emit();
		for(TransformationComponent* child : _members->children)
		{
			child->onParentTransformationChanged();
		}
	}

	void TransformationComponent::onParentTransformationChanged()
	{
		_members->cache.dirtyFlags[DirtyFlag::WorldTransformation] = true;
		_members->cache.dirtyFlags[DirtyFlag::InvWorldTransformation] = true;
		_members->cache.dirtyFlags[DirtyFlag::WorldPosition] = true;
		_members->cache.dirtyFlags[DirtyFlag::WorldRotation] = true;
		onTransformationChanged();
	}


	std::vector<TransformationComponent*>& TransformationComponent::accessChildren()
	{
		return _members->children;
	}

	void TransformationComponent::setParent(TransformationComponent* parent)
	{
		ASSERT(hasParentComponent() == false);
		if(parent)
		{
			_members->parent = parent;
		}
	}

	void TransformationComponent::onUpdateComponent()
	{
	}


	void TransformationComponent::onRenderComponent(RenderContext* renderContext)
	{
		const std::string& worldResName = renderContext->getResourceMapping()[GlobalResource::WorldMatrix];
		GlobalShaderResource<GPUMemberType::Mat4>* worldResource = renderContext->getGlobalResources()->findMat4Resource(worldResName);
		if(worldResource && worldResource->hasAttachement())
		{
			recalclateWorldTransformation();
			worldResource->setValue(_members->cache.worldTransformation);
		}
		
		const std::string& invWorldResName = renderContext->getResourceMapping()[GlobalResource::InvWorldMatrix];
		GlobalShaderResource<GPUMemberType::Mat4>* invWorldResource = renderContext->getGlobalResources()->findMat4Resource(worldResName);
		if(invWorldResource && invWorldResource->hasAttachement())
		{
			recalclateInvWorldTransformation();
			invWorldResource->setValue(_members->cache.invWorldTransformation);
		}
	}

	std::unique_ptr<Component> TransformationComponent::cloneComponent() const
	{
		std::unique_ptr<TransformationComponent> result(new TransformationComponent());

		result->setLocalPosition(getLocalPosition());
		result->setLocalRotation(getLocalRotation());
		if(hasParentComponent())
		{
			getParentComponent()->attachComponent(result.get());
		}
		return common::static_unique_ptr_cast<Component>(std::move(result));
	}

}