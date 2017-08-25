#include <stdafx.h>
#include <engine/entityFramework/ProjectionComponent.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/RenderContext.h>
#include <engine/render/GlobalResourceMapping.h>

#include <engine/view/Window.h>

#include <engine/video/GlobalShaderResourceStorage.h>
#include <engine/video/DriverFeatures.h>

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

	template<engine::NDCType Type>
	struct ViewportCalculator;

	struct ViewportCalculator<engine::NDCType::OpenGl>
	{
		static inline glm::vec3 normalScreenVectorToNDC(const glm::vec3& v)
		{
			// [0,1]^3 -> [-1,1]^3
			glm::vec3 result = v;
			result *= 2.0f;
			result -= glm::vec3(1.0f);
			return result;
		}

		static inline glm::vec3 ndcToNormalScreenVector(const glm::vec3& v)
		{
			// [-1,1]^3 -> [0,1]^3 
			glm::vec3 result = v;
			result += glm::vec3(1.0f);
			result /= 2.0f;
			return result;
		}

		static inline glm::mat4 adaptPorjectionMatrix(const glm::mat4& m)
		{
			return m;
		}
	};

	struct ViewportCalculator<engine::NDCType::DirectX>
	{
		static inline glm::vec3 normalScreenVectorToNDC(const glm::vec3& v)
		{
			return v;
		}

		static inline glm::vec3 ndcToNormalScreenVector(const glm::vec3& v)
		{
			return v;
		}

		static inline glm::mat4 adaptPorjectionMatrix(const glm::mat4& m)
		{
			// [-1,1]^3 -> [0,1]^3
			//glm::scale(glm::vec3(0.5f, 0.5f, 0.5f)) * glm::translate(glm::vec3(1.0f, 1.0f, 1.0f)) * m;
			glm::mat4 result = glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
			result *= glm::translate(glm::vec3(1.0f, 1.0f, 1.0f));
			result *= m;
			return result;
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
		{}
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
		_members->nearPlane = v;
		_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix] = true;
		_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix] = true;
	}

	void ProjectionComponent::setFarPlane(float v)
	{
		_members->farPlane = v;
		_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix] = true;
		_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix] = true;
	}

	glm::mat4 ProjectionComponent::getProjectionMatrix() const
	{
		updateProjectionMatrix();
		return _members->cache.projectionMatrix;
	}

	glm::mat4 ProjectionComponent::getInvProjectionMatrix() const
	{
		updateInvProjectionMatrix();
		return _members->cache.invProjectionMatrix;
	}

	void ProjectionComponent::updateProjectionMatrix() const
	{
		if(_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix])
		{
			_members->cache.projectionMatrix = buildProjectionMatrix();
			_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix] = false;
		}
	}

	void ProjectionComponent::updateInvProjectionMatrix() const
	{
		if(_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix])
		{
			updateProjectionMatrix();
			_members->cache.invProjectionMatrix = glm::inverse(_members->cache.projectionMatrix);
			_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix] = false;
		}
	}

	void ProjectionComponent::setProjectionMatrixDirty()
	{
		_members->cache.dirtyFlags[DirtyFlags::ProjectionMatrix] = true;
	}

	void ProjectionComponent::setInvProjectionMatrixDirty()
	{
		_members->cache.dirtyFlags[DirtyFlags::InvProjectionMatrix] = true;
	}

	float ProjectionComponent::getNearPlane() const
	{
		return _members->nearPlane;
	}

	float ProjectionComponent::getFarPlane() const
	{
		return _members->farPlane;
	}

	//glm::vec3 ProjectionComponent::screenPointToWorldPoint(const glm::vec3& screenPosition) const
	//{
	//	updateInvProjectionMatrix();
	//	const glm::vec3 dimension(_members->window->getWidth(),
	//							  _members->window->getHeight(), 
	//							  _members->settings.getFarPlane() - _members->settings.getNearPlane());
	//	// screen position to [0,1]
	//	glm::vec3 viewportPosition = screenPosition / dimension;
	//	// depend on environment it goes to [-1,1] or [0,1] range
	//	viewportPosition = ViewportCalculator<CurrentDriverFeatures::ndcType>::normalScreenVectorToNDC(viewportPosition);

	//	glm::vec4 result = _members->cache.invProjectionMatrix * glm::vec4(viewportPosition, 1.0f);
	//	result /= result.w;
	//	return glm::vec3(result);
	//}

	//glm::vec3 ProjectionComponent::worldPointToScreenPoint(const glm::vec3& worldPosition) const
	//{
	//	updateProjectionMatrix();
	//	
	//}

	//glm::vec3 ProjectionComponent::screenPointToViewport(const glm::vec3& screenPosition) const
	//{

	//}

	//glm::vec3 ProjectionComponent::viewportToScreenPoint(const glm::vec3& viewportPosition) const
	//{

	//}

	//glm::vec3 ProjectionComponent::viewportToWorldPoint(const glm::vec3& viewportPosition) const
	//{

	//}

	//glm::vec3 ProjectionComponent::WorldPointToViewport(const glm::vec3& worldPosition) const
	//{

	//}

	void ProjectionComponent::onRenderComponent(RenderContext* renderContext)
	{
		const std::string& projectionName = renderContext->getResourceMapping()[GlobalResource::ProjectionMatrix];
		GlobalShaderResource<GPUMemberType::Mat4>* projParameter = renderContext->getGlobalResources()->findMat4Resource(projectionName);
		if(projParameter->hasAttachement())
		{
			updateProjectionMatrix();
			projParameter->setValue(_members->cache.projectionMatrix);
		}

		const std::string& invProjectionName = renderContext->getResourceMapping()[GlobalResource::InvProjectionMatrix];
		GlobalShaderResource<GPUMemberType::Mat4>* invProjParameter = renderContext->getGlobalResources()->findMat4Resource(projectionName);
		if(invProjParameter->hasAttachement())
		{
			updateInvProjectionMatrix();
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
		tmp->updateInvProjectionMatrix();
		tmp->updateProjectionMatrix();
		return result;
	}
}
