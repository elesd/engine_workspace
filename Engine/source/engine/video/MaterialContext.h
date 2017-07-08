#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Material;
	class MaterialContext
		: private NonCopyable
		, private NonMoveable
	{
	public:
		explicit MaterialContext(const Material* material);
		virtual ~MaterialContext();

		const Material* getMaterial() const;
	private:
		struct MaterialContextPrivate* _members = nullptr;
	};
}