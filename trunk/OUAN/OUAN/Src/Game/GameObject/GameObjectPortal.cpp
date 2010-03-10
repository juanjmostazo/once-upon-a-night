#include "GameObjectPortal.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectPortal::GameObjectPortal(const std::string& name)
:GameObject(name)
{

}

GameObjectPortal::~GameObjectPortal()
{

}

RenderComponentEntityPtr GameObjectPortal::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectPortal::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectPortal::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectPortal::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

void GameObjectPortal::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectPortal::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectPortal::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectPortal::getPhysicsComponentSimpleBox()
{
	return mPhysicsComponentSimpleBox;
}
void GameObjectPortal::changeWorld(int world)
{
	if(mLogicComponentWorldExistance->getExistsInDreams() && mLogicComponentWorldExistance->getExistsInNightmares())
	{
		//Ogre::LogManager::getSingleton().logMessage("BOTH " + getName());
		if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
		{
			//Ogre::LogManager::getSingleton().logMessage("BOTH IN " + getName());
			mPhysicsComponentSimpleBox->create();
		}
		return;
	}
	else
	{
		switch(world)
		{
		case DREAMS:
			//Ogre::LogManager::getSingleton().logMessage("DREAMS " + getName());

			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}
	
			break;
		case NIGHTMARES:
			//Ogre::LogManager::getSingleton().logMessage("NIGHT " + getName());
	
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentEntityNightmares->setVisible(true);
			if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
			{
				mPhysicsComponentSimpleBox->create();
			}

			break;
		default:
			break;
		}
	}
}
//-------------------------------------------------------------------------------------------

void GameObjectPortal::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectPortal::registerHandlers()
{
	GameObjectPortalPtr _this =shared_from_this();

	registerEventHandler<GameObjectPortal,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectPortal::processChangeWorld,
		mGameWorldManager->getEventManager());
}
void GameObjectPortal::unregisterHandlers()
{
	GameObjectPortalPtr _this =shared_from_this();

	unregisterEventHandler<GameObjectPortal,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectPortal::processChangeWorld,
		mGameWorldManager->getEventManager());
}
//-------------------------------------------------------------------------------------------

TGameObjectPortalParameters::TGameObjectPortalParameters() : TGameObjectParameters()
{

}

TGameObjectPortalParameters::~TGameObjectPortalParameters()
{

}