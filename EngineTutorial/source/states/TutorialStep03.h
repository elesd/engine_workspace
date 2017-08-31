#pragma once

#include <engine/stateStack/StateBase.h>
#include <engine/signalSlot/SlotHolder.h>
namespace engine
{
	class BufferContext;
	class Material;
	class IndexBufferBase;
	class ShaderResourceDescription;
	class VertexBuffer;
	class Window;

	enum class KeyboardButton;
}

namespace states
{
	class TutorialStep03
		: public engine::StateBase
		, public engine::SlotHolder
	{
	public:
		explicit TutorialStep03(engine::Window *window);
		~TutorialStep03() override;

		engine::ISignalManager* getSignalManager() const override;
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

		std::vector<engine::ShaderResourceDescription> createMaterialParameters() const;
		std::vector<engine::ShaderResourceDescription> createHLSLMaterialParameters() const;
		std::vector<engine::ShaderResourceDescription> createGLSLMaterialParameters() const;

		void createConnections();
		void onKeyUp(engine::KeyboardButton);
	private:
		struct TutorialStep03Private* _members = nullptr;
	};
}