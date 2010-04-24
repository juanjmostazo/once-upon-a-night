#include "GameObjectFlashLight.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Graphics/CameraManager/CameraManager.h"
#include "../../Graphics/RenderComponent/RenderComponentLight.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeConvex.h"
#include "../../RayCasting/RayCasting.h"
#include "../../Utils/Utils.h"

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

PhysicsComponentVolumeConvexPtr GameObjectFlashLight::getPhysicsComponentVolumeConvex() const
{
	return mPhysicsComponentVolumeConvex;
}

void GameObjectFlashLight::changeWorld(int world)
{
	//The flashlight's operation mode concerning a world change is managed
	//by Ony (i.e, on a change to dreams Ony changes his active weapon to the pillow,
	// and to the flashlight on a change to nightmares)
	//Theoretically, the weapon shouldn't care about the world it is in 
	
	//switch(world)
	//{
	//case DREAMS:
	//	//PROVISIONAL
	//	mRenderComponentLight->getLight()->setVisible(false);
	//	if (mPhysicsComponentVolumeConvex.get() && mPhysicsComponentVolumeConvex->isInUse())
	//	{
	//		mPhysicsComponentVolumeConvex->destroy();
	//	}
	//	break;
	//case NIGHTMARES:
	//	//PROVISIONAL
	//	mRenderComponentLight->getLight()->setVisible(true);
	//	if (mPhysicsComponentVolumeConvex.get() && !mPhysicsComponentVolumeConvex->isInUse())
	//	{
	//		mPhysicsComponentVolumeConvex->create();
	//	}
	//	break;
	//default:
	//	break;
	//}
}

void GameObjectFlashLight::reset()
{
	GameObject::reset();
}
void GameObjectFlashLight::enable()
{
	GameObject::enable();
	show();
	mRenderComponentLight->getLight()->setVisible(false);
}
void GameObjectFlashLight::disable()
{
	GameObject::disable();
	hide();
	switchOff();
}

bool GameObjectFlashLight::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectFlashLight::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectFlashLight::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectFlashLight::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeConvex();
}

void GameObjectFlashLight::update(double elapsedSeconds)
{
	if (isEnabled()) //there is no point to updating the flashlight when it's not active
	{
		Ogre::Camera * camera;
		Vector3 direction;

		GameObject::update(elapsedSeconds);

		camera=mCameraManager->getActiveCamera();

		if(mCameraManager->getActiveCameraControllerType()==CAMERA_THIRD_PERSON)
		{
			//mRenderComponentPositional->setPosition(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition());
			//mRenderComponentPositional->setOrientation(camera->getOrientation());
			GameObjectOnyPtr ony = mGameWorldManager->getGameObjectOny();
			Ogre::Vector3 pos;
			Ogre::Quaternion quat;
			if (ony.get() && ony->getRenderComponentEntity()->getEntity()->hasSkeleton()
				&& ony->getRenderComponentEntity()->getEntity()->getSkeleton()->hasBone(ATTACH_BONE_NAME))
			{
				Ogre::Entity* ent = ony->getRenderComponentEntity()->getEntity();
				Ogre::Node* bone = ent->getSkeleton()->getBone(ATTACH_BONE_NAME);
				pos=Utils::getNodeWorldPosition(ent,bone);
			}
			else
			{
				pos=ony->getRenderComponentPositional()->getPosition();
			}

			mRenderComponentPositional->setPosition(pos);			
			mRenderComponentPositional->setOrientation(camera->getOrientation()*Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3::UNIT_Y));

			if (mPhysicsComponentVolumeConvex.get() && mPhysicsComponentVolumeConvex->isInUse())
			{
				//OUCH! BUT FOR THE MOMENT WE LEAVE IT LIKE THIS as there's an error getting the orientation if not done that way
				mPhysicsComponentVolumeConvex->destroy();
				mPhysicsComponentVolumeConvex->create();

				//mPhysicsComponentVolumeConvex->setPosition(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition());
				mPhysicsComponentVolumeConvex->setPosition(mRenderComponentPositional->getPosition());

				camera=mCameraManager->getActiveCamera();
				mPhysicsComponentVolumeConvex->setOrientation(camera->getOrientation());
				//mPhysicsComponentVolumeConvex->setOrientation(mRenderComponentPositional->getOrientation());
			}
		}

		//ACHTUNG: The light's not in sync with the flashlight model, but with ony instead!!!
		mLightPositionalComponent->setPosition(mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition());

		direction=mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition()-camera->getPosition();
		direction.normalise();

		mRenderComponentLight->setDirection(direction);

	}
}
void GameObjectFlashLight::setAttack(const std::string& newAttack)
{
	mAttackComponent->setSelectedAttack(newAttack);
	FlashlightAttackDataPtr attackData= boost::dynamic_pointer_cast<FlashlightAttackData>(mAttackComponent->getSelectedAttack());
	if (attackData.get())
	{
		ColourValue newColour;
		newColour.setAsRGBA(attackData->rgb);
		mRenderComponentLight->setDiffuseColor(newColour);
		mRenderComponentLight->setSpecularColor(newColour);
		//TODO: radius, etc, should also be modified here
	}

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
	if (mPhysicsComponentVolumeConvex.get() && !mPhysicsComponentVolumeConvex->isInUse())
	{
		mPhysicsComponentVolumeConvex->create();
	}
}
void GameObjectFlashLight::switchOff()
{
	mRenderComponentLight->getLight()->setVisible(false);
	if (mPhysicsComponentVolumeConvex.get() && mPhysicsComponentVolumeConvex->isInUse())
	{
		mPhysicsComponentVolumeConvex->destroy();
	}
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
AttackComponentPtr GameObjectFlashLight::getAttackComponent() const
{
	return mAttackComponent;
}
void GameObjectFlashLight::setAttackComponent(AttackComponentPtr attackComponent)
{
	mAttackComponent=attackComponent;
}
std::string GameObjectFlashLight::translateWeaponMode(TWeaponMode weaponMode)
{
	switch (weaponMode)
	{
		case WEAPON_MODE_0:
			return ATTACK_NAME_RED;
		case WEAPON_MODE_1:
			return ATTACK_NAME_BLUE;
		case WEAPON_MODE_2:
			return ATTACK_NAME_GREEN;
		case WEAPON_MODE_SPECIAL:
			return ATTACK_NAME_WHITE;
		default:
			return "";
	}
}
void GameObjectFlashLight::beginAttack()
{
	switchOn();
}
std::string GameObjectFlashLight::getDefaultAttack()
{
	return ATTACK_NAME_RED;
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
int GameObjectFlashLight::getColour()
{
	FlashlightAttackDataPtr attackData=boost::dynamic_pointer_cast<FlashlightAttackData>(mAttackComponent->getSelectedAttack());
	if (attackData && attackData.get())
	{
		return attackData->rgb;
	}
	return 0;
}
bool GameObjectFlashLight::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectFlashLight::getEntityComponent() const
{
	return mRenderComponentEntity;
}
TGameObjectFlashLightParameters::TGameObjectFlashLightParameters() : TGameObjectParameters()
{

}

TGameObjectFlashLightParameters::~TGameObjectFlashLightParameters()
{

}