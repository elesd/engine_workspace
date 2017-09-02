#include <stdafx.h>
#include <states/TutorialStep02.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/Context.h>

#include <engine/app/Application.h>

#include <engine/entityFramework/Entity.h>
#include <engine/entityFramework/CameraComponent.h>
#include <engine/entityFramework/PerspProjectionComponent.h>
#include <engine/entityFramework/MeshComponent.h>

#include <engine/events/EventManager.h>
#include <engine/events/Keyboard.h>

#include <engine/fileSystem/FilePath.h>

#include <engine/render/RenderContext.h>
#include <engine/render/Render.h>
#include <engine/render/Mesh.h>

#include <engine/scene/Scene.h>
#include <engine/scene/SceneManager.h>

#include <engine/video/AttributeFormat.h>
#include <engine/video/BufferContext.h>
#include <engine/video/Effect.h>
#include <engine/video/EffectCompiler.h>
#include <engine/video/EffectDescription.h>
#include <engine/video/GPUTypes.h>
#include <engine/video/IndexBuffer.h>
#include <engine/video/GlobalShaderResourceStorage.h>
#include <engine/video/Material.h>
#include <engine/video/MaterialDescription.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/MaterialResourceHandler.h>
#include <engine/video/ShaderResourceDescription.h> 
#include <engine/video/ShaderResourceStorage.h>
#include <engine/video/ShaderResourceBindingData.h>
#include <engine/video/VertexBuffer.h>

#include <engine/view/Console.h>
#include <engine/view/Window.h>

#include <RenderDefinitions.h>
#include <componentRegisters/SolidComponentRegister.h>

namespace states
{
	struct TutorialStep02Private
	{
		engine::Window* window = nullptr;
		engine::RenderContext* renderContext = nullptr;
		engine::Scene* scene = nullptr;
		engine::Render* render = nullptr;
		renderPasses::OnlySloid::PipelineRenderer* renderPipeline = nullptr;
		std::unique_ptr<engine::Shader> vs;
		std::unique_ptr<engine::Shader> fs;

		std::unique_ptr<engine::Mesh> triangle;

		glm::vec4 instanceColor;
		explicit TutorialStep02Private(engine::Window* window)
			: window(window)
			, renderContext(window->getRenderContext())
			, instanceColor(0.5f, 0.0f, 0.0f, 0.0f)
		{ }
	};

	TutorialStep02::TutorialStep02(engine::Window *window)
		: engine::StateBase("TutorialStep02")
		, _members(new TutorialStep02Private(window))
	{

	}

	TutorialStep02::~TutorialStep02()
	{
		delete _members;
		_members = nullptr;
	}

	void TutorialStep02::initState()
	{
		initRender();
		initShaders();
		initTriangle();
		//_members->renderPipeline->getRenderPass(renderPasses::TutorialStep02::Passes::Solid)->addObject(_members->triangle.get());
		createConnections();
		loadScene();
	}

	void TutorialStep02::destroyState()
	{

	}

	void TutorialStep02::resumeState()
	{

	}

	void TutorialStep02::pauseState()
	{

	}

	void TutorialStep02::updateState()
	{
	}

	engine::ISignalManager* TutorialStep02::getSignalManager() const
	{
		return _members->window->getEventManager()->getEventsSignalManager();
	}

	void TutorialStep02::initRender()
	{
		std::unique_ptr<engine::PipelineRendererBase> renderTutorialStep02 = renderPasses::OnlySloid::createRenderer(_members->window->getRenderContext());
		_members->render = _members->renderContext->createRender("TutorialStep02", std::move(renderTutorialStep02));
		_members->renderPipeline = _members->render->getPipeline<renderPasses::OnlySloid::PipelineRenderer>();
	}

	void TutorialStep02::initTriangle()
	{
		_members->triangle = std::make_unique<engine::Mesh>("triangle");
		std::unique_ptr<engine::BufferContext> bufferContext = _members->renderContext->createBufferContext();
		std::unique_ptr<engine::Material> material = loadMaterial();
		loadTriangleVerticies(material.get(), bufferContext.get());
		loadTriangleIndicies(bufferContext.get());
		bufferContext->finalize();
		_members->triangle->load(std::move(bufferContext), std::move(material));
	}

	void TutorialStep02::initShaders()
	{
		std::string vsPath;
		std::string fsPath;
		std::string vsMain;
		std::string fsMain;
#if TUTORIAL_USE_WINAPI
	
		vsPath = "shaders/hlsl/Tutorial02.hlsl";
		vsMain = "VShader";
		fsPath = "shaders/hlsl/Tutorial02.hlsl";
		fsMain = "PShader";
	
#else
		vsPath = "shaders/glsl/Tutorial02_vs.glsl";
		vsMain = "main";
		fsPath = "shaders/glsl/Tutorial02_fs.glsl";
		fsMain = "main";
#endif
		_members->vs.reset(new engine::Shader(engine::ShaderType::VertexShader));
		if(_members->vs->init(engine::FilePath(vsPath), vsMain) == false)
		{
			getConsole()->print("Vertex shader creation failed");
		}

		_members->fs.reset(new engine::Shader(engine::ShaderType::FragmentShader));
		if(_members->fs->init(engine::FilePath(fsPath), fsMain) == false)
		{
			getConsole()->print("Fragment shader creation failed");
		}
	}

