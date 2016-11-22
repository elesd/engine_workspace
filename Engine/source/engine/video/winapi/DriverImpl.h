#pragma once

#include "engine/video/Driver.h"

namespace engine
{
	namespace video
	{
		namespace winapi
		{
			class DriverImpl : public Driver
			{
			public:
				DriverImpl();
				~DriverImpl() override;

				void initImpl(const DriverInitParameters& params, view::Window *window) override;
			private:
				struct DriverImplPrivate *_members = nullptr;
			};
		}
	}
}