#include "WeaponComponent.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectFlashLight.h"
#include "../../Game/GameObject/GameObjectPillow.h"
#include <algorithm>
using namespace OUAN;

WeaponComponent::WeaponComponent(const std::string& type)
:Component(COMPONENT_TYPE_WEAPON)
{
	mWeaponNames.clear();
	mActiveWeapon.reset();
	mActiveWeaponInUse=false;
}
WeaponComponent::~WeaponComponent()
{
	cleanUp();
}

void WeaponComponent::initWeapons(std::vector<std::string> weaponNames, const std::string& activeWeapon)
{	
	mWeaponNames.clear();
	for (std::vector<std::string>::iterator it=weaponNames.begin();it!=weaponNames.end();++it)
	{
			mWeaponNames.push_back(*it);
	}
	GameObjectPtr nullPtr;
	nullPtr.reset();
	mActiveWeapon=nullPtr;
	mActiveWeaponName=activeWeapon;
	mActiveWeaponInUse=false;

	mMaxWeaponPower=DEFAULT_MAX_WEAPON_POWER;
	mWeaponPower=0;
}
void WeaponComponent::initActiveWeapon()
{
	if (!mActiveWeaponName.empty())
	{
		changeActiveWeapon(mActiveWeaponName);
	}
}
void WeaponComponent::cleanUp()
{
	if (mActiveWeapon.get())
		mActiveWeapon->reset();
	mWeaponNames.clear();
}
void WeaponComponent::changeActiveWeapon(const std::string& newWeapon)
{
	GameObjectPtr oldActiveWeapon=mActiveWeapon;
	mActiveWeaponInUse=false;
	mActiveWeapon.reset();
	if (std::find(mWeaponNames.begin(),mWeaponNames.end(),newWeapon)!=mWeaponNames.end())
	{
		mActiveWeapon=mParent->getGameWorldManager()->getObject(newWeapon);
		if (mActiveWeapon.get())
		{
			mActiveWeapon->enable();
			mActiveWeapon->setAttack(mActiveWeapon->getDefaultAttack());
		}
	}
	if (oldActiveWeapon.get())
	{
		oldActiveWeapon->disable();
		oldActiveWeapon->reset();
	}
}

void WeaponComponent::setAttackType(const std::string& newAttack)
{
	if (mActiveWeapon.get() && !newAttack.empty())
	{
		mCurrentWeaponAttack=newAttack;
		mActiveWeapon->setAttack(mCurrentWeaponAttack);
	}
}

void WeaponComponent::updateAttackType()
{
	if (mActiveWeapon.get())
	{
		std::string defaultAttack=mActiveWeapon->getDefaultAttack();
		setAttackType(defaultAttack);
	}
}
void WeaponComponent::update(long elapsedTime)
{
	//  ¿?
}
void WeaponComponent::switchOn()
{
	if (mActiveWeapon.get() && !mActiveWeaponInUse)
	{
		mActiveWeaponInUse=true;
		mActiveWeapon->beginAttack();
	}
}
void WeaponComponent::switchOff()
{
	if (mActiveWeapon.get() && mActiveWeaponInUse)
	{
		mActiveWeaponInUse=false;
		mActiveWeapon->switchOff();
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
