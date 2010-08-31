#include "OUAN_Precompiled.h"

#include "LogicComponentOny.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectOny.h"
#include "../../Game/GameObject/GameObjectTripollo.h"
#include "../../Game/GameObject/GameObjectTentetieso.h"
#include "../../Game/GameObject/GameObjectPlataform.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacterOny.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../../Event/Event.h"

using namespace OUAN;

LogicComponentOny::LogicComponentOny(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_ONY)
{
	mHitRecoveryTime=-1;
}

LogicComponentOny::~LogicComponentOny()
{
}

void LogicComponentOny::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (!pGameObject->isEnabled() || !getParent()->isEnabled()) 
	{
		return;
	}

	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ITEM_1UP)==0)
	{
		increaseLives();
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ITEM_MAXHP)==0)
	{
		setHealthPoints(getInitialHealthPoints());
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_HEART)==0)
	{
		increaseHP();
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_DIAMOND)==0)
	{
		increaseCollectableItemAmount(GAME_OBJECT_TYPE_DIAMOND);
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_CLOCKPIECE)==0)
	{
		GameOverEventPtr evt= GameOverEventPtr(new GameOverEvent(true));
		mParent->getGameWorldManager()->addEvent(evt);
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_STORYBOOK)==0)
	{
		//TODO
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_TRIPOLLO)==0 
		&& !getParent()->getGameWorldManager()->isGodMode())
	{
		GameObjectTripolloPtr tripollo= 
			BOOST_PTR_CAST(GameObjectTripollo,pGameObject);

		if(tripollo.get() && !tripollo->hasBeenHit() &&!tripollo->hasDied() 
			&& mHitRecoveryTime<0 && !CHECK_BIT(mState,ONY_STATE_BIT_FIELD_DIE))
		{		
			int oldLives=getNumLives();
			decreaseHP();
			mHitRecoveryTime=POST_HIT_INVULNERABILITY;

			if (getNumLives()==oldLives)
			{
				OnyTakesHitEventPtr evt = OnyTakesHitEventPtr(new OnyTakesHitEvent());
				getParent()->getGameWorldManager()->addEvent(evt);
			}			
		}
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_TENTETIESO)==0 
		&& pGameObject->getGameWorldManager()->getWorld()==NIGHTMARES 
		&& !getParent()->getGameWorldManager()->isGodMode())
	{
		GameObjectTentetiesoPtr tentetieso= 
			BOOST_PTR_CAST(GameObjectTentetieso,pGameObject);

		if(tentetieso.get() && !tentetieso->hasBeenHit() &&!tentetieso->hasDied() 
			&& mHitRecoveryTime<0 && !CHECK_BIT(mState,ONY_STATE_BIT_FIELD_DIE))
		{		
			int oldLives=getNumLives();
			decreaseHP();
			mHitRecoveryTime=POST_HIT_INVULNERABILITY;

			if (getNumLives()==oldLives)
			{
				OnyTakesHitEventPtr evt = OnyTakesHitEventPtr(new OnyTakesHitEvent());
				getParent()->getGameWorldManager()->addEvent(evt);
			}			
		}
	}
	else if (pGameObject->getType().compare(GAME_OBJECT_TYPE_PLATAFORM)==0)
	{
		GameObjectPlataformPtr plataform = 
			BOOST_PTR_CAST(GameObjectPlataform,pGameObject);

		PhysicsComponentComplexConvexPtr physicsPlataform = plataform->getPhysicsComponentComplexConvex();

		GameObjectOnyPtr ony = BOOST_PTR_CAST(GameObjectOny,getParent());
		PhysicsComponentCharacterOnyPtr physicsOny = ony->getPhysicsComponentCharacterOny();
		
		//Logger::getInstance()->log("///////////////////////");
		//Logger::getInstance()->log("ONY: " + Ogre::StringConverter::toString(physicsOny->getPosition()));
		//Logger::getInstance()->log("PLATFORM: " + Ogre::StringConverter::toString(physicsPlataform->getPosition()));
		//Logger::getInstance()->log("LAST_POS_DIFF: " + Ogre::StringConverter::toString(physicsPlataform->getLastPositionDifference()));

		Ogre::Vector3 posOny = physicsOny->getPosition();
		posOny += physicsPlataform->getLastPositionDifference();
		physicsOny->setPosition(posOny);
	}
	else if (pGameObject->getType().compare(GAME_OBJECT_TYPE_WATER)==0)
	{
		//Logger::getInstance()->log("ONY IS ON WATER");
		GameObjectOnyPtr ony = BOOST_PTR_CAST(GameObjectOny,getParent());
		ony->setOnWater(true);
	}
}

