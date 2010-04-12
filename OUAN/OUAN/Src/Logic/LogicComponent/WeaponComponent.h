#ifndef WEAPONCOMPONENTH_H
#define WEAPONCOMPONENTH_H

#include "../../Component/Component.h"
namespace OUAN
{
	typedef std::map<int,GameObjectPtr> TWeaponCollection;
	class WeaponComponent: public Component
	{
	public:
		WeaponComponent(const std::string& type="");
		~WeaponComponent();

		void init(int currentWorld);
		void cleanUp();
		
		void changeActiveWeapon(int world);
		GameObjectPtr getActiveWeapon();

		void setActiveWeaponMode(TWeaponMode activeWeaponMode);
		void updateWeaponMode();
		
		void update(long elapsedTime);

		bool isActiveWeaponInUse() const;
		void switchOn();
		void switchOff();

		int getWeaponPower() const;
		void setWeaponPower(int weaponPower);
		void increaseWeaponPower(int amount=1);
		void decreaseWeaponPower(int amount=1);

		int getMaxWeaponPower() const;
		void setMaxWeaponPower(int maxWeaponPower);

	private:
		TWeaponCollection mAvailableWeapons;
		GameObjectPtr mActiveWeapon;
		bool mActiveWeaponInUse;
		int mWeaponPower;//Atm, use the same value for both weapons
		int mMaxWeaponPower;//set as an attribute to consider 'level-up'
		TWeaponMode mCurrentWeaponMode;
	};
	
	class TWeaponComponentParameters: public TComponentParameters
	{
	public:
		TWeaponComponentParameters();
		~TWeaponComponentParameters();

	};
}

#endif