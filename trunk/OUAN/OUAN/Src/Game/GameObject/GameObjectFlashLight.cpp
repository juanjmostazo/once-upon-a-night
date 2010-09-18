#include "OUAN_Precompiled.h"

#include "GameObjectFlashLight.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Graphics/CameraManager/CameraManager.h"
#include "../../Graphics/RenderSubsystem.h"
#include "../../Graphics/RenderComponent/RenderComponentLight.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentVolumeConvex.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentWeapon.h"
#include "../../RayCasting/RayCasting.h"
#include "../../Utils/Utils.h"

using namespace OUAN;

GameObjectFlashLight::GameObjectFlashLight(const std::string& name, RenderSubsystemPtr renderSubsystem)
:GameObject(name,GAME_OBJECT_TYPE_FLASHLIGHT)
{
	mRenderSubsystem=renderSubsystem;
	rollAngle=0.0;
	reset();
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

void GameObjectFlashLight::setRenderComponentParticleSystemAttack(RenderComponentParticleSystemPtr pRenderComponentParticleSystemAttack)
{
	mRenderComponentParticleSystemAttack = pRenderComponentParticleSystemAttack;
}

void GameObjectFlashLight::setRenderComponentParticleSystemAttackRed(RenderComponentParticleSystemPtr pRenderComponentParticleSystemAttackRed)
{
	mRenderComponentParticleSystemAttackRed = pRenderComponentParticleSystemAttackRed;
}

void GameObjectFlashLight::setRenderComponentParticleSystemAttackGreen(RenderComponentParticleSystemPtr pRenderComponentParticleSystemAttackGreen)
{
	mRenderComponentParticleSystemAttackGreen = pRenderComponentParticleSystemAttackGreen;
}

void GameObjectFlashLight::setRenderComponentParticleSystemAttackBlue(RenderComponentParticleSystemPtr pRenderComponentParticleSystemAttackBlue)
{
	mRenderComponentParticleSystemAttackBlue = pRenderComponentParticleSystemAttackBlue;
}

RenderComponentParticleSystemPtr GameObjectFlashLight::getRenderComponentParticleSystemAttack() const
{
	return mRenderComponentParticleSystemAttack;
}

RenderComponentParticleSystemPtr GameObjectFlashLight::getRenderComponentParticleSystemAttackRed() const
{
	return mRenderComponentParticleSystemAttackRed;
}

RenderComponentParticleSystemPtr GameObjectFlashLight::getRenderComponentParticleSystemAttackGreen() const
{
	return mRenderComponentParticleSystemAttackGreen;
}

RenderComponentParticleSystemPtr GameObjectFlashLight::getRenderComponentParticleSystemAttackBlue() const
{
	return mRenderComponentParticleSystemAttackBlue;
}

void GameObjectFlashLight::setPhysicsComponentVolumeConvex(PhysicsComponentVolumeConvexPtr pPhysicsComponentVolumeConvex)
{
	mPhysicsComponentVolumeConvex=pPhysicsComponentVolumeConvex;
}

PhysicsComponentVolumeConvexPtr GameObjectFlashLight::getPhysicsComponentVolumeConvex() const
{
	return mPhysicsComponentVolumeConvex;
}

void GameObjectFlashLight::setPhysicsComponentWeapon(PhysicsComponentWeaponPtr pPhysicsComponentWeapon)
{
	mPhysicsComponentWeapon=pPhysicsComponentWeapon;
}

PhysicsComponentWeaponPtr GameObjectFlashLight::getPhysicsComponentWeapon() const
{
	return mPhysicsComponentWeapon;
}

void GameObjectFlashLight::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		//if (mFlashlightDecalComponent.get())
		//{
		//	mFlashlightDecalComponent->destroyProjector();
		//}
		stopAttackParticles();
		mFlashlightDecalComponent->hide();
		break;
	case NIGHTMARES:
		break;
	}
}

void GameObjectFlashLight::changeWorldStarted(int newWorld)
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

void GameObjectFlashLight::changeToWorld(int newWorld, double perc)
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

void GameObjectFlashLight::reset()
{
	GameObject::reset();
	mCurrentColour=RED;
	mTargetColour=RED;
	stopAttackParticles();
}

