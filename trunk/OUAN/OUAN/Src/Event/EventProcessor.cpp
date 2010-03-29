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

		registerEventHandler<EventProcessor,CharactersCollisionEvent, EVENT_TYPE_CHARACTERS_COLLISION>
			(this_,&EventProcessor::processCharactersCollision,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,CharacterInTriggerEvent, EVENT_TYPE_CHARACTER_IN_TRIGGER>
			(this_,&EventProcessor::processCharacterInTrigger,mWorldManager->getEventManager());

		registerEventHandler<EventProcessor,GameOverEvent, EVENT_TYPE_GAMEOVER>
			(this_,&EventProcessor::processGameOver,mWorldManager->getEventManager());
		registerEventHandler<EventProcessor,OnyDiesEvent, EVENT_TYPE_ONY_DEATH>
			(this_,&EventProcessor::processOnyDies,mWorldManager->getEventManager());
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
		unregisterEventHandler<EventProcessor,GameOverEvent, EVENT_TYPE_GAMEOVER>
			(this_,&EventProcessor::processGameOver,mWorldManager->getEventManager());
		unregisterEventHandler<EventProcessor,OnyDiesEvent, EVENT_TYPE_ONY_DEATH>
			(this_,&EventProcessor::processOnyDies,mWorldManager->getEventManager());
	}
}

//---------------------------------------------------------------------
// Event callbacks
//---------------------------------------------------------------------
void EventProcessor::processGameOver(GameOverEventPtr evt)
{
	if (mWorldManager.get())
	{
		//TODO: Additional stuff if required
		if (evt->isWin())
			mWorldManager->win();
		else mWorldManager->lose();
	}
}
void EventProcessor::processOnyDies(OnyDiesEventPtr evt)
{
	if (mWorldManager.get())
	{
		//TODO: Additional stuff as needed
		mWorldManager->onyDied();
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

void EventProcessor::processCharactersCollision(CharactersCollisionEventPtr evt)
{
	if (evt->getCharacter1() && evt->getCharacter2())
	{
		Ogre::String characters = evt->getCharacter1()->getName() + "," + evt->getCharacter2()->getName();
		Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCharactersCollision (" + characters + ")");
		//TODO: Handle weapon->enemy collisions, so their health can be modified as well
		GameObjectOnyPtr ony;
		ony.reset();
		if (evt->getCharacter1()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
		{
			ony = boost::dynamic_pointer_cast<GameObjectOny>(evt->getCharacter1());
		}
		else if (evt->getCharacter2()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
		{
			ony = boost::dynamic_pointer_cast<GameObjectOny>(evt->getCharacter2());
		}
		if (ony.get())
		{
			ony->decreaseHP();
		}
	}
	else Ogre::LogManager::getSingleton().logMessage("EventProcessor: empty characters!");
}

void EventProcessor::processCharacterInTrigger(CharacterInTriggerEventPtr evt)
{
	//Ogre::LogManager::getSingleton().logMessage("* Character: " + evt->getCharacter()->getName());
	//Ogre::LogManager::getSingleton().logMessage("* Trigger: " + evt->getTrigger()->getName());

	if (evt->getCharacter() && evt->getTrigger() && evt->getTrigger()->isEnabled())
	{
		if (evt->getCharacter()->getType().compare(GAME_OBJECT_TYPE_ONY) == 0)
		{
			Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCharacterTrigger (ONY)");
			
			GameObjectOnyPtr ony = boost::dynamic_pointer_cast<GameObjectOny>(evt->getCharacter());

			if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_TRIGGERBOX) == 0) 
			{
				//GameObjectTriggerBoxPtr tmpObject = boost::dynamic_pointer_cast<GameObjectTriggerBox>(evt->getTrigger());
				GameOverEventPtr evt=GameOverEventPtr(new GameOverEvent(true));
				mWorldManager->addEvent(evt);
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_TRIGGERCAPSULE) == 0) 
			{	
				//GameObjectTriggerCapsulePtr tmpObject = boost::dynamic_pointer_cast<GameObjectTriggerCapsule>(evt->getTrigger());
				GameOverEventPtr evt=GameOverEventPtr(new GameOverEvent(true));
				mWorldManager->addEvent(evt);
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_ITEM_1UP) == 0) 
			{
				GameObjectItem1UPPtr tmpObject = boost::dynamic_pointer_cast<GameObjectItem1UP>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->takeItem1UP(tmpObject, ony);
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_ITEM_MAXHP) == 0) 
			{
				GameObjectItemMaxHPPtr tmpObject = boost::dynamic_pointer_cast<GameObjectItemMaxHP>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->takeItemMaxHP(tmpObject,ony);
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_HEART) == 0) 
			{
				GameObjectHeartPtr tmpObject = boost::dynamic_pointer_cast<GameObjectHeart>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->takeItemHeart(tmpObject,ony);
			}
			else if (evt->getTrigger()->getType().compare(GAME_OBJECT_TYPE_DIAMOND) == 0) 
			{
				GameObjectDiamondPtr tmpObject = boost::dynamic_pointer_cast<GameObjectDiamond>(evt->getTrigger());
				Application::getInstance()->getGameWorldManager()->takeItemDiamond(tmpObject,ony);
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
			//TODO else if block, 
			//same with rest of game object items which need trigger actions
		}
		else 
		{
			//Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCharacterTrigger (OTHER)");
		}
	}
	else 
	{
		//Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCharacterTrigger (NULL OR NOT ENABLED)");
	}
}
void EventProcessor::processClearQueue(ClearQueueEventPtr evt)
{
	if (mWorldManager)
		mWorldManager->clearEvents();
}