#include "OUAN_Precompiled.h"

#include "../../Utils/Utils.h"
#include "LogicComponentOny.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectOny.h"
#include "../../Game/GameObject/GameObjectTripollo.h"
#include "../../Game/GameObject/GameObjectBoss.h"
#include "../../Game/GameObject/GameObjectTentetieso.h"
#include "../../Game/GameObject/GameObjectPlataform.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacterOny.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../../Audio/AudioComponent/AudioComponent.h"
#include "../../Event/Event.h"

using namespace OUAN;

LogicComponentOny::LogicComponentOny(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_ONY)
{
	mHitRecoveryTime=-1;
	mIdleTime=0;
	mNapBufferState=-1;
	mAttackBufferState=-1;
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
	Logger::getInstance()->log("LogicComponentOny::processCollision " + pGameObject->getName());

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
		GameWorldManagerPtr worldMgr = mParent->getGameWorldManager();
		worldMgr->setPickedStoryParts(worldMgr->getPickedStoryParts()+1);
		StorybookPartPickedEventPtr evt = StorybookPartPickedEventPtr(new StorybookPartPickedEvent(worldMgr->getPickedStoryParts(),worldMgr->getTotalStoryParts()));
		worldMgr->addEvent(evt);
	}
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_TRIPOLLO)==0
		&& !getParent()->getGameWorldManager()->isGodMode())
	{
		getParent()->displayText("TRIPOLLOHIT!");
		GameObjectTripolloPtr tripollo= 
			BOOST_PTR_CAST(GameObjectTripollo,pGameObject);
		bool mayHitTripollo=tripollo.get() && !tripollo->hasBeenHit() &&!tripollo->hasDied() && 
			!tripollo->isStatueEnabled();
		if( mayHitTripollo && mHitRecoveryTime<0 && mState!=ONY_STATE_DIE)
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
	else if(pGameObject->getType().compare(GAME_OBJECT_TYPE_BOSS)==0
		&& !getParent()->getGameWorldManager()->isGodMode())
	{
		GameObjectBossPtr boss= 
			BOOST_PTR_CAST(GameObjectBoss,pGameObject);
		bool mayHitBoss=boss.get() && !boss->hasBeenHit() &&!boss->hasDied();
		if( mayHitBoss && mHitRecoveryTime<0 && mState!=ONY_STATE_DIE)
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

		GameObjectOnyPtr ony = BOOST_PTR_CAST(GameObjectOny,getParent());

		//if(Ogre::Math::Abs(Application::getInstance()->getPhysicsSubsystem()->angleFromNormal(pNormal))<50)
		//{
			ony->setOnPlataform(true,plataform);
		//}
	}
	else if (pGameObject->getType().compare(GAME_OBJECT_TYPE_WOODBOX)==0)
	{
		GameObjectOnyPtr ony = BOOST_PTR_CAST(GameObjectOny,getParent());
		if(!ony->getAudioComponent()->isPlaying(ONY_SOUND_PUSH))
		{
			ony->getAudioComponent()->playSound(ONY_SOUND_PUSH);
		}
	}
	else if (pGameObject->getType().compare(GAME_OBJECT_TYPE_BOMB)==0)
	{
		GameObjectOnyPtr ony = BOOST_PTR_CAST(GameObjectOny,getParent());
		if(!ony->getAudioComponent()->isPlaying(ONY_SOUND_PUSH))
		{
			ony->getAudioComponent()->playSound(ONY_SOUND_PUSH);
		}
	}


}

