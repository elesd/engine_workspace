#pragma once

#include <engine/video/AttributeFormat.h>


namespace engine
{
	enum class PrimitiveType;

	template<typename IndexBufferType_t>
	class GeometryLibraryData
	{
	public:
		using IndexContainer = typename std::vector<IndexBufferType_t>;
	public:
		GeometryLibraryData(AttributeFormat attributeFormat, PrimitiveType type, const std::vector<float>& verticies, const IndexContainer& indicies)
			: _attributeFormat(attributeFormat)
			, _primitiveType(type)
			, _verticies(verticies)
			, _indicies(indicies)
		{ }

		AttributeFormat getAttributeFormat() const	{	return _attributeFormat;	}
		PrimitiveType getPrimitiveType() const { return _primitiveType; }
		std::vector<float> getVerticies() const { return _verticies; }
		IndexContainer getInicies() const { return _indicies; }
	private:
		AttributeFormat _attributeFormat;
		PrimitiveType _primitiveType;
		std::vector<float> _verticies;
		IndexContainer _indicies;
	};
}