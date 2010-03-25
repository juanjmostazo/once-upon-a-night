#include "EventProcessor.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObject.h"
#include "../Game/GameObject/GameObjectItem1UP.h"
#include "../Game/GameObject/GameObjectItemMaxHP.h"

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

		registerEventHandler<EventProcessor,CharactersCollisionEvent, EVENT_TYPE_CHARACTERS_COLLISION>
			(this_,&EventProcessor::processCharactersCollision,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,CharacterInTriggerEvent, EVENT_TYPE_CHARACTER_IN_TRIGGER>
			(this_,&EventProcessor::processCharacterInTrigger,mWorldManager->getEventManager());
	}
}

void EventProcessor::unregisterHandlers()
{
	if (mWorldManager.get())
	{
		boost::shared_ptr<EventProcessor> this_ =shared_from_this();

		unregisterEventHandler<EventProcessor,ChangeWorldEvent, EVENT_TYPE_CHANGEWORLD>
			(this_,&EventProcessor::processChangeWorld,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,CharactersCollisionEvent, EVENT_TYPE_CHARACTERS_COLLISION>
			(this_,&EventProcessor::processCharactersCollision,mWorldManager->getEventManager());

		unregisterEventHandler<EventProcessor,CharacterInTriggerEvent, EVENT_TYPE_CHARACTER_IN_TRIGGER>
			(this_,&EventProcessor::processCharacterInTrigger,mWorldManager->getEventManager());
	}
}

//---------------------------------------------------------------------
// Event callbacks
//---------------------------------------------------------------------

void EventProcessor::processChangeWorld(ChangeWorldEventPtr evt)
{
	if (mWorldManager.get())
	{
		TGameObjectContainer objs=mWorldManager->getAllGameObjects();

		//TODO: Replace the container getter with a more specific one if needed
		for (TGameObjectContainerIterator it = objs.begin(); it!=objs.end();++it)
		{
			it->second->changeWorld(evt->getNewWorld());
		}		
	}
}

void EventProcessor::processCharactersCollision(CharactersCollisionEventPtr evt)
{
	Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCharactersCollision");
}

void EventProcessor::processCharacterInTrigger(CharacterInTriggerEventPtr evt)
{
	//WHEN ENTERING A WIN ZONE
	//mApp->getGameWorldManager()->setGameOver(true);
	//mApp->getGameWorldManager()->setGameBeaten(true);

	switch (evt->getCollisionType())
	{
	case COLLISION_TYPE_TRIGGER_ENTER: 
		/**
		* If it is an item:
		* - Set it as disabled
		* - Hide it (Render Component)
		* - Destroy Physics Component
		*/

		if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_ITEM_1UP) == 0) 
		{
			GameObjectItem1UPPtr tmpObject = boost::dynamic_pointer_cast<GameObjectItem1UP>(evt->getTrigger());
			tmpObject->getRenderComponentEntity()->setVisible(false);
			tmpObject->getPhysicsComponentVolumeBox()->destroy();
			tmpObject->disable();

			//TODO Add 1 life logic
		}
		else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_ITEM_MAXHP) == 0) 
		{
			GameObjectItemMaxHPPtr tmpObject = boost::dynamic_pointer_cast<GameObjectItemMaxHP>(evt->getTrigger());
			tmpObject->getRenderComponentEntity()->setVisible(false);
			tmpObject->getPhysicsComponentVolumeBox()->destroy();
			tmpObject->disable();

			//TODO Add max hp logic
		}
		//TODO else if block, same with rest of game object items

	break;
	case COLLISION_TYPE_TRIGGER_PRESENCE: 

	break;
	case COLLISION_TYPE_TRIGGER_EXIT: break;
	default: break;
	}

	Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCharacterTrigger");
}