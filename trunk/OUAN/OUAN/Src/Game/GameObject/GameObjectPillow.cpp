#include "GameObjectPillow.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Graphics/CameraManager/CameraManager.h"

#include "../../Utils/Utils.h"

using namespace OUAN;

GameObjectPillow::GameObjectPillow(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PILLOW)
{
	mLastAttackTime=-1;
}

GameObjectPillow::~GameObjectPillow()
{

}
/// Set logic component
void GameObjectPillow::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectPillow::getLogicComponent()
{
	return mLogicComponent;
}
RenderComponentEntityPtr GameObjectPillow::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectPillow::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectPillow::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectPillow::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectPillow::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectPillow::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectPillow::setPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule)
{
	mPhysicsComponentSimpleCapsule=pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleCapsulePtr GameObjectPillow::getPhysicsComponentSimpleCapsule() const
{
	return mPhysicsComponentSimpleCapsule;
}
PhysicsComponentVolumeBoxPtr GameObjectPillow::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}
void GameObjectPillow::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr physicsComponent)
{
	mPhysicsComponentVolumeBox=physicsComponent;
}

void GameObjectPillow::changeWorld(int world)
{
	/*if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
		if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
		{
			mPhysicsComponentSimpleCapsule->create();
		}

		mRenderComponentEntity->setVisible(true);
		return;
	}
	else
	{
		switch(world)
		{
			case DREAMS:
				if(mLogicComponent->existsInDreams())
				{
					mRenderComponentEntity->setVisible(true);
					if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
					{
						mPhysicsComponentSimpleCapsule->create();
					}
				}
				else
				{
					mRenderComponentEntity->setVisible(false);
					if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
					{
						mPhysicsComponentSimpleCapsule->destroy();
					}
				}		
				break;
			case NIGHTMARES:
				if(mLogicComponent->existsInNightmares())
				{
					mRenderComponentEntity->setVisible(true);
					if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
					{
						mPhysicsComponentSimpleCapsule->create();
					}
				}
				else
				{
					mRenderComponentEntity->setVisible(false);
					if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
					{
						mPhysicsComponentSimpleCapsule->destroy();
					}
				}
				break;
			default:
				break;
		}
	}*/
}

void GameObjectPillow::reset()
{
	GameObject::reset();
}

bool GameObjectPillow::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectPillow::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectPillow::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectPillow::getPhysicsComponent() const
{
	//TODO: Exchange method
	//return getPhysicsComponentSimpleCapsule();
	return getPhysicsComponentVolumeBox();
}

void GameObjectPillow::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectPillow::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectPillow::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectPillow::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
double GameObjectPillow::getLastAttackTime()
{
	return mLastAttackTime;
}
void GameObjectPillow::setLastAttackTime(double lastAttackTime)
{
	mLastAttackTime=lastAttackTime;
}

