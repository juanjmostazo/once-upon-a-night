#include "GameObjectParticleSystem.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectParticleSystem::GameObjectParticleSystem(const std::string& name)
:GameObject(name)
{

}

GameObjectParticleSystem::~GameObjectParticleSystem()
{

}

RenderComponentParticleSystemPtr GameObjectParticleSystem::getRenderComponentParticleSystem() const
{
	return mRenderComponentParticleSystem;
}

void GameObjectParticleSystem::setRenderComponentParticleSystem(RenderComponentParticleSystemPtr pRenderComponentParticleSystem)
{
	mRenderComponentParticleSystem=pRenderComponentParticleSystem;
}
void GameObjectParticleSystem::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectParticleSystem::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectParticleSystem::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}

}
//-------------------------------------------------------------------------------------------
void GameObjectParticleSystem::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectParticleSystem::registerHandlers()
{
	GameObjectParticleSystemPtr _this =shared_from_this();

	registerEventHandler<GameObjectParticleSystem,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectParticleSystem::processChangeWorld,
		mGameWorldManager->getEventManager());
}

void GameObjectParticleSystem::unregisterHandlers()
{
	GameObjectParticleSystemPtr _this =shared_from_this();

	unregisterEventHandler<GameObjectParticleSystem,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectParticleSystem::processChangeWorld,
		mGameWorldManager->getEventManager());
}
//-------------------------------------------------------------------------------------------

TGameObjectParticleSystemParameters::TGameObjectParticleSystemParameters() : TGameObjectParameters()
{

}

TGameObjectParticleSystemParameters::~TGameObjectParticleSystemParameters()
{

}