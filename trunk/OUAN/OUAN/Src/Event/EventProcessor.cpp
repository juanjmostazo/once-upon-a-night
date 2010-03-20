#include "EventProcessor.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObject.h"

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
	Ogre::LogManager::getSingleton().logMessage("EventProcessor: processCharacterTrigger");
}