void GameObjectFlashLight::enable()
{
	GameObject::enable();
	//show();
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
		GameObject::update(elapsedSeconds);

		mCurrentColour=calculateCurrentColour(elapsedSeconds);
		setColour(mCurrentColour);

		GameObjectOnyPtr ony = mGameWorldManager->getGameObjectOny();
		Ogre::Vector3 pos;
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
		mRenderComponentPositional->setOrientation(
			ony->getRenderComponentPositional()->getOrientation()*
			Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y)*
			Ogre::Quaternion(Ogre::Radian(rollAngle),Ogre::Vector3::UNIT_Z));

		rollAngle+=elapsedSeconds*DEFAULT_ROLL_OMEGA;
		//constrain the angle into the range [0..2PI)
		if (rollAngle>=2*PI)
		{
			//The while addition is a safety check for situations
			//where the angle increases above 4*PI, which
			//might happen as a result of a dramatic drop in 
			//the framerate
			while(rollAngle>=2*PI)
			{
				rollAngle-=2*PI;
			}
		}

		if (mPhysicsComponentVolumeConvex.get() && mPhysicsComponentVolumeConvex->isInUse())
		{
			//OUCH! BUT FOR THE MOMENT WE LEAVE IT LIKE THIS as there's an error getting the orientation if not done that way
			//mPhysicsComponentVolumeConvex->destroy();
			//mPhysicsComponentVolumeConvex->create();
			mPhysicsComponentVolumeConvex->setPosition(pos);
			mPhysicsComponentVolumeConvex->setOrientation(ony->getRenderComponentPositional()->getOrientation()*Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y));
		}

		if (mPhysicsComponentWeapon.get() && mPhysicsComponentWeapon->isInUse())
		{
			mPhysicsComponentWeapon->setPosition(pos);
			Vector3 nextMovement;
			nextMovement=mLastBonePosition-pos+ony->getPhysicsComponentCharacterOny()->getOuternMovement();
			nextMovement.normalise();
			mPhysicsComponentWeapon->setOuternMovement(nextMovement);
			mPhysicsComponentWeapon->setCyclicCharacter(nextMovement==Vector3::ZERO);

			//Logger::getInstance()->log("setOuternMovement " + Ogre::StringConverter::toString(pos-mLastBonePosition));
			//mPhysicsComponentWeapon->setOrientation(orient);
		}
		mLastBonePosition=pos;
	}
}

void GameObjectFlashLight::setColour(int colour)
{
		ColourValue ogreColour;
		ogreColour.setAsRGBA(colour);
		mRenderComponentLight->setDiffuseColor(ogreColour);
		mRenderComponentLight->setSpecularColor(ogreColour);
		//TODO: radius, etc, should also be modified here
		if (mFlashlightDecalComponent.get())
		{
			mFlashlightDecalComponent->changeColour(colour);
			if (mFlashlightDecalComponent->isVisible())
			{	
				mFlashlightDecalComponent->hide();
				mFlashlightDecalComponent->show();
			}
		}
		if (mConeEntity)
		{
			applyTintColour(colour);
		}
}

int GameObjectFlashLight::calculateCurrentColour(double elapsedSeconds)
{
	int nextColour;

	ColourValue ogreTargetColour;
	ColourValue ogreCurrentColour;
	ColourValue ogreNextColour;
	double incr;

	ogreTargetColour.setAsRGBA(mTargetColour);
	ogreCurrentColour.setAsRGBA(mCurrentColour);
	incr=mGameWorldManager->CHANGE_FLASHLIGHT_COLOUR_SPEED*elapsedSeconds;

	ogreNextColour.r=ogreCurrentColour.r+(ogreTargetColour.r-ogreCurrentColour.r)*incr;
	ogreNextColour.g=ogreCurrentColour.g+(ogreTargetColour.g-ogreCurrentColour.g)*incr;
	ogreNextColour.b=ogreCurrentColour.b+(ogreTargetColour.b-ogreCurrentColour.b)*incr;
	ogreNextColour.a=1;

	if(Ogre::Math::Abs(ogreTargetColour.r-ogreCurrentColour.r)<incr &&
		Ogre::Math::Abs(ogreTargetColour.g-ogreCurrentColour.g)<incr &&
		Ogre::Math::Abs(ogreTargetColour.b-ogreCurrentColour.b)<incr)
	{
		nextColour=mTargetColour;
	}
	else
	{
		nextColour=ogreNextColour.getAsRGBA();
	}

	return nextColour;
}	

