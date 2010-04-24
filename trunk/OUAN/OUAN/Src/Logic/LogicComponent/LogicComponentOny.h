#ifndef LogicComponentOnyH_H
#define LogicComponentOnyH_H

#include "LogicComponent.h"
namespace OUAN
{

	class LogicComponentOny: public LogicComponent
	{
	public:
		LogicComponentOny(const std::string& type="");
		~LogicComponentOny();

		void processCollision(GameObjectPtr pGameObject);
		void processAnimationEnded(const std::string& animationName);

		int getHealthPoints() const;
		void setHealthPoints(int healthPoints);

		int getNumLives() const;
		void setNumLives(int numLives);

		int getInitialHealthPoints() const;
		void setInitialHealthPoints(int healthPoints);

		int getInitialNumLives() const;
		void setInitialNumLives(int numLives);

		int getAttackDamage() const;
		void setAttackDamage(int attackDamage);


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

		void setEventInducedStateChange(bool eventInducedStateChange);
		bool isEventInducedStateChange() const;

	private:
		bool mEventInducedStateChange;
		/// Number of lives of the component
		int mNumLives;
		/// Health points of the component
		int mHealthPoints;		
	
		int mInitialHealthPoints;
		int mInitialNumLives;

		/// Damage inflicted by the attack
		int mAttackDamage;

		/// 'Immunity' time so a single collision is not processed during several ticks
		double mHitRecoveryTime;

	};
	
	class TLogicComponentOnyParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentOnyParameters();
		~TLogicComponentOnyParameters();

		int numLives;
		int healthPoints;

		int attackDamage;

	};
}

#endif