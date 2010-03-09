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

RenderComponentEntityPtr GameObjectProvisionalEntity::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectProvisionalEntity::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
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
	if(mLogicComponentWorldExistance->getExistsInDreams() && mLogicComponentWorldExistance->getExistsInNightmares())
	{

		return;
	}
	else
	{
		switch(world)
		{
		case DREAMS:
			if(mLogicComponentWorldExistance->getExistsInDreams())
			{
				mRenderComponentEntity->setVisible(true);
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponentWorldExistance->getExistsInNightmares())
			{
				mRenderComponentEntity->setVisible(true);
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
			}
			break;
		default:
			break;
		}
	}
}

void GameObjectProvisionalEntity::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectProvisionalEntity::registerHandlers()
{
	GameObjectProvisionalEntityPtr _this =shared_from_this();
	//Subscribe to world change event
	registerEventHandler<GameObjectProvisionalEntity,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectProvisionalEntity::processChangeWorld,
		mGameWorldManager->getEventManager());

}
void GameObjectProvisionalEntity::unregisterHandlers()
{
	GameObjectProvisionalEntityPtr _this =shared_from_this();
	//Subscribe to world change event
	registerEventHandler<GameObjectProvisionalEntity,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectProvisionalEntity::processChangeWorld,
		mGameWorldManager->getEventManager());

}
//-------------------------------------------------------------------------------------------

TGameObjectProvisionalEntityParameters::TGameObjectProvisionalEntityParameters() : TGameObjectParameters()
{

}

TGameObjectProvisionalEntityParameters::~TGameObjectProvisionalEntityParameters()
{

}