#include "GameObjectFlashLight.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Graphics/CameraManager/CameraManager.h"
#include "../../Graphics/RenderComponent/RenderComponentLight.h"
#include "../../RayCasting/RayCasting.h"

using namespace OUAN;

GameObjectFlashLight::GameObjectFlashLight(const std::string& name,  GameWorldManagerPtr pGameWorldManager, CameraManagerPtr pCameraManager, RayCastingPtr pRayCasting)
:GameObject(name,GAME_OBJECT_TYPE_FLASHLIGHT)
{
	mGameWorldManager=pGameWorldManager;
	mCameraManager=pCameraManager;
	mRayCasting=pRayCasting;

	distance=10000.0f;
}

GameObjectFlashLight::~GameObjectFlashLight()
{

}

RenderComponentEntityPtr GameObjectFlashLight::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectFlashLight::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectFlashLight::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}


RenderComponentLightPtr GameObjectFlashLight::getRenderComponentLight() const
{
	return mRenderComponentLight;
}

void GameObjectFlashLight::setRenderComponentLight(RenderComponentLightPtr pRenderComponentLight)
{
	mRenderComponentLight = pRenderComponentLight;
}

void GameObjectFlashLight::setLightPositionalComponent(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mLightPositionalComponent=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectFlashLight::getLightPositionalComponent() const
{
	return mLightPositionalComponent;
}

RenderComponentPositionalPtr GameObjectFlashLight::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectFlashLight::setPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule)
{
	mPhysicsComponentSimpleCapsule=pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleCapsulePtr GameObjectFlashLight::getPhysicsComponentSimpleCapsule()
{
	return mPhysicsComponentSimpleCapsule;
}

void GameObjectFlashLight::changeWorld(int world)
{

	switch(world)
	{
	case DREAMS:
		//TODO: set this to false
		mRenderComponentLight->setVisible(true);
		break;
	case NIGHTMARES:
		mRenderComponentLight->setVisible(true);
		break;
	default:
		break;
	}
}
bool GameObjectFlashLight::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectFlashLight::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

void GameObjectFlashLight::detectLightCollisions()
{
	Vector3 position;
	Vector3 direction;
	std::vector<GameObjectPtr> result;

	Ogre::Camera * camera;
	camera=mCameraManager->getActiveCamera();

	position=mLightPositionalComponent->getPosition();

	direction=mLightPositionalComponent->getPosition()-camera->getPosition();
	direction.normalise();

	//Ogre::LogManager::getSingleton().logMessage("FLASHLIGHT COLLISIONS");

	//int numHits = mRayCasting->raycastPhysicsAllBoundings(position,
 //                                       direction,
 //                                       result,
	//									10,
	//									QUERYFLAGS_FLASHLIGHT_LIGHT);

	//Ogre::LogManager::getSingleton().logMessage("RAYCAST NUMBER OF HITS "+Ogre::StringConverter::toString(numHits));
}

void GameObjectFlashLight::update(double elapsedSeconds)
{
	Ogre::Camera * camera;
	Vector3 direction;

	camera=mCameraManager->getActiveCamera();

	mLightPositionalComponent->setPosition(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition());
	//mLightPositionalComponent->setOrientation(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getOrientation());

	mRenderComponentPositional->setPosition(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition());
	mRenderComponentPositional->setOrientation(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getOrientation());

	direction=mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition()-camera->getPosition();
	direction.normalise();

	mRenderComponentLight->setDirection(direction);
}

TGameObjectFlashLightParameters::TGameObjectFlashLightParameters() : TGameObjectParameters()
{

}

TGameObjectFlashLightParameters::~TGameObjectFlashLightParameters()
{

}