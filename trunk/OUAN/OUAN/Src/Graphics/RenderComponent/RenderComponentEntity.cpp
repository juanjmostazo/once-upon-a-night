#include "RenderComponentEntity.h"
using namespace OUAN;

RenderComponentEntity::RenderComponentEntity(const std::string& name)
:RenderComponent(COMPONENT_NAME_RENDER_ENTITY)
{
}
RenderComponentEntity::~RenderComponentEntity()
{
	mEntity=NULL;
}

Ogre::Entity* RenderComponentEntity::getEntity() const
{
	return mEntity;
}
void RenderComponentEntity::setEntity(Ogre::Entity* entity)
{
	mEntity=entity;
}

TRenderComponentEntityParameters::TRenderComponentEntityParameters() : TRenderComponentParameters()
{
}
TRenderComponentEntityParameters::~TRenderComponentEntityParameters()
{
}

TRenderComponentSubEntityParameters::TRenderComponentSubEntityParameters() : TRenderComponentParameters()
{
}
TRenderComponentSubEntityParameters::~TRenderComponentSubEntityParameters()
{
}

