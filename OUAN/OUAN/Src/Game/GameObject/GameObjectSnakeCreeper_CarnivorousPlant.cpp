#include "GameObjectSnakeCreeper_CarnivorousPlant.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectSnakeCreeper_CarnivorousPlant::GameObjectSnakeCreeper_CarnivorousPlant(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SNAKE_CREEPER_CARNIVOROUS_PLANT)
{

}

GameObjectSnakeCreeper_CarnivorousPlant::~GameObjectSnakeCreeper_CarnivorousPlant()
{

}

void GameObjectSnakeCreeper_CarnivorousPlant::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectSnakeCreeper_CarnivorousPlant::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectSnakeCreeper_CarnivorousPlant::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

void GameObjectSnakeCreeper_CarnivorousPlant::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectSnakeCreeper_CarnivorousPlant::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectSnakeCreeper_CarnivorousPlant::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectSnakeCreeper_CarnivorousPlant::setPhysicsComponentCharacterDreams(PhysicsComponentCharacterPtr pPhysicsComponentCharacterDreams)
{
	mPhysicsComponentCharacterDreams=pPhysicsComponentCharacterDreams;
}

PhysicsComponentCharacterPtr GameObjectSnakeCreeper_CarnivorousPlant::getPhysicsComponentCharacterDreams()
{
	return mPhysicsComponentCharacterDreams;
}

void GameObjectSnakeCreeper_CarnivorousPlant::setPhysicsComponentCharacterNightmares(PhysicsComponentCharacterPtr pPhysicsComponentCharacterNightmares)
{
	mPhysicsComponentCharacterNightmares=pPhysicsComponentCharacterNightmares;
}

PhysicsComponentCharacterPtr GameObjectSnakeCreeper_CarnivorousPlant::getPhysicsComponentCharacterNightmares()
{
	return mPhysicsComponentCharacterNightmares;
}

void GameObjectSnakeCreeper_CarnivorousPlant::update(double elapsedSeconds)
{

}


//-------------------------------------------------------------------------------------------
TGameObjectSnakeCreeper_CarnivorousPlantParameters::TGameObjectSnakeCreeper_CarnivorousPlantParameters() : TGameObjectParameters()
{

}

TGameObjectSnakeCreeper_CarnivorousPlantParameters::~TGameObjectSnakeCreeper_CarnivorousPlantParameters()
{

}