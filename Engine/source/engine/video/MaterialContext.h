#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Driver;
	class Material;
	class MaterialContext
		: private NonCopyable
		, private NonMoveable
	{
	public:
		explicit MaterialContext(const Material* material, Driver* driver);
		virtual ~MaterialContext();

		const Material* getMaterial() const;
		void bind() const;
		void unbind() const;
	private:
		struct MaterialContextPrivate* _members = nullptr;
	};
}