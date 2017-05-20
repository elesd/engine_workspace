#include <engine/video/VideoBufferBase.h>

namespace engine
{
	class VertexBuffer : public VideoBufferBase
	{
	public:
		VertexBuffer();
		VertexBuffer(const std::vector<char>& data);
		~VertexBuffer() override;
	};
}