void LogicComponentOny::processAnimationEnded(const std::string& animationName)
{
	if (!Application::getInstance()->isPlayingCutscene())
	{
		if (animationName.compare(ONY_ANIM_HIT01)==0)
		{
			//if (mHitRecoveryTime<0)
			//{								
				mNewState=CLEAR_BIT(mNewState,ONY_STATE_BIT_FIELD_HIT);			
				//mInvulnerabilityCounter=POST_HIT_INVULNERABILITY;
			//}
		}
		else if (animationName.compare(ONY_ANIM_DIE01)==0)
		{
			mNewState=CLEAR_BIT(mNewState,ONY_STATE_BIT_FIELD_DIE);
			mParent->getGameWorldManager()->onyDied();
		}
	}
}

void LogicComponentOny::increaseHP(int amount)
{
	if (getParent()->isEnabled())
	{
		if (getHealthPoints()+amount>getInitialHealthPoints())
		{
			setHealthPoints(getInitialHealthPoints());
		}
		else 
		{
			setHealthPoints(getHealthPoints()+amount);
		}
	}
}

void LogicComponentOny::decreaseHP(int amount)
{	
	if (getParent()->isEnabled())
	{
		if (getHealthPoints()>0 && getNumLives()>0)
		{
			setHealthPoints(getHealthPoints()-amount<0
				?0
				:getHealthPoints()-amount);
			if (getHealthPoints()==0)
			{
				decreaseLives();				
			}
		}
	}
}

void LogicComponentOny::increaseLives(int amount)
{
	setNumLives(getNumLives()+amount);
}

void LogicComponentOny::decreaseLives(int amount,bool fallDown)
{
	setNumLives(getNumLives()-amount);
	if (getNumLives()<=0)
	{
		setNumLives(0);//safety assignment.
		gameOver();
	}
	else
	{
		loseLife(fallDown);
	}
}

void LogicComponentOny::loseLife(bool fallDown)
{
	if (fallDown)
	{
		setHealthPoints(getInitialHealthPoints());
	}
	//getParent()->disable();

	OnyDiesEventPtr evt=OnyDiesEventPtr(new OnyDiesEvent(getNumLives(),fallDown));
	getParent()->getGameWorldManager()->addEvent(evt);
}

void LogicComponentOny::gameOver()
{
	//TODO: ADDITIONAL STUFF (Or redefine in subclass for type-specific behaviour)
	getParent()->disable();

	GameOverEventPtr evt=GameOverEventPtr(new GameOverEvent(false));
	getParent()->getGameWorldManager()->addEvent(evt);
}

int LogicComponentOny::getHealthPoints() const
{
	return mHealthPoints;
}

void LogicComponentOny::setHealthPoints(int healthPoints)
{
	mHealthPoints=healthPoints;
}

int LogicComponentOny::getNumLives() const
{
	return mNumLives;
}

void LogicComponentOny::setNumLives(int numLives)
{
	mNumLives=numLives;
}

int LogicComponentOny::getInitialHealthPoints() const
{
	return mInitialHealthPoints;
}

void LogicComponentOny::setInitialHealthPoints(int healthPoints)
{
	mInitialHealthPoints=healthPoints;
}

int LogicComponentOny::getInitialNumLives() const
{
	return mInitialNumLives;
}

void LogicComponentOny::setInitialNumLives(int numLives)
{
	mInitialNumLives=numLives;
}

void LogicComponentOny::update(double elapsedTime)
{
	GameObjectOnyPtr ony = BOOST_PTR_CAST(GameObjectOny,getParent());
	int oldState=mState;
	int finalState=mNewState;

	if (finalState!=ONY_STATE_IDLE)
	{
		if (CHECK_BIT(finalState,ONY_STATE_BIT_FIELD_MOVEMENT))
		{
			if (CHECK_BIT(finalState,ONY_STATE_BIT_FIELD_HIT) && CHECK_BIT(oldState,ONY_STATE_BIT_FIELD_HIT))
			{
				//Interrupt hit animation
				finalState=CLEAR_BIT(finalState,ONY_STATE_BIT_FIELD_HIT);
			}
		}
		if (CHECK_BIT(finalState,ONY_STATE_BIT_FIELD_WALK))
		{
			if (CHECK_BIT(finalState,ONY_STATE_BIT_FIELD_HIT) && CHECK_BIT(oldState,ONY_STATE_BIT_FIELD_HIT))
			{
				//Interrupt hit animation
				finalState=CLEAR_BIT(finalState,ONY_STATE_BIT_FIELD_HIT);
			}

		}
		if (CHECK_BIT(finalState,ONY_STATE_BIT_FIELD_JUMP))
		{
			if (!ony->getPhysicsComponentCharacterOny()->isJumping())
			{
				finalState=CLEAR_BIT(finalState,ONY_STATE_BIT_FIELD_JUMP);
			}
			if (CHECK_BIT(finalState,ONY_STATE_BIT_FIELD_HIT) && CHECK_BIT(oldState,ONY_STATE_BIT_FIELD_HIT))
			{
				//Interrupt hit animation
				finalState=CLEAR_BIT(finalState,ONY_STATE_BIT_FIELD_HIT);
			}
		}
	}

	if(mHitRecoveryTime>=0)
	{
		mHitRecoveryTime-=elapsedTime;
	}
	else
	{
		finalState=CLEAR_BIT(finalState,ONY_STATE_BIT_FIELD_INVULNERABLE);
	}

	setState(finalState);
	setNewState(finalState);
	// mEventInducedStateChange=false;
}

