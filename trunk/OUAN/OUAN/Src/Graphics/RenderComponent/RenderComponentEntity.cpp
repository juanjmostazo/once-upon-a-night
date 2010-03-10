#include "RenderComponentEntity.h"
using namespace OUAN;

RenderComponentEntity::RenderComponentEntity(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_ENTITY)
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

void RenderComponentEntity::setVisible(bool visible)
{
	mEntity->setVisible(visible);
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

