#include "GameObjectTripollo.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTripollo::GameObjectTripollo(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIPOLLO)
{

}

GameObjectTripollo::~GameObjectTripollo()
{

}

void GameObjectTripollo::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTripollo::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTripollo::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTripollo::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTripollo::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectTripollo::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
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

void GameObjectTripollo::update(double elapsedSeconds)
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

void GameObjectTripollo::reset()
{
	GameObject::reset();
}

void GameObjectTripollo::changeWorld(int world)
{
	if (!isEnabled()) return;

	if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
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
		}
		if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->create();
		}
		return;
	}
	else
	{
		switch(world)
		{
		case DREAMS:
			
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentEntityDreams->setVisible(true);
				if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->create();
				}
			}
			else
			{
				mRenderComponentEntityNightmares->setVisible(false);
				if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->create();
				}
			}
			else
			{
				mRenderComponentEntityDreams->setVisible(false);
				if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->destroy();
				}
			}
			break;
		default:
			break;
		}
	}
}
bool GameObjectTripollo::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectTripollo::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------
TGameObjectTripolloParameters::TGameObjectTripolloParameters() : TGameObjectParameters()
{

}

TGameObjectTripolloParameters::~TGameObjectTripolloParameters()
{

}