bool GameObjectPillow::canInitiateAttack()
{
	PillowAttackDataPtr attackData = boost::dynamic_pointer_cast<PillowAttackData>(mAttackComponent->getSelectedAttack());
	bool coolDownPassed=mLastAttackTime<0;
	bool isCombo=attackData->comboDelay>0.0 && mLastAttackTime>=0 && mLastAttackTime<(attackData->cooldownDelay-attackData->comboDelay);
	return (!mParentWeaponComponent->isActiveWeaponInUse() && coolDownPassed) || (mParentWeaponComponent->isActiveWeaponInUse() && isCombo);
}
void GameObjectPillow::beginAttack()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("PILLOW ATTACK LAUNCHED!");
	PillowAttackDataPtr attackData = boost::dynamic_pointer_cast<PillowAttackData>(mAttackComponent->getSelectedAttack());
	if (attackData.get() && attackData->comboDelay>0.0 && mLastAttackTime>0 && mLastAttackTime<=(attackData->cooldownDelay-attackData->comboDelay))
	{
		//NEW COMBO: CHANGE ATTACK
		Ogre::LogManager::getSingletonPtr()->logMessage("COMBO!!");
		setAttack(attackData->nextComboAttack);
		attackData=boost::dynamic_pointer_cast<PillowAttackData>(mAttackComponent->getSelectedAttack());
	}
	Ogre::LogManager::getSingletonPtr()->logMessage("AttackName: "+attackData->attackName);
	if (!mRenderComponentEntity->getEntity()->isVisible())
		mRenderComponentEntity->getEntity()->setVisible(true);
	if (mPhysicsComponentVolumeBox.get())
	{
		if (mPhysicsComponentVolumeBox->isInUse())
			mPhysicsComponentVolumeBox->destroy();
		mPhysicsComponentVolumeBox->create();
	}
	mLastAttackTime=attackData->cooldownDelay;

}
void GameObjectPillow::endAttack()
{
	if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse() && 
		mParentWeaponComponent.get() && mParentWeaponComponent->isActiveWeaponInUse())
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("ATTACK ENDED");
		mPhysicsComponentVolumeBox->destroy();		
		mParentWeaponComponent->setActiveWeaponInUse(false);
		setAttack(getDefaultAttack());
	}
}
void GameObjectPillow::setAttack(const std::string& newAttack)
{
	mAttackComponent->setSelectedAttack(newAttack);
	PillowAttackDataPtr attackData= boost::dynamic_pointer_cast<PillowAttackData>(mAttackComponent->getSelectedAttack());
	if (attackData.get())
	{		
		GameObjectOnyPtr ony = mGameWorldManager->getGameObjectOny();
		mPhysicsComponentVolumeBox->setNxOgreSize(NxOgre::Vec3(attackData->attackRange,attackData->attackRange/4,attackData->attackRange));
		//TODO: radius, etc, should also be modified here
	}
}
std::string GameObjectPillow::getDefaultAttack()
{
	return ATTACK_NAME_BASE;	
}
std::string GameObjectPillow::getAttackName()
{
	if (mAttackComponent.get())
		return mAttackComponent->getSelectedAttack()->attackName;
	return "";
}
int GameObjectPillow::getAttackDamage()
{
	if (mAttackComponent.get())
		return mAttackComponent->getSelectedAttack()->damage;
	return 0;

}
void GameObjectPillow::update(double elapsedSeconds)
{
	if (isEnabled()) //there is no point to updating the flashlight when it's not active
	{
		GameObject::update(elapsedSeconds);
		if (mLastAttackTime>=0.0)
			mLastAttackTime-=elapsedSeconds;
		else 
			if (mParentWeaponComponent.get() && 
			mParentWeaponComponent->getActiveWeapon()->getName().compare(getName())==0 &&
				mParentWeaponComponent->isActiveWeaponInUse())
			endAttack();

		GameObjectOnyPtr ony = mGameWorldManager->getGameObjectOny();
		Ogre::Vector3 pos;
		Ogre::Quaternion orient;
		if (ony.get() && ony->getRenderComponentEntity()->getEntity()->hasSkeleton()
			&& ony->getRenderComponentEntity()->getEntity()->getSkeleton()->hasBone(ATTACH_BONE_NAME))
		{
			Ogre::Entity* ent = ony->getRenderComponentEntity()->getEntity();
			Ogre::Node* bone = ent->getSkeleton()->getBone(ATTACH_BONE_NAME);
			pos=Utils::getNodeWorldPosition(ent,bone);
			orient=Utils::getNodeWorldOrientation(ent,bone);
		}
		else	
		{
			pos=ony->getRenderComponentPositional()->getPosition();
			orient=ony->getRenderComponentPositional()->getOrientation();
		}
		mRenderComponentPositional->setPosition(pos);
		mRenderComponentPositional->setOrientation(orient);

		//if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
		//{
		//	mPhysicsComponentSimpleCapsule->setPosition(mRenderComponentPositional->getPosition());
		//	mPhysicsComponentSimpleCapsule->setOrientation(mRenderComponentPositional->getOrientation());
		//}
		if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
		{
			//mPhysicsComponentVolumeBox->destroy();
			//mPhysicsComponentVolumeBox->create();

			Ogre::Matrix4 onyTransform;
			ony->getRenderComponentPositional()->getSceneNode()->getWorldTransforms(&onyTransform);
			Ogre::Vector3 relPos(0,15,mPhysicsComponentVolumeBox->getNxOgreSize().z/2);

			mPhysicsComponentVolumeBox->setOrientation(ony->getRenderComponentPositional()->getOrientation());
			mPhysicsComponentVolumeBox->setPosition(onyTransform*relPos);
		}
	}
}
bool GameObjectPillow::hasRenderComponentEntity() const
{
	return true;
}
AttackComponentPtr GameObjectPillow::getAttackComponent() const
{
	return mAttackComponent;
}
void GameObjectPillow::setAttackComponent(AttackComponentPtr attackComponent)
{
	mAttackComponent=attackComponent;
}
RenderComponentEntityPtr GameObjectPillow::getEntityComponent() const
{
	return mRenderComponentEntity;
}
WeaponComponentPtr GameObjectPillow::getParentWeaponComponent() const
{
	return mParentWeaponComponent;
}
void GameObjectPillow::setParentWeaponComponent(WeaponComponentPtr parentWeaponComponent) 
{
	mParentWeaponComponent=parentWeaponComponent;
}
bool GameObjectPillow::hasParentWeaponComponent() const
{
	return true;
}
void GameObjectPillow::enable()
{
	GameObject::enable();
	mRenderComponentEntity->setVisible(true);
	//decide what to do with physics component
}
void GameObjectPillow::disable()
{
	GameObject::disable();
	mRenderComponentEntity->setVisible(false);
	if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
		mPhysicsComponentVolumeBox->destroy();
}
//---------
TGameObjectPillowParameters::TGameObjectPillowParameters() : TGameObjectParameters()
{

}

TGameObjectPillowParameters::~TGameObjectPillowParameters()
{

}