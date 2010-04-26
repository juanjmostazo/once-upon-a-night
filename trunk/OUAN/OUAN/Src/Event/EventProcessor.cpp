#include "EventProcessor.h"
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
		TGameObjectContainer objs=mWorldManager->getAllGameObjects();

		for (TGameObjectContainerIterator it = objs.begin(); it!=objs.end();++it)
		{
			it->second->changeWorld(evt->getNewWorld());
		}
	}
}

void EventProcessor::processCollision(CollisionEventPtr evt)
{
	if (evt->getGameObject1() && evt->getGameObject2())
	{
		//Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCollision (" + evt->getGameObject1()->getName() + "," + evt->getGameObject2()->getName() + ")");
		
		 evt->getGameObject1()->processCollision( evt->getGameObject2());
		 evt->getGameObject2()->processCollision( evt->getGameObject1());
	}
	else
	{
		Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCollision with unknown data!");
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
		Ogre::LogManager::getSingleton().logMessage("EventProcessor: processEnterTrigger with unknown data!");
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
		Ogre::LogManager::getSingleton().logMessage("EventProcessor: processExitTrigger with unknown data!");
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