	void TutorialStep02::loadScene()
	{
		std::unique_ptr<SolidComponentRegister> componentRegister(new SolidComponentRegister());
		_members->scene = engine::Context::application()->getSceneManager()->createScene("TutorialStep02", _members->renderContext, "TutorialStep02", std::move(componentRegister));
	/*	{
			std::unique_ptr<engine::Entity> camera(new engine::Entity("Camera"));
			engine::PerspectiveProjectionSettings settings(glm::radians(70.0f), 0.1f, 100.0f);
			std::unique_ptr<engine::CameraComponent> cameraComponent(new engine::CameraComponent(_members->window, settings, glm::vec3(0.0f)));
			camera->registerCameraComponent(std::move(cameraComponent));
			_members->scene->registerEntity(std::move(camera));
		}*/
		{
			std::unique_ptr<engine::Entity> entity(new engine::Entity("Triangle"));
			std::unique_ptr<engine::MeshComponent> meshComponent(new engine::MeshComponent(_members->triangle.get()));
			entity->registerVisualComponent(std::move(meshComponent));
			_members->scene->registerEntity(std::move(entity));
		}
	}

	std::vector<engine::ShaderResourceDescription> TutorialStep02::createHLSLMaterialParameters() const
	{
		std::vector<engine::ShaderResourceDescription> result;
		result.push_back(engine::ShaderResourceDescription("instanceColor",
						 engine::GPUMemberType::Vec4,
						 engine::ShaderResourceBindingData(0, {engine::ShaderType::VertexShader})));
		return result;
	}

	std::vector<engine::ShaderResourceDescription> TutorialStep02::createGLSLMaterialParameters() const
	{
		std::vector<engine::ShaderResourceDescription> result;
		result.push_back(engine::ShaderResourceDescription("instanceColor",
														   engine::GPUMemberType::Vec4,
														   engine::ShaderResourceBindingData({ engine::ShaderType::VertexShader })));
		return result;
	}

	std::vector<engine::ShaderResourceDescription> TutorialStep02::createMaterialParameters() const
	{
#if TUTORIAL_USE_WINAPI
		return createHLSLMaterialParameters();
#else
		return createGLSLMaterialParameters();
#endif
	}


	std::unique_ptr<engine::Material> TutorialStep02::loadMaterial()
	{
		ASSERT(_members->fs);
		ASSERT(_members->fs->isInitialized());
		ASSERT(_members->vs);
		ASSERT(_members->vs->isInitialized());

		engine::AttributeFormat layout;
		layout.insertAttribute(engine::GPUMemberType::Vec3, 0, "position");
		layout.insertAttribute(engine::GPUMemberType::Vec4, 1, "color");
#if TUTORIAL_USE_WINAPI
		engine::MaterialDescription description(engine::ShaderVersion::HLSL_5_0);
#else
		engine::MaterialDescription description(engine::ShaderVersion::GLSL_330);
#endif
		description.setFragmentShader(_members->fs.get());
		description.setVertexShader(_members->vs.get());
		
		std::vector<engine::ShaderResourceDescription> materialParameters = createMaterialParameters();
		for(const engine::ShaderResourceDescription& materialParam : materialParameters)
		{
			description.getDefaultEffect().addParameter(materialParam);
		}

		description.getDefaultEffect().getOptions().addFlag(engine::ShaderCompileFlag::Debug);
		description.setAttributeFormat(layout);

		std::unique_ptr<engine::Material> result = std::make_unique<engine::Material>("Simple", description, _members->renderContext);
		result->getResourceHandler()->setVec4("instanceColor", _members->instanceColor);
		return result;
	}

	void TutorialStep02::loadTriangleVerticies(engine::Material* material, engine::BufferContext* bufferContext)
	{
#if TUTORIAL_USE_WINAPI
		std::vector<float> data(
		{
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.45f, -0.5, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.45f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		});
#else
		std::vector<float> data(
		{
			-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		});
#endif
		
		bufferContext->setupVertexBuffer(material->getAttributeFormat(), data);
	}

	void TutorialStep02::loadTriangleIndicies(engine::BufferContext* bufferContext)
	{
		std::vector<int32_t> data = 
		{
			0, 1, 2
		};
		bufferContext->setupIndexBuffer(engine::PrimitiveType::Triangle, data);
	}

	void TutorialStep02::createConnections()
	{
		engine::Keyboard* keyboard = _members->window->getEventManager()->findEventSource<engine::Keyboard>()[0];
		CONNECT_SIGNAL(keyboard, keyReleased, this, onKeyUp);
	}

	void TutorialStep02::onKeyUp(engine::KeyboardButton button)
	{
		switch(button)
		{
			case engine::KeyboardButton::Key_Up:
				_members->instanceColor.r = (std::min)(1.0f, _members->instanceColor.r + 0.1f);
				break;
			case engine::KeyboardButton::Key_Down:
				_members->instanceColor.r = (std::max)(0.0f, _members->instanceColor.r - 0.1f);
				break;
		}		
		_members->triangle->getMaterial()->getResourceHandler()->setVec4("instanceColor", _members->instanceColor);
	}
}
