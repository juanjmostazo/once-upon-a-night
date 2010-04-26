#ifndef WEAPONCOMPONENTH_H
#define WEAPONCOMPONENTH_H

#include "../../Component/Component.h"
namespace OUAN
{
	typedef std::map<std::string,GameObjectPtr> TWeaponCollection;
	class WeaponComponent: public Component
	{
	public:
		WeaponComponent(const std::string& type="");
		~WeaponComponent();

		void initWeapons(std::vector<std::string> weapons, const std::string& activeWeapon);

		void cleanUp();
		
		void changeActiveWeapon(const std::string& newWeapon);
		GameObjectPtr getActiveWeapon();
		void initActiveWeapon();

		void setAttackType(const std::string& newAttack);
		void updateAttackType();
		
		void update(long elapsedTime);

		bool isActiveWeaponInUse() const;
		void setActiveWeaponInUse(bool activeWeaponInUse);
		void switchOn();
		void switchOff();

		int getWeaponPower() const;
		void setWeaponPower(int weaponPower);
		void increaseWeaponPower(int amount=1);
		void decreaseWeaponPower(int amount=1);

		int getMaxWeaponPower() const;
		void setMaxWeaponPower(int maxWeaponPower);

	private:
		//TWeaponCollection mAvailableWeapons;
		GameObjectPtr mActiveWeapon;
		bool mActiveWeaponInUse;
		std::string mActiveWeaponName;
		int mWeaponPower;//Atm, use the same value for both weapons
		int mMaxWeaponPower;//set as an attribute to consider 'level-up'
		std::string mCurrentWeaponAttack;
		// We can't instance the GameObjects during the component initialization,
		// since in principle it is possible that they haven't been created yet.
		// For that reason, we'll keep their names temporarily until 
		std::vector<std::string> mWeaponNames;
	};
	
	class TWeaponComponentParameters: public TComponentParameters
	{
	public:
		TWeaponComponentParameters();
		~TWeaponComponentParameters();
		std::vector<std::string> mWeaponNames;
		std::string mSelectedWeapon;

	};
}

#endif