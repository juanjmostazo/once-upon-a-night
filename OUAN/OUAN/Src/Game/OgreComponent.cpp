#include "OgreComponent.h"
using namespace OUAN;

OgreComponent::OgreComponent(const std::string& name)
:Component(name.empty()?COMPONENT_NAME_OGRE:name,COMPONENT_NAME_OGRE)
{
}
OgreComponent::~OgreComponent()
{
	//Since we don't own them, we can't delete them
	//Ogre should take care of it
	mSceneNode=NULL;
	mEntity=NULL;
	//...delete others
}
Ogre::SceneNode* OgreComponent::getSceneNode() const
{
	return mSceneNode;
}
void OgreComponent::setSceneNode(Ogre::SceneNode* sceneNode)
{
	mSceneNode=sceneNode;
}
Ogre::Entity* OgreComponent::getEntity() const
{
	return mEntity;
}
void OgreComponent::setEntity(Ogre::Entity* entity)
{
	mEntity=entity;
}

void OgreComponent::update(long elapsedTime)
{
}