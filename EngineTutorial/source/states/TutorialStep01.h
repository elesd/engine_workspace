#pragma once

#include <engine/stateStack/StateBase.h>
namespace engine
{
	class BufferContext;
	class Material;
	class IndexBufferBase;
	class ShaderResourceDescription;
	class VertexBuffer;
	class Window;
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

		void initRender();
		void initTriangle();
		void initShaders();
		void loadScene();

		std::unique_ptr<engine::Material> loadMaterial();
		void loadTriangleVerticies(engine::Material* material, engine::BufferContext* bufferContext);
		void loadTriangleIndicies(engine::BufferContext*);
	private:
		std::vector<engine::ShaderResourceDescription> createMaterialParameters() const;
		std::vector<engine::ShaderResourceDescription> createGLSLMaterialParameters() const;
		std::vector<engine::ShaderResourceDescription> createHLSLMaterialParameters() const;


	private:
		struct TutorialStep01Private* _members = nullptr;

	};
}