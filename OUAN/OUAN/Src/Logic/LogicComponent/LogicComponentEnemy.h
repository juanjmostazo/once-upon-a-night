#ifndef LogicComponentEnemyH_H
#define LogicComponentEnemyH_H

#include "LogicComponent.h"
namespace OUAN
{
	const int COLOUR_FLAG_RED=1;
	const int COLOUR_FLAG_GREEN=2;
	const int COLOUR_FLAG_BLUE=4;
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
		int mHitRecoveryTime;

		std::string getColourName(int colour);
		std::string getMaskString();

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
	};
}

#endif