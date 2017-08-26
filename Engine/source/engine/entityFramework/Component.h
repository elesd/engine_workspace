#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>


namespace engine
{
	class RenderContext;

	class Component
		: private NonCopyable
		, private NonMoveable
	{
	protected:
		Component();
	public:
		virtual ~Component();

		uint32_t getTag() const;
		void onRender(RenderContext*);
		void onUpdate();

		std::unique_ptr<Component> clone() const;
	protected:
		void setTag(uint32_t tag);
	private:
		virtual void onRenderComponent(RenderContext*) = 0;
		virtual void onUpdateComponent() = 0;
		virtual std::unique_ptr<Component> cloneComponent() const = 0;
	private:
		struct ComponentPrivate* _members = nullptr;
	};
}