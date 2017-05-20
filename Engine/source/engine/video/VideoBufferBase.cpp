#include <stdafx.h>
#include <engine/video/VideoBufferBase.h>

namespace engine
{
	struct VideoBufferBasePrivate
	{
		std::vector<char> data;
		VideoBufferBasePrivate() = default;
		VideoBufferBasePrivate(const std::vector<char> &data)
			:data(data)
		{ }
	};

	VideoBufferBase::VideoBufferBase()
		: _members(new VideoBufferBasePrivate())
	{

	}

	VideoBufferBase::VideoBufferBase(const std::vector<char>& data)
		: _members(new VideoBufferBasePrivate(data))
	{

	}

	VideoBufferBase::VideoBufferBase(VideoBufferBase&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	VideoBufferBase::~VideoBufferBase()
	{
		delete _members;
	}

	VideoBufferBase& VideoBufferBase::operator=(VideoBufferBase &&o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	void VideoBufferBase::setData(const std::vector<char>& data)
	{
		_members->data = data;
	}

	const std::vector<char>& VideoBufferBase::getData() const
	{
		return _members->data;
	}

	std::vector<char>& VideoBufferBase::getData()
	{
		return _members->data;
	}

}