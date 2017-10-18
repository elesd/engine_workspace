#include <stdafx.h>
#include <engine/libraries/GeometryInstance.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Geometry.h>


namespace engine
{
	struct GeometryInstancePrivate
	{
		std::shared_ptr<Geometry> origin;
		explicit GeometryInstancePrivate(std::shared_ptr<Geometry> origin)
			: origin(origin)
		{ }
	};

	GeometryInstance::GeometryInstance(std::shared_ptr<Geometry> origin)
		: _members(new GeometryInstancePrivate(origin))
	{

	}

	GeometryInstance::~GeometryInstance()
	{
		delete _members;
		_members = nullptr;
	}

	bool GeometryInstance::hasIndexBuffer() const
	{
		return _members->origin->hasIndexBuffer();
	}

	bool GeometryInstance::hasVertexBuffer() const
	{
		return _members->origin->hasVertexBuffer();
	}

	bool GeometryInstance::allBuffersBound() const
	{
		return _members->origin->allBuffersBound();
	}

	const IndexBufferBase* GeometryInstance::getIndexBuffer() const
	{
		return _members->origin->getIndexBuffer();
	}

	const VertexBuffer* GeometryInstance::getVertexBuffer() const
	{
		return _members->origin->getVertexBuffer();
	}

	GuardedObject<const Geometry*> GeometryInstance::lockGeometry() const
	{
		return static_cast<const Geometry*>(_members->origin.get())->lock();
	}

	GuardedObject<Geometry*> GeometryInstance::lockGeometry()
	{
		return _members->origin->lock();
	}
}