void GameObjectFlashLight::setAttack(const std::string& newAttack)
{
	mAttackComponent->setSelectedAttack(newAttack);
	FlashlightAttackDataPtr attackData= BOOST_PTR_CAST(FlashlightAttackData,
		mAttackComponent->getSelectedAttack());

	if (attackData.get())
	{
		mTargetColour=attackData->rgb;
	}

	getRenderComponentParticleSystemAttackRed()->stop();
	getRenderComponentParticleSystemAttackGreen()->stop();
	getRenderComponentParticleSystemAttackBlue()->stop();
	switch (mTargetColour)
	{
	case RED:
		getRenderComponentParticleSystemAttackRed()->start();
		break;

	case GREEN:
		getRenderComponentParticleSystemAttackGreen()->start();
		break;

	case BLUE:
		getRenderComponentParticleSystemAttackBlue()->start();
		break;

	case WHITE:
		getRenderComponentParticleSystemAttackRed()->start();
		getRenderComponentParticleSystemAttackGreen()->start();
		getRenderComponentParticleSystemAttackBlue()->start();
		break;
	}
}

void GameObjectFlashLight::startAttackParticles()
{
	mRenderComponentParticleSystemAttack->start();
}

void GameObjectFlashLight::stopAttackParticles()
{
	if(mRenderComponentParticleSystemAttack.get())
	{
		mRenderComponentParticleSystemAttack->stop();
	}
	
	if(mRenderComponentParticleSystemAttackRed.get())
	{
		mRenderComponentParticleSystemAttackRed->stop();
	}
	if(mRenderComponentParticleSystemAttackGreen.get())
	{
		mRenderComponentParticleSystemAttackGreen->stop();
	}
	if(mRenderComponentParticleSystemAttackBlue.get())
	{
		mRenderComponentParticleSystemAttackBlue->stop();
	}
}

void GameObjectFlashLight::switchOn()
{
	//Logger::getInstance()->log("SWITCH ON");

	std::stringstream colourStream("");
	colourStream<<GameObjectFlashLight::getColourName(getColour());
	mRenderComponentLight->getLight()->setVisible(true);
	if (mPhysicsComponentVolumeConvex.get() && !mPhysicsComponentVolumeConvex->isInUse())
	{
		mPhysicsComponentVolumeConvex->create();
	}

	if (mPhysicsComponentWeapon.get() && !mPhysicsComponentWeapon->isInUse())
	{
		mPhysicsComponentWeapon->startAttack();
	}

	if (mFlashlightDecalComponent.get())
	{
		mFlashlightDecalComponent->show();
	}

	mConeEntity->setVisible(true);
	mCurrentColour=mTargetColour;
	setColour(mTargetColour);

	startAttackParticles();
}

void GameObjectFlashLight::switchOff()
{
	//Logger::getInstance()->log("SWITCH FF");

	mRenderComponentLight->getLight()->setVisible(false);
	mConeEntity->setVisible(false);

	if (mPhysicsComponentVolumeConvex.get() && mPhysicsComponentVolumeConvex->isInUse())
	{
		mPhysicsComponentVolumeConvex->destroy();
	}

	if (mPhysicsComponentWeapon.get() && mPhysicsComponentWeapon->isInUse())
	{
		mPhysicsComponentWeapon->endAttack();
	}

	if (mParentWeaponComponent.get())
	{
		mParentWeaponComponent->setActiveWeaponInUse(false);
	}

	if (mFlashlightDecalComponent.get())
	{
		mFlashlightDecalComponent->hide();
	}

	if (mAttackComponent->getSelectedAttack().get())
	{
		FlashlightAttackDataPtr attackData = 
			BOOST_PTR_CAST(FlashlightAttackData,mAttackComponent->getSelectedAttack());
		AttackEndedEventPtr evt = AttackEndedEventPtr(new AttackEndedEvent(attackData->attackName,shared_from_this()));
		mGameWorldManager->addEvent(evt);
	}

	mRenderComponentParticleSystemAttack->stop();

	mCurrentColour=mTargetColour;
}

void GameObjectFlashLight::show()
{
	//mRenderComponentEntity->getEntity()->setVisible(true);
	//mConeEntity->setVisible(true);
	Logger::getInstance()->log("LIGHT CONE NOW VISIBLE -theoretically -_-");
}

