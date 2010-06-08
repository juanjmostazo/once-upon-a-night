#include "OUAN_Precompiled.h"

#include "RenderComponent.h"
using namespace OUAN;

RenderComponent::RenderComponent(const std::string& type)
:Component(COMPONENT_TYPE_RENDER)
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