#include "GameObjectEye.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectEye::GameObjectEye(const std::string& name)
:GameObject(name)
{

}

GameObjectEye::~GameObjectEye()
{

}

RenderComponentEntityPtr GameObjectEye::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectEye::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectEye::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectEye::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectEye::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectEye::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectEye::update(double elapsedSeconds)
{
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

	getPhysicsComponentCharacter()->getNxOgreController()->move(
		Application::getInstance()->getPhysicsSubsystem()->mGravity * 
			Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale,
		GROUP_COLLIDABLE_MASK,
		Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
		collisionFlags);
}

void GameObjectEye::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->create();
		}
		break;
	case NIGHTMARES:
		break;
	default:break;
	}

}
//-------------------------------------------------------------------------------------------

void GameObjectEye::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectEye::registerHandlers()
{
	GameObjectEyePtr _this =shared_from_this();

	registerEventHandler<GameObjectEye,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectEye::processChangeWorld,
		mGameWorldManager->getEventManager());
}
void GameObjectEye::unregisterHandlers()
{
	GameObjectEyePtr _this =shared_from_this();

	unregisterEventHandler<GameObjectEye,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectEye::processChangeWorld,
		mGameWorldManager->getEventManager());
}
//-------------------------------------------------------------------------------------------

TGameObjectEyeParameters::TGameObjectEyeParameters() : TGameObjectParameters()
{

}

TGameObjectEyeParameters::~TGameObjectEyeParameters()
{

}