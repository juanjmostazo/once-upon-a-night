#ifndef LogicComponentOnyH_H
#define LogicComponentOnyH_H

#include "LogicComponent.h"
namespace OUAN
{

	struct TCollectableItemEntry
	{
		std::string gameObjectType;
		int newLifeAmount;
		int collectedItems;
	};
	typedef std::map<std::string, TCollectableItemEntry> TCollectedItems;

	class LogicComponentOny: public LogicComponent
	{
	public:
		LogicComponentOny(const std::string& type="");
		~LogicComponentOny();

		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);
		void processAnimationEnded(const std::string& animationName);

		int getHealthPoints() const;
		void setHealthPoints(int healthPoints);

		int getNumLives() const;
		void setNumLives(int numLives);

		int getInitialHealthPoints() const;
		void setInitialHealthPoints(int healthPoints);

		int getInitialNumLives() const;
		void setInitialNumLives(int numLives);

		/// If applicable, increase the object's health points
		/// @param amount number of HP to increase
		void increaseHP(int amount=1);
		/// If applicable, decrease the object's health points
		/// @param amount number of HP to decrease
		void decreaseHP(int amount=1);
		
		/// If applicable, increase the object's number of lives
		/// @param amount of lives to increase
		void increaseLives(int amount=1);
		/// If applicable, decrease the object's number of lives
		/// @param amount of lives to decrease
		void decreaseLives(int amount=1, bool fallDown=false);

		/// Additional actions to take after losing one life
		void loseLife(bool fallDown=false);

		/// Additional actions to take after losing all lives
		void gameOver();

		void update(double elapsedTime);

		void setNewState(int newState);
		int getNewState() const;

		double getHitRecoveryTime() const;

		void increaseCollectableItemAmount(const std::string& type, int value=1);
		void setCollectableItems(const TCollectedItems& collectableItems);

		int getItemAmount(const std::string& type);
		int getDiamonds();

		void activateTrajectory(const std::string& name,bool looping);
		void deactivateTrajectory();
		bool isTrajectoryFinished() const;

		void changeMessage(const std::string& message, double duration);
		void changeMessage(const std::string& message);
		void hideMessage();
		void showMessage();
		bool isMessageVisible() const;

		double getIdleTime() const;
		void setIdleTime(double idleTime);

		bool awaitingForNapEnd() const;

	private:
		double mIdleTime;
		/// Number of lives of the component
		int mNumLives;
		/// Health points of the component
		int mHealthPoints;		
	
		int mInitialHealthPoints;
		int mInitialNumLives;

		/// Collection keeping track of all possible collectable items
		TCollectedItems mCollectedItems;

		/// 'Immunity' time so a single collision is not processed during several ticks
		double mHitRecoveryTime;
		
		//double mInvulnerabilityCounter;

		//This variable will hold the state changes caused by game or input events
		//This way, there will only be a state change per frame, as it should be.
		int mNewState; 

		//State to return to after the stand-up animation has finished
		int mNapBufferState;
	};
	
	class TLogicComponentOnyParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentOnyParameters();
		~TLogicComponentOnyParameters();

		int numLives;
		int healthPoints;
		TCollectedItems collectedItems;
	};
}

#endif