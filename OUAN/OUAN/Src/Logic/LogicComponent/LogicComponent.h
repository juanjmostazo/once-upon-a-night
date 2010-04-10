#ifndef LogicComponentH_H
#define LogicComponentH_H

#include "../../Component/Component.h"
namespace OUAN
{
	/*
	typedef struct
	{
		std::string attackName;
		int	attackRange;
		int damage;
		std::string relatedAnimation;
	} TAttackData;
	*/

	class LogicComponent: public Component
	{
	public:
		LogicComponent(const std::string& type="");
		~LogicComponent();

		bool existsInDreams() const;
		void setExistsInDreams(bool existsInDreams);

		bool existsInNightmares() const;
		void setExistsInNightmares(bool existsInNightmares);

		int getState() const;
		void setState(int state);

		int getOldState(int index=0) const;

		int getHealthPoints() const;
		void setHealthPoints(int healthPoints);

		int getNumLives() const;
		void setNumLives(int numLives);

		int getInitialHealthPoints() const;
		void setInitialHealthPoints(int healthPoints);

		int getInitialNumLives() const;
		void setInitialNumLives(int numLives);

		std::string getScriptFilename() const;
		void setScriptFilename(const std::string& scriptFilename);

		std::string getScriptFunction() const;
		void setScriptFunction(const std::string& scriptFunction);

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

		virtual void update(long elapsedTime);

		bool isStateChanged() const;
		void setStateChanged(bool stateChanged);
		
		void initStateHistory();
	private:
		/// Number of lives of the component
		int mNumLives;
		/// Health points of the component
		int mHealthPoints;		
		/// Sight range
		int mLineOfSight;
		/// Logic state of the parent game object
		int mState;
		/// Filename of the script that'll be executed by the logic subsystem
		/// to update this component's parent game object
		std::string mScriptFilename;
		
		/// Name of the script function that'll handle the state update
		std::string mScriptFunction;

		/// Size of the number of states
		int stateHistory[GAMESTATE_HISTORY_SIZE];

		bool mStateChanged;

		bool mExistsInDreams;
		bool mExistsInNightmares;

		int mInitialHealthPoints;
		int mInitialNumLives;

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

	};
	
	class TLogicComponentParameters: public TComponentParameters
	{
	public:
		TLogicComponentParameters();
		~TLogicComponentParameters();

		/// Existence in each world
		bool existsInDreams;
		bool existsInNightmares;

		bool hasPatrolTrajectory;

		std::string scriptFilename;
		std::string scriptFunction;
		int defaultState;
		int numLives;
		int healthPoints;
		int lineOfSight;
		int attackDelay;
		int attackRange;
		int attackDamage;
		int colourSensitivityMask;	
	};
}

#endif