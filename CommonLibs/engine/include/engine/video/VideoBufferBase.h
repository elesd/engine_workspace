#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	class VideoBufferBase
		: private NonCopyable
	{
	public:
		VideoBufferBase();
		explicit VideoBufferBase(const std::vector<char>& data);

		VideoBufferBase(VideoBufferBase&& o);
		virtual ~VideoBufferBase();

		VideoBufferBase& operator=(VideoBufferBase &&o);

		void setData(const std::vector<char>& data);
		const std::vector<char>& getData() const;
		std::vector<char>& getData();

	private:
		struct VideoBufferBasePrivate* _members = nullptr;
	};
}