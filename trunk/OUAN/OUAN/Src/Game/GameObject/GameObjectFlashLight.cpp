#include "GameObjectFlashLight.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Graphics/CameraManager/CameraManager.h"
#include "../../Graphics/RenderComponent/RenderComponentLight.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeConvex.h"
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

void GameObjectFlashLight::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentLightPtr GameObjectFlashLight::getRenderComponentLight() const
{
	return mRenderComponentLight;
}

void GameObjectFlashLight::setRenderComponentLight(RenderComponentLightPtr pRenderComponentLight)
{
	mRenderComponentLight = pRenderComponentLight;
	mRenderComponentLight->getLight()->setVisible(false);
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

RenderComponentInitialPtr GameObjectFlashLight::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectFlashLight::setPhysicsComponentVolumeConvex(PhysicsComponentVolumeConvexPtr pPhysicsComponentVolumeConvex)
{
	mPhysicsComponentVolumeConvex=pPhysicsComponentVolumeConvex;
}

PhysicsComponentVolumeConvexPtr GameObjectFlashLight::getPhysicsComponentVolumeConvex()
{
	return mPhysicsComponentVolumeConvex;
}

void GameObjectFlashLight::changeWorld(int world)
{

	switch(world)
	{
	case DREAMS:
		//PROVISIONAL
		mRenderComponentLight->getLight()->setVisible(false);
		if (mPhysicsComponentVolumeConvex.get() && mPhysicsComponentVolumeConvex->isInUse())
		{
			mPhysicsComponentVolumeConvex->destroy();
		}
		break;
	case NIGHTMARES:
		//PROVISIONAL
		mRenderComponentLight->getLight()->setVisible(true);
		if (mPhysicsComponentVolumeConvex.get() && !mPhysicsComponentVolumeConvex->isInUse())
		{
			mPhysicsComponentVolumeConvex->create();
		}
		break;
	default:
		break;
	}
}

void GameObjectFlashLight::reset()
{
	GameObject::reset();
}

bool GameObjectFlashLight::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectFlashLight::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

void GameObjectFlashLight::update(double elapsedSeconds)
{
	Ogre::Camera * camera;
	Vector3 direction;

	GameObject::update(elapsedSeconds);

	camera=mCameraManager->getActiveCamera();

	if(mCameraManager->getActiveCameraControllerType()==CAMERA_THIRD_PERSON)
	{
		mRenderComponentPositional->setPosition(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition());
		mRenderComponentPositional->setOrientation(camera->getOrientation());

		if (mPhysicsComponentVolumeConvex.get() && mPhysicsComponentVolumeConvex->isInUse())
		{
			//OUCH! BUT FOR THE MOMENT WE LEAVE IT LIKE THIS as there's an error getting the orientation if not done that way
			mPhysicsComponentVolumeConvex->destroy();
			mPhysicsComponentVolumeConvex->create();

			mPhysicsComponentVolumeConvex->setPosition(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition());

			camera=mCameraManager->getActiveCamera();
			mPhysicsComponentVolumeConvex->setOrientation(camera->getOrientation());
		}
	}

	mLightPositionalComponent->setPosition(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition());

	direction=mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition()-camera->getPosition();
	direction.normalise();

	mRenderComponentLight->setDirection(direction);



	//OLD STUFF

	//Ogre::Camera * camera;
	//Vector3 direction;

	//if (mPhysicsComponentVolumeConvex.get() && mPhysicsComponentVolumeConvex->isInUse())
	//{
	//	mPhysicsComponentVolumeConvex->destroy();
	//	mPhysicsComponentVolumeConvex->create();
	//}

	//ERASE NEXT TWO LINES WHEN FLASHLIGHT IS ATTACHED TO ONY
	//mRenderComponentPositional->setPosition(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition());
	//mRenderComponentPositional->setOrientation(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getOrientation());

	//mPhysicsComponentVolumeConvex->setPosition(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition());
	//if(mCameraManager->getActiveCameraControllerType()==CAMERA_THIRD_PERSON)
	//{
	//	camera=mCameraManager->getActiveCamera();

	//	//mPhysicsComponentVolumeConvex->setOrientation(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getOrientation());
	//	
	//	Ogre::LogManager::getSingleton().logMessage("CAMERA YAW "+Ogre::StringConverter::toString(camera->getOrientation().getYaw().valueDegrees()));	
	//	//if(camera->getOrientation().getYaw().valueDegrees()<0)
	//	//{
	//	//Ogre::Quaternion quat;
	//	//quat.FromAxes(&camera->getDirection());
	//	mPhysicsComponentVolumeConvex->setOrientation(camera->getOrientation());

	//	mPhysicsComponentVolumeConvex->update(elapsedSeconds);
			
		//}
		//else
		//{
		//	mPhysicsComponentVolumeConvex->setOrientation(camera->getOrientation());
		//}

		//direction=mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition()-camera->getPosition();
		//direction.normalise();

		//mRenderComponentLight->setDirection(direction);
	//}
}
void GameObjectFlashLight::setAttackMode(TWeaponMode attackMode)
{
	switch(attackMode)
	{
	case WEAPON_MODE_0:
		mSelectedColour=RED;//red
		break;
	case WEAPON_MODE_1:
		mSelectedColour=BLUE;//blue
		break;
	case WEAPON_MODE_2:
		mSelectedColour=GREEN;//green
		break;
	case WEAPON_MODE_SPECIAL:
		mSelectedColour=WHITE;//white
		break;
	}
	ColourValue diffuseColour=ColourValue::Black;
	diffuseColour.setAsRGBA(mSelectedColour);
	mRenderComponentLight->setDiffuseColor(diffuseColour);
	mRenderComponentLight->setSpecularColor(diffuseColour);
}
void GameObjectFlashLight::switchOn()
{
	mRenderComponentLight->getLight()->setVisible(true);
}
void GameObjectFlashLight::switchOff()
{
	mRenderComponentLight->getLight()->setVisible(false);
}
void GameObjectFlashLight::show()
{
	mRenderComponentEntity->getEntity()->setVisible(true);
}
void GameObjectFlashLight::hide()
{
	mRenderComponentEntity->getEntity()->setVisible(false);
}
int GameObjectFlashLight::getSelectedColour() const
{
	return mSelectedColour;
}
void GameObjectFlashLight::setSelectedColour(int selectedColour)
{
	mSelectedColour=selectedColour;
}

/// Set logic component
void GameObjectFlashLight::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectFlashLight::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectFlashLight::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectFlashLight::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectFlashLight::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectFlashLight::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

TGameObjectFlashLightParameters::TGameObjectFlashLightParameters() : TGameObjectParameters()
{

}

TGameObjectFlashLightParameters::~TGameObjectFlashLightParameters()
{

}