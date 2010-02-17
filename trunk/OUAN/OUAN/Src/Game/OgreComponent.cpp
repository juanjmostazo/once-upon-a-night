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
Ogre::Camera* OgreComponent::getCamera() const
{
	return mCamera;
}
void OgreComponent::setCamera(Ogre::Camera* camera)
{
	mCamera=camera;
}
Ogre::ParticleSystem* OgreComponent::getParticleSystem() const
{
	return mParticleSystem;
}
void OgreComponent::setParticleSystem(Ogre::ParticleSystem* particleSystem)
{
	mParticleSystem=particleSystem;
}
Ogre::BillboardSet* OgreComponent::getBillboardSet() const
{
	return mBillboardSet;
}
void OgreComponent::setBillboardSet(Ogre::BillboardSet* billboardSet)
{
	mBillboardSet=billboardSet;
}
Ogre::Light* OgreComponent::getLight() const
{
	return mLight;
}
void OgreComponent::setLight(Ogre::Light* light)
{
	mLight=light;
}

void OgreComponent::update(long elapsedTime)
{
}