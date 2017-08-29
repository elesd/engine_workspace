#include <stdafx.h>
#include <componentRegisters/SolidComponentRegister.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/VisualComponent.h>

#include <engine/render/Render.h>
#include <engine/render/RenderPassPipeline.h>

#include <RenderDefinitions.h>

void SolidComponentRegister::registerVisualComponent(engine::Entity* entity, engine::VisualComponent* visualComponent, engine::Render* renerer)
{
	switch(_tutorialId)
	{
		case 1:
			renerer->getPipeline<renderPasses::TutorialStep01::PipelineRenderer>()->getRenderPass(renderPasses::TutorialStep01::Passes::Solid)->registerComponent(visualComponent);
			break;
		case 2:
			renerer->getPipeline<renderPasses::TutorialStep02::PipelineRenderer>()->getRenderPass(renderPasses::TutorialStep02::Passes::Solid)->registerComponent(visualComponent);
			break;
		default:
			FAIL("Unknown tutorial");
	}
}