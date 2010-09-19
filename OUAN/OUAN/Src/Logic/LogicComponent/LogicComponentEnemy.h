#ifndef LogicComponentEnemyH_H
#define LogicComponentEnemyH_H

#include "LogicComponent.h"
namespace OUAN
{
	const int COLOUR_FLAG_RED=0x1;
	const int COLOUR_FLAG_GREEN=0x2;
	const int COLOUR_FLAG_BLUE=0x4;
	class LogicComponentEnemy: public LogicComponent
	{
	public:
		LogicComponentEnemy(const std::string& type="");
		~LogicComponentEnemy();

		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);

		int getNumLives() const;

		int getHealthPoints() const;
		void setHealthPoints(int healthPoints);

		int getInitialHealthPoints() const;
		void setInitialHealthPoints(int healthPoints);

		int getLineOfSight() const;
		void setLineOfSight(int lineOfSight);

		int getEnemyTypeLUA() const;
		EnemyType getEnemyType() const;
		void setEnemyType(EnemyType enemyType);

		bool isFlying() const;

		int getColourSensitivityMask() const;
		void setColourSensitivityMask(int colourSensitivityMask);
		int getMaskValueFromColour(int colour);

		/// If applicable, increase the object's health points
		/// @param amount number of HP to increase
		void increaseHP(int amount=1);
		/// If applicable, decrease the object's health points
		/// @param amount number of HP to decrease
		void decreaseHP(int amount=1);

		void update(double elapsedTime);

		bool hasBeenHit() const;
		void setHasBeenHit(bool hasBeenHit);
		bool hasDied() const;
		void setHasDied(bool hasDied);

		bool isAlertFinished() const;
		void setAlertFinished(bool alert);
		bool isSurpriseFinished() const;
		void setSurpriseFinished(bool surprise);
		bool isFalseAlarmFinished() const;
		void setFalseAlarmFinished(bool falseAlarm);
		bool isCallToArmsFinished() const;
		void setCallToArmsFinished(bool callToArms);
		bool isTiredFinished() const;
		void setTiredFinished(bool tired);
		bool isIdle1Finished() const;
		void setIdle1Finished(bool idle1);
		bool isAttackFinished() const;
		void setAttackFinished(bool attackFinished);

		bool hasPatrolTrajectory() const;

		int getPreviousState() const;
		double getMeleeRange() const;

		int getNeighboursInRange(double range) const;
		bool callWasHeard() const;
		void setCallWasHeard(bool callWasHeard);
		
		bool hasHeardCall() const;
		void setHasHeardCall(bool hasHeardCall);

		bool isStatueEnabled() const;
		void setStatueEnabled(bool statueEnabled);

		bool isFlyingEnabled() const;
		void setFlyingEnabled(bool flyingEnabled);

		void setState(int state);

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

		/// If the GO presents a nightmare variant and
		/// will take damage when lit by the flashlight, 
		/// This value will hold the colours that the object
		/// will react to.
		int mColourSensitivityMask;	

		/// 'Immunity' time so a single collision is not processed during several ticks
		double mHitRecoveryTime;

		std::string getMaskString();

		bool mHasBeenHit;
		bool mHasDied;

		bool mAlertFinished;
		bool mSurpriseFinished;
		bool mFalseAlarmFinished;
		bool mCallToArmsFinished;
		bool mTiredFinished;
		bool mIdle1Finished;
		bool mAttackFinished;
		bool mCallWasHeard;
		bool mHasHeardCall;
		bool mStatueEnabled;
		bool mFlyingEnabled;

		EnemyType mEnemyType;

	};
	
	class TLogicComponentEnemyParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentEnemyParameters();
		~TLogicComponentEnemyParameters();

		bool hasPatrolTrajectory;

		int healthPoints;
		int lineOfSight;
		int colourSensitivityMask;
		EnemyType enemyType;
	};
}

#endif