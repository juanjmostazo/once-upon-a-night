#include "GameObjectTripollo.h"

using namespace OUAN;

GameObjectTripollo::GameObjectTripollo(const std::string& name)
:GameObject(name)
{

}

GameObjectTripollo::~GameObjectTripollo()
{

}

void GameObjectTripollo::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectTripollo::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectTripollo::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectTripollo::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

void GameObjectTripollo::setToDreams()
{
		Ogre::LogManager::getSingleton().logMessage("TRIPOLLO TO DREAMS");
	mRenderComponentEntityDreams->setVisible(true);
	mRenderComponentEntityNightmares->setVisible(false);
}
void GameObjectTripollo::setToNightmares()
{
		Ogre::LogManager::getSingleton().logMessage("TRIPOLLO TO NIGHTMARES");
	mRenderComponentEntityDreams->setVisible(false);
	mRenderComponentEntityNightmares->setVisible(true);
}

RenderComponentEntityPtr GameObjectTripollo::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTripollo::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTripollo::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectTripollo::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

TGameObjectTripolloParameters::TGameObjectTripolloParameters() : TGameObjectParameters()
{
}

TGameObjectTripolloParameters::~TGameObjectTripolloParameters()
{
}