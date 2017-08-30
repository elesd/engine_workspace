#include <stdafx.h>
#include <componentRegisters/SolidComponentRegister.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/VisualComponent.h>

#include <engine/render/Render.h>
#include <engine/render/RenderPassPipeline.h>

#include <RenderDefinitions.h>

void SolidComponentRegister::registerVisualComponent(engine::Entity* entity, engine::VisualComponent* visualComponent, engine::Render* renerer)
{
	renerer->getPipeline<renderPasses::OnlySloid::PipelineRenderer>()->getRenderPass(renderPasses::OnlySloid::Passes::Solid)->registerComponent(visualComponent);
}