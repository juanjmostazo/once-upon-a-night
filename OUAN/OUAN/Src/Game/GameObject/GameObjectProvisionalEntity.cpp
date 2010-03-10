#include "GameObjectProvisionalEntity.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectProvisionalEntity::GameObjectProvisionalEntity(const std::string& name)
:GameObject(name)
{

}

GameObjectProvisionalEntity::~GameObjectProvisionalEntity()
{

}

void GameObjectProvisionalEntity::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectProvisionalEntity::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectProvisionalEntity::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectProvisionalEntity::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectProvisionalEntity::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectProvisionalEntity::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectProvisionalEntity::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		if(mLogicComponentWorldExistance->getExistsInDreams() && mLogicComponentWorldExistance->getExistsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
		}
		else if(mLogicComponentWorldExistance->getExistsInDreams()&& !mLogicComponentWorldExistance->getExistsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
		}
		else if(!mLogicComponentWorldExistance->getExistsInDreams()&& mLogicComponentWorldExistance->getExistsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(false);
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponentWorldExistance->getExistsInDreams() && mLogicComponentWorldExistance->getExistsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentEntityNightmares->setVisible(true);
		}
		else if(mLogicComponentWorldExistance->getExistsInDreams()&& !mLogicComponentWorldExistance->getExistsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
		}
		else if(!mLogicComponentWorldExistance->getExistsInDreams()&& mLogicComponentWorldExistance->getExistsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(true);
		}		
		break;
	default:
		break;
	}
}
//-------------------------------------------------------------------------------------------

void GameObjectProvisionalEntity::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectProvisionalEntity::registerHandlers()
{
	GameObjectProvisionalEntityPtr _this =shared_from_this();
	
	registerEventHandler<GameObjectProvisionalEntity,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectProvisionalEntity::processChangeWorld,
		mGameWorldManager->getEventManager());

}
void GameObjectProvisionalEntity::unregisterHandlers()
{
	GameObjectProvisionalEntityPtr _this =shared_from_this();
	
	unregisterEventHandler<GameObjectProvisionalEntity,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectProvisionalEntity::processChangeWorld,
		mGameWorldManager->getEventManager());

}
//-------------------------------------------------------------------------------------------

TGameObjectProvisionalEntityParameters::TGameObjectProvisionalEntityParameters() : TGameObjectParameters()
{

}

TGameObjectProvisionalEntityParameters::~TGameObjectProvisionalEntityParameters()
{

}