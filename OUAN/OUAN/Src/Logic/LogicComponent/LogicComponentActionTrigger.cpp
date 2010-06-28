#include "OUAN_Precompiled.h"

#include "LogicComponentActionTrigger.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectTripolloDreams.h"
#include "../../Game/GameObject/GameObjectPortal.h"
#include "../../Event/EventDefs.h"

using namespace OUAN;

LogicComponentActionTrigger::LogicComponentActionTrigger(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_TRIGGER_ACTION)
{
	triggerPlatformBigName = "trigger-action#platform_big";
	portalPlatformBigName = "changeworld#platform_big";
	portalPlatformBigMaxDistance = 300;
}

LogicComponentActionTrigger::~LogicComponentActionTrigger()
{

}

void LogicComponentActionTrigger::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		if (getParent()->getName().compare(triggerPlatformBigName)==0)
		{
			processActionPlatformBig();
		}
	}
}

void LogicComponentActionTrigger::processEnterTrigger(GameObjectPtr pGameObject)
{
	
}

void LogicComponentActionTrigger::processExitTrigger(GameObjectPtr pGameObject)
{
	
}

void LogicComponentActionTrigger::processActionPlatformBig()
{
	//Logger::getInstance()->log("@@ PROCESS ACTION PLATFORM BIG WITH ONY");

	///////////////////

	GameObjectPortalPtr portalPlatformBig;
	bool portalPlatformBigFound = false;
	bool allTripollosAreDisabled = true;

	///////////////////

	TGameObjectPortalContainer::iterator itPortal;
	TGameObjectPortalContainer * containerPortal = 
		Application::getInstance()->getGameWorldManager()->getGameObjectPortalContainer();

	for(itPortal = containerPortal->begin(); itPortal != containerPortal->end(); itPortal++)
	{
		GameObjectPortalPtr portal = (*itPortal);

		if (portal->getName().compare(portalPlatformBigName) == 0)
		{
			portalPlatformBig = portal;
			portalPlatformBigFound = true;
			break;
		}
	}

	///////////////////

	if (!portalPlatformBigFound)
	{
		Logger::getInstance()->log("LogicComponentActionTrigger::processActionPlatformBig() [ERROR]: portalPlatformBig not found");
	}

	///////////////////

	TGameObjectTripolloDreamsContainer::iterator itTripollo;
	TGameObjectTripolloDreamsContainer * containerTripollo = 
		Application::getInstance()->getGameWorldManager()->getGameObjectTripolloDreamsContainer();

	for(itTripollo = containerTripollo->begin(); itTripollo != containerTripollo->end(); itTripollo++)
	{
		GameObjectTripolloDreamsPtr tripollo = (*itTripollo);

		double distanceToPortal = tripollo->getRenderComponentPositional()->getPosition().distance(
			portalPlatformBig->getRenderComponentPositional()->getPosition());

		//Logger::getInstance()->log("@@ " + tripollo->getName() + " -> " + Ogre::StringConverter::toString(Ogre::Real(distanceToPortal)));

		if (distanceToPortal <= portalPlatformBigMaxDistance)
		{
			//Logger::getInstance()->log("@@ " + tripollo->getName() + " -> IN! -> " + Ogre::StringConverter::toString(tripollo->isEnabled()));	

			if (tripollo->isEnabled())
			{
				allTripollosAreDisabled = false;
				break;
			}
		}
	}

	///////////////////

	RenderComponentEntityPtr entityTripollo = (Application::getInstance()->getGameWorldManager()->getWorld()==DREAMS)
		? portalPlatformBig->getRenderComponentEntityDreams()
		: portalPlatformBig->getRenderComponentEntityNightmares();

	RenderComponentGlowPtr glowTripollo = (Application::getInstance()->getGameWorldManager()->getWorld()==DREAMS)
		? portalPlatformBig->getRenderComponentGlowDreams()
		: portalPlatformBig->getRenderComponentGlowNightmares();

	entityTripollo->setVisible(allTripollosAreDisabled);
	glowTripollo->setVisible(allTripollosAreDisabled);
}

TLogicComponentActionTriggerParameters::TLogicComponentActionTriggerParameters() : TLogicComponentParameters()
{

}

TLogicComponentActionTriggerParameters::~TLogicComponentActionTriggerParameters()
{

}
