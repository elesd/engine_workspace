#include <stdafx.h>
#include <states/TutorialStep01.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/fileSystem/FilePath.h>

#include <engine/render/Effect.h>
#include <engine/render/RenderContext.h>
#include <engine/render/Render.h>
#include <engine/render/Material.h>
#include <engine/render/MaterialDescription.h>
#include <engine/render/Mesh.h>
#include <engine/render/EffectCompiler.h>

#include <engine/video/GPUTypes.h>
#include <engine/video/IndexBuffer.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/ShaderLayoutDescription.h>
#include <engine/video/VertexBuffer.h>

#include <engine/view/Window.h>

#include <RenderDefinitions.h>
#include <Log.h>

namespace states
{
	struct TutorialStep01Private
	{
		engine::Window* window = nullptr;
		engine::RenderContext* renderContext = nullptr;
		engine::Render* render = nullptr;
		std::unique_ptr<engine::Effect> defaultEffect;
		renderPasses::TutorialStep01::PipelineRenderer* renderPipeline = nullptr;
		std::unique_ptr<engine::Shader> vs;
		std::unique_ptr<engine::Shader> fs;

		std::unique_ptr<engine::Mesh> triangle;
		explicit TutorialStep01Private(engine::Window* window)
			: window(window)
			, renderContext(window->getRenderContext())
		{ }
	};

	TutorialStep01::TutorialStep01(engine::Window *window)
		: engine::StateBase("TutorialStep01")
		, _members(new TutorialStep01Private(window))
	{

	}

	TutorialStep01::~TutorialStep01()
	{
		delete _members;
		_members = nullptr;
	}

	void TutorialStep01::initState()
	{
		initRender();
		initShaders();
		initTriangle();
		_members->renderPipeline->getRenderPass(renderPasses::TutorialStep01::Passes::Solid)->addObject(_members->triangle.get());
	}

	void TutorialStep01::destroyState()
	{

	}

	void TutorialStep01::resumeState()
	{

	}

	void TutorialStep01::pauseState()
	{

	}

	void TutorialStep01::updateState()
	{
		
	}

	void TutorialStep01::renderState()
	{
		_members->render->render();
		_members->renderContext->swapBuffer();
	}

	void TutorialStep01::initRender()
	{
		std::unique_ptr<engine::PipelineRendererBase> renderTutorialStep01 = renderPasses::TutorialStep01::createRenderer(_members->window->getRenderContext());
		_members->render = _members->renderContext->createRender("TutorialStep01", std::move(renderTutorialStep01));
		_members->renderPipeline = _members->render->getPipeline<renderPasses::TutorialStep01::PipelineRenderer>();
		
	}

	void TutorialStep01::initTriangle()
	{
		_members->triangle = std::make_unique<engine::Mesh>("triangle");
		std::unique_ptr<engine::Material> material = loadMaterial();
		std::unique_ptr<engine::VertexBuffer> verticies = loadTriangleVerticies(material.get());
		std::unique_ptr<engine::IndexBufferBase> indicies = loadTriangleIndicies();
		_members->triangle->load(std::move(verticies), std::move(indicies), std::move(material));
	}

	void TutorialStep01::initShaders()
	{
		_members->vs.reset(new engine::Shader(engine::ShaderType::VertexShader));
		if(_members->vs->init(engine::FilePath("shaders/hlsl/Tutorial01.hlsl"), "VShader") == false)
		{
			Log("Vertex shader creation failed");
		}

		_members->fs.reset(new engine::Shader(engine::ShaderType::FragmentShader));
		if(_members->fs->init(engine::FilePath("shaders/hlsl/Tutorial01.hlsl"), "PShader") == false)
		{
			Log("Fragment shader creation failed");
		}
	}

	std::unique_ptr<engine::Material> TutorialStep01::loadMaterial()
	{
		ASSERT(_members->fs);
		ASSERT(_members->vs);
		engine::MaterialDescription description(engine::ShaderVersion::HLSL_5_0);
	
		engine::ShaderLayoutDescription layout;
		layout.insertAttribute(engine::GPUMemberType::Vec3, 0, "position");
		layout.insertAttribute(engine::GPUMemberType::Vec4, 1, "color");

		description.setFragmentShader(_members->fs.get());
		description.setVertexShader(_members->vs.get());
		engine::ShaderCompileOptions options = description.createEmptyOptions();
		options.addFlag(engine::ShaderCompileFlag::Debug);
		options.setLayout(layout);
		description.setDefaultTechnique(options);
		
		return std::make_unique<engine::Material>("Simple", description, _members->renderContext);
	}

	std::unique_ptr<engine::VertexBuffer> TutorialStep01::loadTriangleVerticies(const engine::Material* material)
	{
		std::vector<float> data(
		{
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.45f, -0.5, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.45f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		});
		std::vector<char> rawData;
		rawData.resize(data.size() * sizeof(float));
		memcpy(rawData.data(), data.data(), rawData.size());

		std::unique_ptr<engine::VertexBuffer> buffer = material->createVertexBufferFor(engine::Material::defaultEffectName);
		buffer->fill(rawData);
		buffer->map(_members->renderContext);
		return buffer;
	}

	std::unique_ptr<engine::IndexBufferBase> TutorialStep01::loadTriangleIndicies()
	{
		std::vector<int32_t> data = 
		{
			0, 1, 2
		};
		std::unique_ptr<engine::IndexBufferBase> buffer(new engine::IndexBuffer<int32_t>(engine::PrimitiveType::Triangle, data));
		buffer->map(_members->renderContext);
		return buffer;
	}
}