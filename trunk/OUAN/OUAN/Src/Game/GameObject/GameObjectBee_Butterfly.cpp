#include "GameObjectBee_Butterfly.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectBee_Butterfly::GameObjectBee_Butterfly(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_BEE_BUTTERFLY)
{

}

GameObjectBee_Butterfly::~GameObjectBee_Butterfly()
{

}

void GameObjectBee_Butterfly::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectBee_Butterfly::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectBee_Butterfly::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

void GameObjectBee_Butterfly::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectBee_Butterfly::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectBee_Butterfly::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectBee_Butterfly::setPhysicsComponentCharacterDreams(PhysicsComponentCharacterPtr pPhysicsComponentCharacterDreams)
{
	mPhysicsComponentCharacterDreams=pPhysicsComponentCharacterDreams;
}

PhysicsComponentCharacterPtr GameObjectBee_Butterfly::getPhysicsComponentCharacterDreams()
{
	return mPhysicsComponentCharacterDreams;
}

void GameObjectBee_Butterfly::setPhysicsComponentCharacterNightmares(PhysicsComponentCharacterPtr pPhysicsComponentCharacterNightmares)
{
	mPhysicsComponentCharacterNightmares=pPhysicsComponentCharacterNightmares;
}

PhysicsComponentCharacterPtr GameObjectBee_Butterfly::getPhysicsComponentCharacterNightmares()
{
	return mPhysicsComponentCharacterNightmares;
}

void GameObjectBee_Butterfly::update(double elapsedSeconds)
{

}

//-------------------------------------------------------------------------------------------
TGameObjectBee_ButterflyParameters::TGameObjectBee_ButterflyParameters() : TGameObjectParameters()
{

}

TGameObjectBee_ButterflyParameters::~TGameObjectBee_ButterflyParameters()
{

}