#ifndef LogicComponentEnemyH_H
#define LogicComponentEnemyH_H

#include "LogicComponent.h"
namespace OUAN
{

	class LogicComponentEnemy: public LogicComponent
	{
	public:
		LogicComponentEnemy(const std::string& type="");
		~LogicComponentEnemy();

		void processCollision(GameObjectPtr pGameObject);

		int getNumLives() const;

		int getHealthPoints() const;
		void setHealthPoints(int healthPoints);

		int getInitialHealthPoints() const;
		void setInitialHealthPoints(int healthPoints);

		int getLineOfSight() const;
		void setLineOfSight(int lineOfSight);

		int getAttackRange() const;
		void setAttackRange(int attackRange);

		int getAttackDamage() const;
		void setAttackDamage(int attackDamage);

		int getAttackDelay() const;
		void setAttackDelay(int attackDelay);

		int getColourSensitivityMask() const;
		void setColourSensitivityMask(int colourSensitivityMask);

		/// If applicable, increase the object's health points
		/// @param amount number of HP to increase
		void increaseHP(int amount=1);
		/// If applicable, decrease the object's health points
		/// @param amount number of HP to decrease
		void decreaseHP(int amount=1);

	private:

		/// Health points of the component
		int mHealthPoints;		
		/// Sight range
		int mLineOfSight;

		int mInitialHealthPoints;

		///// Set of available attacks
		//std::vector<TAttackData> mAttackTypes;
		//int mSelectedAttackType;

		std::string mPatrolTrajectoryName;
		//TrajectoryPtr mPatrolTrajectory;

		//
		// TODO [ENHANCEMENT]: 
		// Add support for a variety of attacks
		// This will probably be a must anyway, since some enemies might
		// sport a different behaviour depending on the world
		//

		/// Distance at which the parent object can launch its attack
		int mAttackRange;
		/// Damage inflicted by the attack
		int mAttackDamage;
		/// Minimum delay between two consecutive attacks
		int mAttackDelay;

		/// If the GO presents a nightmare variant and
		/// will take damage when lit by the flashlight, 
		/// This value will hold the colours that the object
		/// will react to.
		int mColourSensitivityMask;	

		/// 'Immunity' time so a single collision is not processed during several ticks
		int mHitRecoveryTime;

	};
	
	class TLogicComponentEnemyParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentEnemyParameters();
		~TLogicComponentEnemyParameters();

		bool hasPatrolTrajectory;

		int healthPoints;
		int lineOfSight;
		int attackDelay;
		int attackRange;
		int attackDamage;
		int colourSensitivityMask;	
	};
}

#endif