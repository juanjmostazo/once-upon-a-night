#include "WeaponComponent.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectFlashLight.h"
#include "../../Game/GameObject/GameObjectPillow.h"
using namespace OUAN;

WeaponComponent::WeaponComponent(const std::string& type)
:Component(COMPONENT_TYPE_WEAPON)
{
	mAvailableWeapons.clear();
	mActiveWeapon.reset();
	mActiveWeaponInUse=false;
}
WeaponComponent::~WeaponComponent()
{
	cleanUp();
}

void WeaponComponent::init(int currentWorld)
{
	GameObjectPtr nullPtr;
	nullPtr.reset();
	mAvailableWeapons[DREAMS]=nullPtr;//TODO: replace with the pillow (//mParent->getGameWorldManager()->getGameObjectPillow())
	mAvailableWeapons[NIGHTMARES]=mParent->getGameWorldManager()->getGameObjectFlashLight();
	
	mActiveWeapon=mAvailableWeapons[currentWorld];
	mActiveWeaponInUse=false;
	
	mMaxWeaponPower=DEFAULT_MAX_WEAPON_POWER;
	mWeaponPower=0;
}
void WeaponComponent::cleanUp()
{
	if (mActiveWeapon.get())
		mActiveWeapon->reset();
	if (!mAvailableWeapons.empty())
		for (TWeaponCollection::iterator it=mAvailableWeapons.begin();
			it!=mAvailableWeapons.end();++it)
		{
			(it->second).reset();
		}
	mAvailableWeapons.clear();
}
void WeaponComponent::changeActiveWeapon(int world)
{
	mActiveWeapon=mAvailableWeapons[world];
	mActiveWeaponInUse=false;
}
void WeaponComponent::setActiveWeaponMode(TWeaponMode activeWeaponMode)
{
	mCurrentWeaponMode=activeWeaponMode;
	if (boost::dynamic_pointer_cast<GameObjectFlashLight>(mActiveWeapon))
	{
		GameObjectFlashLightPtr flashlight = boost::dynamic_pointer_cast<GameObjectFlashLight>(mActiveWeapon);
		flashlight->setAttackMode(activeWeaponMode);
	}
	else if (boost::dynamic_pointer_cast<GameObjectPillow>(mActiveWeapon))
	{
		GameObjectPillowPtr pillow = boost::dynamic_pointer_cast<GameObjectPillow>(mActiveWeapon);
		//pillow->setAttackMode(activeWeaponMode);
	}
}
void WeaponComponent::updateWeaponMode()
{
	setActiveWeaponMode(mCurrentWeaponMode);
}
void WeaponComponent::update(long elapsedTime)
{
	//  ¿?
}
void WeaponComponent::switchOn()
{
	if (!mActiveWeaponInUse)
	{
		mActiveWeaponInUse=true;
		if (boost::dynamic_pointer_cast<GameObjectFlashLight>(mActiveWeapon))
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("USING FLASHLIGHT");
			GameObjectFlashLightPtr flashlight = boost::dynamic_pointer_cast<GameObjectFlashLight>(mActiveWeapon);
			flashlight->switchOn();
		}
		else if (boost::dynamic_pointer_cast<GameObjectPillow>(mActiveWeapon))
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("USING PILLOW");
			GameObjectPillowPtr pillow = boost::dynamic_pointer_cast<GameObjectPillow>(mActiveWeapon);
			//pillow->draw();
		}
	}
}
void WeaponComponent::switchOff()
{
	if (mActiveWeaponInUse)
	{
		mActiveWeaponInUse=false;
		if (boost::dynamic_pointer_cast<GameObjectFlashLight>(mActiveWeapon))
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("STOPPED USING FLASHLIGHT");
			GameObjectFlashLightPtr flashlight = boost::dynamic_pointer_cast<GameObjectFlashLight>(mActiveWeapon);
			flashlight->switchOff();
		}
		else if (boost::dynamic_pointer_cast<GameObjectPillow>(mActiveWeapon))
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("STOPPED USING PILLOW");
			GameObjectPillowPtr pillow = boost::dynamic_pointer_cast<GameObjectPillow>(mActiveWeapon);
			//pillow->sheathe();
		}
	}
}
int WeaponComponent::getWeaponPower() const
{
	return mWeaponPower;
}
void WeaponComponent::setWeaponPower(int weaponPower)
{
	mWeaponPower=weaponPower;
}
void WeaponComponent::increaseWeaponPower(int amount)
{
	mWeaponPower+=amount;
	if (mWeaponPower>mMaxWeaponPower)
		mWeaponPower=mMaxWeaponPower;
}
void WeaponComponent::decreaseWeaponPower(int amount)
{
	mWeaponPower-=amount;
	if (mWeaponPower<0)
		mWeaponPower=0;
}
int WeaponComponent::getMaxWeaponPower() const
{
	return mMaxWeaponPower;
}
void WeaponComponent::setMaxWeaponPower(int maxWeaponPower)
{
	mMaxWeaponPower=maxWeaponPower;
}

GameObjectPtr WeaponComponent::getActiveWeapon()
{
	return mActiveWeapon;
}
bool WeaponComponent::isActiveWeaponInUse() const
{
	return mActiveWeaponInUse;
}
TWeaponComponentParameters::TWeaponComponentParameters()
{

}
TWeaponComponentParameters::~TWeaponComponentParameters()
{

}
