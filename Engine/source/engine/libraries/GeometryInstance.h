#pragma once 

#include <engine/constraints/NonMoveable.h>
#include <engine/constraints/NonCopyable.h>

#include <engine/utils/GuardedObject.h>

namespace engine
{
	class Geometry;
	class IndexBufferBase;
	class VertexBuffer;

	class GeometryInstance
		: private NonCopyable
		, private NonMoveable
	{
		friend class Driver;
	public:
		explicit GeometryInstance(std::shared_ptr<Geometry> origin);
		~GeometryInstance();
		bool hasIndexBuffer() const;
		bool hasVertexBuffer() const;
		bool allBuffersBound() const;
		const IndexBufferBase* getIndexBuffer() const;
		const VertexBuffer* getVertexBuffer() const;

		std::unique_ptr<GeometryInstance> clone() const;
	private:
		GuardedObject<const Geometry*> lockGeometry() const;
		GuardedObject<Geometry*> lockGeometry();
	private:
		struct GeometryInstancePrivate* _members = nullptr;
	};
}