#include "OUAN_Precompiled.h"

#include "GameObjectPillow.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Graphics/CameraManager/CameraManager.h"

#include "../../Utils/Utils.h"
#include "../../Event/EventDefs.h"

using namespace OUAN;

GameObjectPillow::GameObjectPillow(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PILLOW)
{
	mLastAttackTime=-1;
	mLastBonePosition=Vector3::ZERO;
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

void GameObjectPillow::setRenderComponentParticleSystemAttack(RenderComponentParticleSystemPtr pRenderComponentParticleSystemAttack)
{
	mRenderComponentParticleSystemAttack = pRenderComponentParticleSystemAttack;
}

RenderComponentParticleSystemPtr GameObjectPillow::getRenderComponentParticleSystemAttack() const
{
	return mRenderComponentParticleSystemAttack;
}

void GameObjectPillow::setPhysicsComponentWeapon(PhysicsComponentWeaponPtr pPhysicsComponentWeapon)
{
	mPhysicsComponentWeapon=pPhysicsComponentWeapon;
}

PhysicsComponentWeaponPtr GameObjectPillow::getPhysicsComponentWeapon() const
{
	return mPhysicsComponentWeapon;
}

void GameObjectPillow::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectPillow::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectPillow::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
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
	return getPhysicsComponentWeapon();
}

void GameObjectPillow::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	//if(pGameObject->getName().compare("ony#0")!=0)
	//{
	//	Logger::getInstance()->log("PILLOW COLLISION " + pGameObject->getName());
	//}
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
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
	PillowAttackDataPtr attackData = BOOST_PTR_CAST(PillowAttackData,mAttackComponent->getSelectedAttack());
	bool coolDownPassed=mLastAttackTime<0;
	bool isCombo=attackData->comboDelay>0.0 && mLastAttackTime>=0 && mLastAttackTime<(attackData->cooldownDelay-attackData->comboDelay);
	return (!mParentWeaponComponent->isActiveWeaponInUse() && coolDownPassed) || (mParentWeaponComponent->isActiveWeaponInUse() && isCombo);
}

void GameObjectPillow::beginAttack()
{
	PillowAttackDataPtr attackData = BOOST_PTR_CAST(PillowAttackData,
		mAttackComponent->getSelectedAttack());
	std::stringstream textMsg("");

	if (attackData.get() && attackData->comboDelay>0.0 && mLastAttackTime>0 && mLastAttackTime<=(attackData->cooldownDelay-attackData->comboDelay))
	{
		//NEW COMBO: CHANGE ATTACK
		//Logger::getInstance()->log("COMBO!!");
		setAttack(attackData->nextComboAttack);
		attackData=BOOST_PTR_CAST(PillowAttackData,mAttackComponent->getSelectedAttack());
		textMsg<<"It's a COMBO! ";
	}

	//Logger::getInstance()->log("AttackName: "+attackData->attackName);
	textMsg<<attackData->attackName<<", "<<attackData->damage<<" HP";
	displayText(textMsg.str());

	if (!mRenderComponentEntity->getEntity()->isVisible())
	{
		//mRenderComponentEntity->getEntity()->setVisible(true);
	}

	if (mPhysicsComponentWeapon.get())
	{
		mPhysicsComponentWeapon->startAttack();
	}

	mLastAttackTime=attackData->cooldownDelay;
}

void GameObjectPillow::endAttack()
{
	
	if (mPhysicsComponentWeapon.get() && mPhysicsComponentWeapon->isInUse() && 
		mParentWeaponComponent.get() && mParentWeaponComponent->isActiveWeaponInUse())
	{
		PillowAttackDataPtr attackData = BOOST_PTR_CAST(PillowAttackData,
			mAttackComponent->getSelectedAttack());
		AttackEndedEventPtr evt = AttackEndedEventPtr(new AttackEndedEvent(attackData->attackName, shared_from_this()));
			mGameWorldManager->addEvent(evt);

		mPhysicsComponentWeapon->endAttack();		
		//mRenderComponentEntity->getEntity()->setVisible(false);

		setAttack(getDefaultAttack());
		mParentWeaponComponent->setActiveWeaponInUse(false);
	}


}

