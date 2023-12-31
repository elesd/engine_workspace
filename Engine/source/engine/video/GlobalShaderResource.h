#pragma once

#include <engine/video/ShaderResource.h>
#include <engine/video/GPUTypes.h>
#include <engine/video/ShaderResourceDescription.h>

namespace engine
{
	template<GPUMemberType Type>
	class GlobalShaderResource
	{
	public:
		explicit GlobalShaderResource(const ShaderResourceDescription& name);
		~GlobalShaderResource() {};

		void attachResource(ShaderResource<Type> *resource);
		void detachResource(ShaderResource<Type> *resource);
		bool hasAttachement() const;

		void setValue(const typename GPUMemberTypeTraits<Type>::ValueType&);
		const typename GPUMemberTypeTraits<Type>::ValueType& getValue() const;

		const std::string& getName() const;
		const ShaderResourceDescription& getDescription() const;

		void cleanUpDirtyFlag() const;
		bool isDirty() const;
	private:
		typename GPUMemberTypeTraits<Type>::ValueType _value;
		std::vector<ShaderResource<Type>*> _attachedResources;
		ShaderResourceDescription _description;
		mutable bool _dirty = false;
	};
}

#include <engine/video/GlobalShaderResource.hpp>