void LogicComponentOny::setNewState(int newState)
{
	mNewState=newState;
}

int LogicComponentOny::getNewState()const
{
	return mNewState;
}
double LogicComponentOny::getHitRecoveryTime() const
{
	return mHitRecoveryTime;
}
void LogicComponentOny::increaseCollectableItemAmount(
	const std::string& type,int amount)
{
	if (mCollectedItems.find(type)!=mCollectedItems.end())
	{
		//alias to type less
		int* oldItemsAmount = &mCollectedItems[type].collectedItems;
		int* to1UP = &mCollectedItems[type].newLifeAmount;
		//
		int newItemsAmount = *oldItemsAmount+ amount;
		int nLives = (newItemsAmount/(*to1UP)) - (*oldItemsAmount/(*to1UP));
		std::stringstream msg;
		// Don't reset the old amount for now. 
		// It can be useful for scoring purposes,
		// and we're not restricted as in the NES era to use 
		// two-digit numbers.
		*oldItemsAmount=newItemsAmount;
		msg<<"DIAMOND PICKED UP - CURRENT AMOUNT: "<<newItemsAmount;
		Logger::getInstance()->log(msg.str());
		if (nLives>0)
		{
			// Generate event LIFEINCREASED so that the game world manager
			// or the state can play some feedback sound, update the HUD, ...
			
			// For Any, we can play the sound right away
			// mParent->getAudioComponent()->playSound("ANY_VICTORY");
			increaseLives(nLives);
			msg.str("");
			msg<<"ONY LOGIC - LIVES INCREASED: "<<mNumLives;
			Logger::getInstance()->log(msg.str());
			// update the map
		}	
	}
}
void LogicComponentOny::setCollectableItems(const TCollectedItems& collectableItems)
{
	mCollectedItems.clear();
	mCollectedItems.insert(collectableItems.begin(),collectableItems.end());
}
int LogicComponentOny::getItemAmount(const std::string& type)
{
	if (mCollectedItems.find(type)!=mCollectedItems.end())
	{
		return mCollectedItems[type].collectedItems;
	}
	else throw std::exception("Collectable item type not found");
}
int LogicComponentOny::getDiamonds()
{
	return getItemAmount(GAME_OBJECT_TYPE_DIAMOND);
}

void LogicComponentOny::activateTrajectory(const std::string& name, bool looping)
{
	BOOST_PTR_CAST(GameObjectOny,mParent)->activateTrajectory(name,looping);
}
void LogicComponentOny::deactivateTrajectory()
{
	BOOST_PTR_CAST(GameObjectOny,mParent)->deactivateTrajectory();
}
bool LogicComponentOny::isTrajectoryFinished() const
{
	return BOOST_PTR_CAST(GameObjectOny,mParent)->isTrajectoryFinished();
}
void LogicComponentOny::changeMessage(const std::string& message, double duration)
{
	BOOST_PTR_CAST(GameObjectOny,mParent)->changeMessage(message,duration);
}
void LogicComponentOny::changeMessage(const std::string& message)
{
	BOOST_PTR_CAST(GameObjectOny,mParent)->changeMessage(message);
}
void LogicComponentOny::hideMessage()
{
	BOOST_PTR_CAST(GameObjectOny,mParent)->hideMessage();
}
void LogicComponentOny::showMessage()
{
	BOOST_PTR_CAST(GameObjectOny,mParent)->showMessage();
}
bool LogicComponentOny::isMessageVisible() const
{
	return BOOST_PTR_CAST(GameObjectOny,mParent)->isMessageVisible();
}
//-------
TLogicComponentOnyParameters::TLogicComponentOnyParameters() : TLogicComponentParameters()
{

}

TLogicComponentOnyParameters::~TLogicComponentOnyParameters()
{

}
