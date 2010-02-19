#include "RenderComponentEntity.h"
using namespace OUAN;

RenderComponentEntity::RenderComponentEntity(const std::string& name)
:RenderComponent(name.empty()?COMPONENT_NAME_OGRE:name)
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

