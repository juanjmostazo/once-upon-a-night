#include "RenderComponent.h"
using namespace OUAN;

RenderComponent::RenderComponent(const std::string& name)
:Component(COMPONENT_NAME_RENDER)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::update(long elapsedTime)
{
}

TRenderComponentParameters::TRenderComponentParameters() : TComponentParameters()
{
}

TRenderComponentParameters::~TRenderComponentParameters()
{
}