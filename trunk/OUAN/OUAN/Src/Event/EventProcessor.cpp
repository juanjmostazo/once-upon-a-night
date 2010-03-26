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
	Ogre::String characters = evt->getCharacter1()->getName() + "," + evt->getCharacter2()->getName();
	Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCharactersCollision (" + characters + ")");
}

void EventProcessor::processCharacterInTrigger(CharacterInTriggerEventPtr evt)
{
	//Ogre::LogManager::getSingleton().logMessage("* Character: " + evt->getCharacter()->getName());
	//Ogre::LogManager::getSingleton().logMessage("* Trigger: " + evt->getTrigger()->getName());

	if (evt->getCharacter()->getType().compare(GAME_OBJECT_TYPE_ONY) == 0)
	{
		Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCharacterTrigger (ONY)");

		switch (evt->getCollisionType())
		{
		case COLLISION_TYPE_TRIGGER_ENTER: 

			if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_TRIGGERBOX) == 0) 
			{
				GameObjectTriggerBoxPtr tmpObject = boost::dynamic_pointer_cast<GameObjectTriggerBox>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->win();
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_TRIGGERCAPSULE) == 0) 
			{	
				GameObjectTriggerCapsulePtr tmpObject = boost::dynamic_pointer_cast<GameObjectTriggerCapsule>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->win();
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_ITEM_1UP) == 0) 
			{
				GameObjectItem1UPPtr tmpObject = boost::dynamic_pointer_cast<GameObjectItem1UP>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->takeItem1UP(tmpObject);
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_ITEM_MAXHP) == 0) 
			{
				GameObjectItemMaxHPPtr tmpObject = boost::dynamic_pointer_cast<GameObjectItemMaxHP>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->takeItemMaxHP(tmpObject);
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_HEART) == 0) 
			{
				GameObjectHeartPtr tmpObject = boost::dynamic_pointer_cast<GameObjectHeart>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->takeItemHeart(tmpObject);
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_DIAMOND) == 0) 
			{
				GameObjectDiamondPtr tmpObject = boost::dynamic_pointer_cast<GameObjectDiamond>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->takeItemDiamond(tmpObject);
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_CLOCKPIECE) == 0) 
			{
				GameObjectClockPiecePtr tmpObject = boost::dynamic_pointer_cast<GameObjectClockPiece>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->takeItemClockPiece(tmpObject);
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_STORYBOOK) == 0) 
			{
				GameObjectStoryBookPtr tmpObject = boost::dynamic_pointer_cast<GameObjectStoryBook>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->takeItemStoryBook(tmpObject);
			}
			//TODO else if block, same with rest of game object items

			break;
		case COLLISION_TYPE_TRIGGER_PRESENCE: 

			break;
		case COLLISION_TYPE_TRIGGER_EXIT: break;
		default: break;
		}
	}
	else 
	{
		Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCharacterTrigger (OTHER)");
	}
}