void GameObjectFlashLight::hide()
{
	//mRenderComponentEntity->getEntity()->setVisible(false);
	mConeEntity->setVisible(false);
	mRenderComponentParticleSystemAttack->stop();
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


void GameObjectFlashLight::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_PORTAL)==0)
	{
		Logger::getInstance()->log("FLASHLIGHT COLLISION " + pGameObject->getName());
	}
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
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

int GameObjectFlashLight::getColour()
{
	FlashlightAttackDataPtr attackData=BOOST_PTR_CAST(FlashlightAttackData,mAttackComponent->getSelectedAttack());
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

WeaponComponentPtr GameObjectFlashLight::getParentWeaponComponent() const
{
	return mParentWeaponComponent;
}
void GameObjectFlashLight::setParentWeaponComponent(WeaponComponentPtr parentWeaponComponent) 
{
	mParentWeaponComponent=parentWeaponComponent;
}
bool GameObjectFlashLight::hasParentWeaponComponent() const
{
	return true;
}

bool GameObjectFlashLight::canInitiateAttack()
{	
	return (!mParentWeaponComponent->isActiveWeaponInUse());
}
int GameObjectFlashLight::getAttackDamage() const
{
	if (mAttackComponent.get())
		return mAttackComponent->getSelectedAttack()->damage;
	return 0;
}
std::string GameObjectFlashLight::getColourName(int colour)
{
	switch(colour)
	{
	case RED:
		return "RED";
	case GREEN:
		return "GREEN";
	case BLUE:
		return "BLUE";
	case WHITE:
		return "WHITE";
	default:
		return "";
	}
}
void GameObjectFlashLight::applyTintColour(int colour)
{
	Ogre::ColourValue tint;
	tint.setAsRGBA(colour);
	Ogre::MaterialPtr mat=Ogre::MaterialManager::getSingleton().getByName(CONE_MATERIAL_NAME);
	Ogre::TextureUnitState* tex= mat->getTechnique(0)->getPass(0)->getTextureUnitState(0);
	if (tex)
	{
		tex->setColourOperationEx(Ogre::LBX_MODULATE,Ogre::LBS_MANUAL,Ogre::LBS_CURRENT,tint);
	}
}
void GameObjectFlashLight::createProjector(TGameObjectContainer* objs)
{
	//if (!mFlashlightDecalComponent)
	//{
	//	mFlashlightDecalComponent= ProjectiveDecalPtr(new ProjectiveDecal());
	//}
	//TDecalParams decalSettings;
	//decalSettings.filterTextureName=FLASHLIGHT_DECAL_FILTER_TEX_NAME;
	//decalSettings.projectorName=FLASHLIGHT_DECAL_PROJECTOR_NAME;
	//decalSettings.projectorNode=getRenderComponentPositional()->getSceneNode();
	//decalSettings.projectorOffset=Ogre::Vector3::ZERO;
	//decalSettings.textureName=FLASHLIGHT_DECAL_TEX_NAME;
	//decalSettings.tintColour=getColour();

	//mFlashlightDecal->createProjector(decalSettings,mRenderSubsystem->getSceneManager(),objs);
}
RenderComponentDecalPtr GameObjectFlashLight::getDecalComponent() const
{
	return mFlashlightDecalComponent;
}
void GameObjectFlashLight::setDecalComponent(RenderComponentDecalPtr decalComponent)
{
	mFlashlightDecalComponent=decalComponent;
}
RenderComponentEntityPtr GameObjectFlashLight::getConeEntity() const
{
	return mConeEntity;
}
void GameObjectFlashLight::setConeEntity(RenderComponentEntityPtr coneEntity)
{
	mConeEntity=coneEntity;
}

void GameObjectFlashLight::loadDecalMaterials(TGameObjectContainer& mGameObjects)
{
	mFlashlightDecalComponent->loadMaterials(mGameObjects);
}
void GameObjectFlashLight::unloadDecalMaterials()
{
	mFlashlightDecalComponent->unloadMaterials();
}
bool GameObjectFlashLight::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectFlashLight::getLogicComponent() const
{
	return mLogicComponent;
}
//---
TGameObjectFlashLightParameters::TGameObjectFlashLightParameters() : TGameObjectParameters()
{

}

TGameObjectFlashLightParameters::~TGameObjectFlashLightParameters()
{

}