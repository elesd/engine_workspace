#pragma once

#include <engine/stateStack/StateBase.h>
namespace engine
{
	class Window;
	class Material;
	class VertexBuffer;
	class IndexBufferBase;
}

namespace states
{
	class TutorialStep01
		: public engine::StateBase
	{
	public:
		explicit TutorialStep01(engine::Window *window);
		~TutorialStep01() override;

	private:
		void initState() override;
		void destroyState() override;

		void resumeState() override;
		void pauseState() override;

		void updateState() override;
		void renderState() override;

		void initRender();
		void initTriangle();
		void initShaders();

		std::unique_ptr<engine::Material> loadMaterial();
		std::unique_ptr<engine::VertexBuffer> loadTriangleVerticies();
		std::unique_ptr<engine::IndexBufferBase> loadTriangleIndicies();

		struct TutorialStep01Private* _members = nullptr;

	};
}