void LogicComponentOny::processAnimationEnded(const std::string& animationName)
{
	if (!Application::getInstance()->isPlayingCutscene())
	{
		if (animationName.compare(ONY_ANIM_IDLE02)==0)
		{
			mNewState=ONY_STATE_IDLE;
		}
		if (animationName.compare(
			ONY_ANIM_NAP_START)==0)
		{
			mParent->changeAnimation(ONY_ANIM_NAP_KEEP);
		}
		if (animationName.compare(
			ONY_ANIM_JUMP01_END)==0 ||
			animationName.compare(
			ONY_ANIM_JUMP02_END)==0 )
		{
			mParent->changeAnimation(ONY_ANIM_IDLE01);
		}
		if (animationName.compare(ONY_ANIM_FALL_END)==0)
		{
			mParent->changeAnimation(ONY_ANIM_IDLE01);
		}
		if (animationName.compare(ONY_ANIM_VICTORY)==0)
		{
			mParent->getGameWorldManager()->setVictoryAnimationEnded(true);
			mParent->getGameWorldManager()->win();
		}
		if (animationName.compare(
			ONY_ANIM_JUMP01_START)==0)
		{
 			mParent->changeAnimation(ONY_ANIM_JUMP01_KEEP);
		}
		if (animationName.compare(
			ONY_ANIM_JUMP02_START)==0)
		{
			mParent->changeAnimation(ONY_ANIM_JUMP02_KEEP);
		}
		if (animationName.compare(ONY_ANIM_FALL_START)==0)
		{
			mParent->changeAnimation(ONY_ANIM_FALL_KEEP);
		}
		if (animationName.compare(ONY_ANIM_NAP_END)==0)
		{
			mNewState = mNapBufferState;
			mNapBufferState=-1;
		}
		if (animationName.compare(ONY_ANIM_HIT01)==0)
		{
			//if (mHitRecoveryTime<0)
			//{								
				mNewState=ONY_STATE_IDLE;			

				//mInvulnerabilityCounter=POST_HIT_INVULNERABILITY;
			//}
		}
		else if (animationName.compare(ONY_ANIM_DIE)==0)
		{
			mNewState=ONY_STATE_IDLE;
			mParent->getGameWorldManager()->onyDied();
		}
		else if (animationName.compare(ONY_ANIM_DRAW_FLASHLIGHT)==0)
		{
			mParent->changeAnimation(ONY_ANIM_SHOOT_CENTER);
		}
		else if (animationName.compare(ONY_ANIM_HIDE_FLASHLIGHT)==0)
		{
			mNewState=mAttackBufferState;
			mAttackBufferState=-1;
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

	if (mIdleTime>0) 
		mIdleTime-=elapsedTime;

	if (finalState!=ONY_STATE_VICTORY)
	{

		if (oldState==ONY_STATE_NAP && finalState!=ONY_STATE_NAP)
		{
			mNapBufferState=finalState;
			finalState=ONY_STATE_NAP_END;
			mParent->changeAnimation(ONY_ANIM_NAP_END);
		}
		else if (oldState==ONY_STATE_ATTACK && finalState!=ONY_STATE_ATTACK)
		{
			if (mParent->getGameWorldManager()->getWorld()==NIGHTMARES)
			{
				mAttackBufferState=finalState;
				finalState=ONY_STATE_ATTACK_END;
				mParent->changeAnimation(ONY_ANIM_HIDE_FLASHLIGHT);
			}
		}

		if (finalState==ONY_STATE_IDLE)
		{
			if ((oldState!=ONY_STATE_IDLE && oldState!=ONY_STATE_IDLE1)|| mParent->isFirstUpdate())
				mIdleTime=IDLE_SECONDS_TO_NAP;
			if (Utils::Random::getInstance()->getRandomDouble()<ONY_IDLE2_CHANCE)
			{
				finalState=ONY_STATE_IDLE1;
			} 
			else if (mIdleTime<=0)
			{
				finalState=ONY_STATE_NAP;	
			}
		}
		else if (finalState==ONY_STATE_JUMP && !ony->getPhysicsComponentCharacterOny()->isJumping())
		{
			finalState=ONY_STATE_IDLE;//or maybe falling?
		}		

		if(mHitRecoveryTime>=0)
		{
			mHitRecoveryTime-=elapsedTime;
		}
		else
		{
			BOOST_PTR_CAST(GameObjectOny, mParent)->setInvulnerable(false);
		}
	}

	setState(finalState);
	setNewState(finalState);
	// mEventInducedStateChange=false;
}

void LogicComponentOny::setNewState(int newState)
{

	mNewState=newState;
	Logger::getInstance()->log("ONY::SET NEW STATE: "+StringConverter::toString(newState));
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

double LogicComponentOny::getIdleTime() const
{
	return mIdleTime;
}
void LogicComponentOny::setIdleTime(double idleTime)
{
	mIdleTime=idleTime;
}
bool LogicComponentOny::awaitingForNapEnd() const
{
	return mNapBufferState!=-1;
}
void LogicComponentOny::initPostHitInvulnerability()
{
	BOOST_PTR_CAST(GameObjectOny,mParent)->setInvulnerable(true);
	mHitRecoveryTime=POST_HIT_INVULNERABILITY;
}
bool LogicComponentOny::awaitingForAttackEnd() const
{
	return mAttackBufferState!=-1;
}
//-------
TLogicComponentOnyParameters::TLogicComponentOnyParameters() : TLogicComponentParameters()
{

}

TLogicComponentOnyParameters::~TLogicComponentOnyParameters()
{

}