void GameObjectPillow::setAttack(const std::string& newAttack)
{
	mAttackComponent->setSelectedAttack(newAttack);
	PillowAttackDataPtr attackData= BOOST_PTR_CAST(PillowAttackData,
		mAttackComponent->getSelectedAttack());
	if (attackData.get())
	{		
		GameObjectOnyPtr ony = mGameWorldManager->getGameObjectOny();
		//mPhysicsComponentVolumeBox->setNxOgreSize(NxOgre::Vec3(attackData->attackRange,attackData->attackRange/4,attackData->attackRange));
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
	{
		return mAttackComponent->getSelectedAttack()->attackName;
	}

	return "";
}

int GameObjectPillow::getAttackDamage()
{
	if (mAttackComponent.get())
	{
		return mAttackComponent->getSelectedAttack()->damage;
	}

	return 0;

}

void GameObjectPillow::update(double elapsedSeconds)
{
	if (isEnabled()) //there is no point to updating the flashlight when it's not active
	{
		GameObject::update(elapsedSeconds);

		if (mLastAttackTime>=0.0)
		{
			mLastAttackTime-=elapsedSeconds;
		}
		else if(mParentWeaponComponent.get() && 
				mParentWeaponComponent->getActiveWeapon()->getName().compare(getName())==0 &&
				mParentWeaponComponent->isActiveWeaponInUse())
		{
			endAttack();
		}	

		GameObjectOnyPtr ony = mGameWorldManager->getGameObjectOny();
		Ogre::Vector3 pos;
		Ogre::Quaternion orient;

		if (ony.get() && ony->getRenderComponentEntity()->getEntity()->hasSkeleton() &&
			ony->getRenderComponentEntity()->getEntity()->getSkeleton()->hasBone(ATTACH_BONE_NAME))
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

	if (mPhysicsComponentWeapon.get() && mPhysicsComponentWeapon->isInUse())
	{
		mPhysicsComponentWeapon->setPosition(pos);
		Vector3 nextMovement;
		nextMovement=mLastBonePosition-pos;
		nextMovement.normalise();
		mPhysicsComponentWeapon->setOuternMovement(nextMovement);
		//Logger::getInstance()->log("setOuternMovement " + Ogre::StringConverter::toString(pos-mLastBonePosition));
		//mPhysicsComponentWeapon->setOrientation(orient);
	}

	mLastBonePosition=pos;

	//	//if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
	//	//{
	//	//	mPhysicsComponentSimpleCapsule->setPosition(mRenderComponentPositional->getPosition());
	//	//	mPhysicsComponentSimpleCapsule->setOrientation(mRenderComponentPositional->getOrientation());
	//	//}
	//	if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
	//	{
	//		//mPhysicsComponentVolumeBox->destroy();
	//		//mPhysicsComponentVolumeBox->create();

	//		Ogre::Matrix4 onyTransform;
	//		ony->getRenderComponentPositional()->getSceneNode()->getWorldTransforms(&onyTransform);
	//		Ogre::Vector3 relPos(0,7,mPhysicsComponentVolumeBox->getNxOgreSize().z/2);

	//		mPhysicsComponentVolumeBox->setOrientation(ony->getRenderComponentPositional()->getOrientation());
	//		mPhysicsComponentVolumeBox->setPosition(onyTransform*relPos);
	//	}
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

bool GameObjectPillow::isWorthUpdatingPhysicsComponents()
{
	return true;
}

bool GameObjectPillow::isWorthUpdatingLogicComponents()
{
	return true;
}	

void GameObjectPillow::enable()
{
	GameObject::enable();
	//mRenderComponentEntity->setVisible(true);
	//decide what to do with physics component
}

void GameObjectPillow::disable()
{
	GameObject::disable();
	mRenderComponentEntity->setVisible(false);

	if (mPhysicsComponentWeapon.get() && mPhysicsComponentWeapon->isInUse())
	{
		mPhysicsComponentWeapon->endAttack();
	}
		
}
void GameObjectPillow::startAttackParticles()
{
	GameObjectOnyPtr ony = BOOST_PTR_CAST(GameObjectOny,
		mParentWeaponComponent->getParent());
	if (ony.get() && ony->getRenderComponentEntity()->getEntity()->hasSkeleton() &&
		ony->getRenderComponentEntity()->getEntity()->getSkeleton()->hasBone(ATTACH_BONE_NAME))
	{
		Ogre::Entity* ent = ony->getRenderComponentEntity()->getEntity();
		Ogre::Node* bone = ent->getSkeleton()->getBone(ATTACH_BONE_NAME);
		Ogre::Vector3 pos = Utils::getNodeWorldPosition(ent,bone);
		mRenderComponentParticleSystemAttack->start(pos);
	}
}
bool GameObjectPillow::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectPillow::getLogicComponentInstance() const
{
	return mLogicComponent;
}
//---------
TGameObjectPillowParameters::TGameObjectPillowParameters() : TGameObjectParameters()
{

}

TGameObjectPillowParameters::~TGameObjectPillowParameters()
{

}