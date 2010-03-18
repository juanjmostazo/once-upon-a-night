#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectOny::GameObjectOny(const std::string& name)
:GameObject(name)
{
	
}

GameObjectOny::~GameObjectOny()
{

}

void GameObjectOny::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectOny::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectOny::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectOny::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectOny::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectOny::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectOny::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectOny::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectOny::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	//TODO THIS SHOULD BE DONE IN A GENERAL WAY IN THE PHYSICSSUBSYSTEM::UPDATE
	mPhysicsComponentCharacter->update(elapsedSeconds);
}

void GameObjectOny::changeWorld(int world)
{
	if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}
}

TGameObjectOnyParameters::TGameObjectOnyParameters() : TGameObjectParameters()
{

}

TGameObjectOnyParameters::~TGameObjectOnyParameters()
{

}
