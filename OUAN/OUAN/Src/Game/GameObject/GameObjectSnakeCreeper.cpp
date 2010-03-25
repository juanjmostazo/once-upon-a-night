#include "GameObjectSnakeCreeper.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectSnakeCreeper::GameObjectSnakeCreeper(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SNAKECREEPER)
{

}

GameObjectSnakeCreeper::~GameObjectSnakeCreeper()
{

}

void GameObjectSnakeCreeper::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectSnakeCreeper::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectSnakeCreeper::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectSnakeCreeper::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectSnakeCreeper::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectSnakeCreeper::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectSnakeCreeper::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectSnakeCreeper::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectSnakeCreeper::update(double elapsedSeconds)
{
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		getPhysicsComponentCharacter()->getNxOgreController()->move(
			Application::getInstance()->getPhysicsSubsystem()->mGravity * 
			Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale,
			GROUP_COLLIDABLE_MASK,
			Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
			collisionFlags);
	}
}

void GameObjectSnakeCreeper::changeWorld(int world)
{
	if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}
	switch(world)
	{
	case DREAMS:
		mRenderComponentEntityDreams->setVisible(true);
		mRenderComponentEntityNightmares->setVisible(false);
		break;
	case NIGHTMARES:
		mRenderComponentEntityDreams->setVisible(false);
		mRenderComponentEntityNightmares->setVisible(true);
		break;
	default:break;
	}
}
//-------------------------------------------------------------------------------------------
TGameObjectSnakeCreeperParameters::TGameObjectSnakeCreeperParameters() : TGameObjectParameters()
{

}

TGameObjectSnakeCreeperParameters::~TGameObjectSnakeCreeperParameters()
{

}