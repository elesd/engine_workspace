#pragma once


#include <engine/video/Geometry.h>

namespace engine
{
	namespace glew
	{
		class BufferContextImpl
			: public Geometry
		{
		public:
			explicit BufferContextImpl(RenderContext* renderContext, Driver* driver);
			~BufferContextImpl() override;

		private:
			void bindBuffersImpl() override;
			void unbindBuffersImpl() override;
			bool isBound() const override;
			void setupLayout() override;
			void bind() override;
			void unbind() override;
			void finalizeImpl() override;


		private:
			struct BufferContextImplPrivate* _members = nullptr;
		};
	}
}