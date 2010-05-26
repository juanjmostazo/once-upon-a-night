#include "EventProcessor.h"
#include "../Graphics/TrajectoryManager/TrajectoryManager.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObject.h"
#include "../Game/GameObject/GameObjectTriggerBox.h"
#include "../Game/GameObject/GameObjectTriggerCapsule.h"
#include "../Game/GameObject/GameObjectItem1UP.h"
#include "../Game/GameObject/GameObjectItemMaxHP.h"
#include "../Game/GameObject/GameObjectHeart.h"
#include "../Game/GameObject/GameObjectDiamond.h"
#include "../Game/GameObject/GameObjectClockPiece.h"
#include "../Game/GameObject/GameObjectStoryBook.h"
#include "../Game/GameObject/GameObjectOny.h"
#include "../Utils/Utils.h"

using namespace OUAN;

EventProcessor::EventProcessor()
{

}

void EventProcessor::init(GameWorldManagerPtr worldManager)
{
	mWorldManager=worldManager;
	registerHandlers();
}

void EventProcessor::cleanUp()
{
	unregisterHandlers();
}

void EventProcessor::registerHandlers()
{
	if (mWorldManager.get())
	{
		boost::shared_ptr<EventProcessor> this_ =shared_from_this();

		registerEventHandler<EventProcessor,ChangeWorldEvent, EVENT_TYPE_CHANGEWORLD>
			(this_,&EventProcessor::processChangeWorld,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,CollisionEvent, EVENT_TYPE_COLLISION>
			(this_,&EventProcessor::processCollision,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,EnterTriggerEvent, EVENT_TYPE_ENTER_TRIGGER>
			(this_,&EventProcessor::processEnterTrigger,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,ExitTriggerEvent, EVENT_TYPE_EXIT_TRIGGER>
			(this_,&EventProcessor::processExitTrigger,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,GameOverEvent, EVENT_TYPE_GAMEOVER>
			(this_,&EventProcessor::processGameOver,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,OnyDiesEvent, EVENT_TYPE_ONY_DEATH>
			(this_,&EventProcessor::processOnyDies,mWorldManager->getEventManager());
		
		registerEventHandler<EventProcessor,OnyFallsEvent, EVENT_TYPE_ONY_FALLS>
			(this_,&EventProcessor::processOnyFalls,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,WeaponModeChangedEvent,EVENT_TYPE_WEAPON_MODE_CHANGED>
			(this_,&EventProcessor::processWeaponModeChanged,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,AnimationEndedEvent,EVENT_TYPE_ANIMATION_ENDED>
			(this_,&EventProcessor::processAnimationEnded,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,AnimationStartedEvent,EVENT_TYPE_ANIMATION_STARTED>
			(this_,&EventProcessor::processAnimationStarted,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,ActivatedItemEvent,EVENT_TYPE_ACTIVATED_ITEM>
			(this_,&EventProcessor::processActivatedItem,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,OnyTakesHitEvent,EVENT_TYPE_ONY_TAKES_HIT>
			(this_,&EventProcessor::processOnyTakesHit,mWorldManager->getEventManager());
	}
}

void EventProcessor::unregisterHandlers()
{
	if (mWorldManager.get())
	{
		boost::shared_ptr<EventProcessor> this_ =shared_from_this();

		unregisterEventHandler<EventProcessor,ChangeWorldEvent, EVENT_TYPE_CHANGEWORLD>
			(this_,&EventProcessor::processChangeWorld,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,CollisionEvent, EVENT_TYPE_COLLISION>
			(this_,&EventProcessor::processCollision,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,EnterTriggerEvent, EVENT_TYPE_ENTER_TRIGGER>
			(this_,&EventProcessor::processEnterTrigger,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,ExitTriggerEvent, EVENT_TYPE_EXIT_TRIGGER>
			(this_,&EventProcessor::processExitTrigger,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,GameOverEvent, EVENT_TYPE_GAMEOVER>
			(this_,&EventProcessor::processGameOver,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,OnyDiesEvent, EVENT_TYPE_ONY_DEATH>
			(this_,&EventProcessor::processOnyDies,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,OnyFallsEvent, EVENT_TYPE_ONY_FALLS>
			(this_,&EventProcessor::processOnyFalls,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,WeaponModeChangedEvent,EVENT_TYPE_WEAPON_MODE_CHANGED>
			(this_,&EventProcessor::processWeaponModeChanged,mWorldManager->getEventManager());
		
		unregisterEventHandler<EventProcessor,AnimationEndedEvent,EVENT_TYPE_ANIMATION_ENDED>
			(this_,&EventProcessor::processAnimationEnded,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,AnimationStartedEvent,EVENT_TYPE_ANIMATION_STARTED>
			(this_,&EventProcessor::processAnimationStarted,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,ActivatedItemEvent,EVENT_TYPE_ACTIVATED_ITEM>
			(this_,&EventProcessor::processActivatedItem,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,OnyTakesHitEvent,EVENT_TYPE_ONY_TAKES_HIT>
			(this_,&EventProcessor::processOnyTakesHit,mWorldManager->getEventManager());
	}
}

//---------------------------------------------------------------------
// Event callbacks
//---------------------------------------------------------------------
void EventProcessor::processGameOver(GameOverEventPtr evt)
{
	if (mWorldManager.get())
	{
		if (evt->isWin())
		{
			mWorldManager->win();
		}
		else 
		{
			mWorldManager->lose();
		}
	}
}

void EventProcessor::processOnyDies(OnyDiesEventPtr evt)
{
	if (mWorldManager.get())
	{
		if (!evt->onyFellDown())
		{
			mWorldManager->getGameObjectOny()->getLogicComponentOny()->setNewState(SET_BIT(0,ONY_STATE_BIT_FIELD_DIE));
		}
		else mWorldManager->onyDied();
	}
}

void EventProcessor::processChangeWorld(ChangeWorldEventPtr evt)
{
	if (mWorldManager.get())
	{
		mWorldManager->getParent()->getTrajectoryManager()->changeWorld(evt->getNewWorld());
		TGameObjectContainer * objs=mWorldManager->getAllGameObjects();

		if(evt->fast)
		{
			mWorldManager->activateChangeWorldFast();
			for (TGameObjectContainerIterator it = objs->begin(); it!=objs->end();++it)
			{
				it->second->activateChangeWorldFast();
				it->second->setWorld(evt->getNewWorld());
			}
		}
		else
		{
			double max_distance=-1;
			double current_distance;
			std::vector<double> distances;
			mWorldManager->activateChangeWorld();
			for (TGameObjectContainerIterator it = objs->begin(); it!=objs->end();++it)
			{
				if(it->second->isChangingWorld())
				{
					it->second->setChangeWorldElapsedTime(it->second->getChangeWorldTotalTime()-it->second->getChangeWorldElapsedTime());				
				}
				else
				{
					if(evt->random_trees)
					{
						it->second->calculateChangeWorldDelay(evt->change_world_elapsed_time,evt->time,evt->getNewWorld(),Utils::Random::getInstance()->getRandomDouble(),0.25f);
					}
					else
					{
						current_distance=mWorldManager->getPlayerDistance(it->second->getName());
						if(current_distance>max_distance)
						{
							max_distance=current_distance;
						}
						distances.push_back(current_distance);
						//Logger::getInstance()->log("getPlayerDistance "+it->second->getName()+" "+Ogre::StringConverter::toString(Ogre::Real(current_distance)));
					}
				}
			}
			//BUG WHEN TRIPOLLO FALLS
			//Logger::getInstance()->log("MAX DISTANCE "+Ogre::StringConverter::toString(Ogre::Real(max_distance)));

			if(!evt->random_trees)
			{
				int k=0;
				for (TGameObjectContainerIterator it = objs->begin(); it!=objs->end();++it)
				{
					if(!it->second->isChangingWorld())
					{
						it->second->calculateChangeWorldDelay(evt->change_world_elapsed_time,evt->time,evt->getNewWorld(),Ogre::Math::Clamp<double>(distances[k]/1000.0f,0.0f,1.0f),0.5f);
						//Logger::getInstance()->log("calculateChangeWorldDelay "+it->second->getName()+" "+Ogre::StringConverter::toString(Ogre::Real(distances[k]/max_distance)));

						k++;
					}
				}
			}
		}
	}
}

void EventProcessor::processCollision(CollisionEventPtr evt)
{
	if (evt->getGameObject1() && evt->getGameObject2())
	{
		//Logger::getInstance()->log("EventProcessor: processCollision (" + evt->getGameObject1()->getName() + "," + evt->getGameObject2()->getName() + ")");
		
		 evt->getGameObject1()->processCollision( evt->getGameObject2());
		 evt->getGameObject2()->processCollision( evt->getGameObject1());
	}
	else
	{
		Logger::getInstance()->log("EventProcessor: processCollision with unknown data!");
	}
}

void EventProcessor::processEnterTrigger(EnterTriggerEventPtr evt)
{
	if (evt->getTrigger() && evt->getGameObject())
	{
		 evt->getTrigger()->processEnterTrigger( evt->getGameObject());
		 evt->getGameObject()->processEnterTrigger( evt->getTrigger());
	}
	else
	{
		Logger::getInstance()->log("EventProcessor: processEnterTrigger with unknown data!");
	}
}

void EventProcessor::processExitTrigger(ExitTriggerEventPtr evt)
{
	if (evt->getTrigger() && evt->getGameObject())
	{
		 evt->getTrigger()->processExitTrigger( evt->getGameObject());
		 evt->getGameObject()->processExitTrigger( evt->getTrigger());
	}
	else
	{
		Logger::getInstance()->log("EventProcessor: processExitTrigger with unknown data!");
	}
}

void EventProcessor::processClearQueue(ClearQueueEventPtr evt)
{
	if (mWorldManager)
		mWorldManager->clearEvents();
}

void EventProcessor::processOnyFalls(OnyFallsEventPtr evt)
{
	mWorldManager->getGameObjectOny()->getLogicComponentOny()->decreaseLives(1,true);
}

void EventProcessor::processWeaponModeChanged(WeaponModeChangedEventPtr evt)
{
	if (mWorldManager.get() && mWorldManager->getGameObjectOny().get())
	{
		mWorldManager->getGameObjectOny()->setAttack(evt->getNewWeaponMode());
	}
}

void EventProcessor::processAnimationEnded(AnimationEndedEventPtr evt)
{
	if (evt->getActor().get())
	{		
		evt->getActor()->processAnimationEnded(evt->getAnimationName());
	}
}

void EventProcessor::processAnimationStarted(AnimationStartedEventPtr evt)
{

}

void EventProcessor::processActivatedItem(ActivatedItemEventPtr evt)
{
	if (evt->getActor().get())
	{
		evt->getActor()->activate();
		//Play "activate" sound
	}
}
void EventProcessor::processOnyTakesHit(OnyTakesHitEventPtr evt)
{
	if (mWorldManager->getGameObjectOny().get())
	{
		mWorldManager->getGameObjectOny()->getLogicComponentOny()->setNewState(SET_BIT(0,ONY_STATE_BIT_FIELD_HIT));
	}	
}