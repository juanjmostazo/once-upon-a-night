#include "OUAN_Precompiled.h"

#include "TrajectoryManager.h"
#include "Trajectory.h"
#include "TrajectoryNode.h"
#include "WalkabilityMap.h"
#include "../RenderComponent/RenderComponentPositional.h"
#include "../RenderSubsystem.h"
#include "../../Loader/Configuration.h"

using namespace OUAN;

TrajectoryManager::TrajectoryManager()
{
	mSceneManager = 0;
	mDebugObjects = 0;
	trajectoryID = 0;
	mVisible=false;
	mDefaultSpeed = 0;
	mMinNextNodeDistance = 0;
}

TrajectoryManager::~TrajectoryManager()
{

}

void TrajectoryManager::init(RenderSubsystemPtr pRenderSubsystem)
{
	mSceneManager=pRenderSubsystem->getSceneManager();
	
	loadConfig();

	clear();
}

bool TrajectoryManager::loadConfig()
{
	Configuration config;
	std::string value;
	bool success;

	if (config.loadFromFile(TRAJECTORY_CFG))
	{
		config.getOption("DEFAULT_SPEED", value); 
		mDefaultSpeed = atof(value.c_str());

		config.getOption("MIN_NEXT_NODE_DISTANCE", value); 
		mMinNextNodeDistance = atof(value.c_str());

		success = true;
	} 
	else 
	{
		//Logger::getInstance()->log(PHYSICS_CFG + " COULD NOT BE LOADED!");
		success = false;
	}

	//	config.~Configuration();
	return success;
}

void TrajectoryManager::createTrajectory(TTrajectoryParameters tTrajectoryParameters)
{
	unsigned int i;
	Ogre::SceneNode * pSceneNode;
	std::vector<TrajectoryNode *> mTrajectoryNodes;
	TrajectoryNode * pTrajectoryNode;

	Logger::getInstance()->log("[TrajectoryManager] Creating trajectory "+tTrajectoryParameters.name);
	
	trajectoryContainer[tTrajectoryParameters.name]= new Trajectory();
	trajectoryContainer[tTrajectoryParameters.name]->setVisible(mVisible);
	trajectoryContainer[tTrajectoryParameters.name]->init(tTrajectoryParameters.name,mSceneManager,mDebugObjects,TrajectoryManagerPtr(this),mDefaultSpeed,mMinNextNodeDistance);

	for(i=0;i<tTrajectoryParameters.tTrajectoryNodeParameters.size();i++)
	{
		//create scene node
		Logger::getInstance()->log("[TrajectoryManager] Creating trajectory node "+tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);
		if(mSceneManager->hasSceneNode(tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName))
		{
			pSceneNode=mSceneManager->getSceneNode(tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);
		}
		else
		{
			pSceneNode=mSceneManager->createSceneNode(tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);
			pSceneNode->setPosition(tTrajectoryParameters.tTrajectoryNodeParameters[i].position);
			pSceneNode->setOrientation(tTrajectoryParameters.tTrajectoryNodeParameters[i].orientation);
		}

		//create trajectory node and set the scene node and the rest of parameters
		pTrajectoryNode = new TrajectoryNode();
		pTrajectoryNode->setSceneNode(pSceneNode);
		pTrajectoryNode->setSpeed(tTrajectoryParameters.tTrajectoryNodeParameters[i].speed);

		mTrajectoryNodes.push_back(pTrajectoryNode);
	}

	trajectoryContainer[tTrajectoryParameters.name]->setTrajectoryNodes(mTrajectoryNodes,"blue");
}

void TrajectoryManager::createWalkabilityMap(TWalkabilityMapParameters tWalkabilityMapParameters)
{
	WalkabilityMap * pWalkabilityMap;

	Logger::getInstance()->log("[TrajectoryManager] Creating walkability map "+tWalkabilityMapParameters.name);

	pWalkabilityMap= new WalkabilityMap();

	pWalkabilityMap->setVisible(mVisible);

	pWalkabilityMap->init(tWalkabilityMapParameters,mSceneManager,mDebugObjects);

	walkabilityMapContainer[tWalkabilityMapParameters.name]=pWalkabilityMap;

	////walkabilityMapContainer[tWalkabilityMapParameters.name]->pathFinding(
	////	mSceneManager->getSceneNode("tree1#4"),mSceneManager->getSceneNode("terrain#tower1"));
}

void TrajectoryManager::clear()
{
	TTrajectoryIterator tit;
	TWalkabilityMapIterator twalk_it;

	Logger::getInstance()->log("[TrajectoryManager] Clearing All Trajectories and Walkability maps");

	for(twalk_it=walkabilityMapContainer.begin();twalk_it!=walkabilityMapContainer.end();twalk_it++)
	{
		twalk_it->second->destroyDebugNodes();
	}

	for(tit=trajectoryContainer.begin();tit!=trajectoryContainer.end();tit++)
	{
		tit->second->destroyDebugNodes();
	}

	trajectoryContainer.clear();
	walkabilityMapContainer.clear();

	if(mSceneManager->hasSceneNode("trajectory manager debug"))
	{
		mDebugObjects->detachAllObjects();
		mDebugObjects->removeAndDestroyAllChildren();

		mSceneManager->destroySceneNode(mDebugObjects);
	}

	mDebugObjects=mSceneManager->getRootSceneNode()->createChildSceneNode("trajectory manager debug");
	mSceneManager->getRootSceneNode()->removeChild(mDebugObjects->getName());
}

Trajectory * TrajectoryManager::getTrajectoryInstance(std::string parent)
{
	Trajectory * pTrajectory;

	pTrajectory = new Trajectory();

	pTrajectory->init("trajectory#"+Ogre::StringConverter::toString(trajectoryID++),mSceneManager,mDebugObjects,TrajectoryManagerPtr(this),mDefaultSpeed,mMinNextNodeDistance);

	trajectoryContainer[pTrajectory->getName()]=pTrajectory;

	pTrajectory->setParent(parent);

	return pTrajectory;
}

bool TrajectoryManager::hasTrajectory(std::string name)
{
	TTrajectoryIterator it;

	it=trajectoryContainer.find(name);

	return it!=trajectoryContainer.end();
}

bool TrajectoryManager::hasWalkabilityMap(std::string name)
{
	TWalkabilityMapIterator it;

	it=walkabilityMapContainer.find(name);

	return it!=walkabilityMapContainer.end();
}

void TrajectoryManager::setIdle(Trajectory & trajectory,std::string gameObjectName)
{
		TrajectoryNode * pTrajectoryNode;
		std::vector<TrajectoryNode *> mTrajectoryNodes;
		//create trajectory node and set the scene node and the rest of parameters
		pTrajectoryNode = new TrajectoryNode();
		pTrajectoryNode->setSceneNode(mSceneManager->getSceneNode(gameObjectName));
		pTrajectoryNode->setSpeed(0);

		mTrajectoryNodes.push_back(pTrajectoryNode);

		trajectory.setTrajectoryNodes(mTrajectoryNodes,"green");
}

void TrajectoryManager::setPredefinedTrajectory(Trajectory & trajectory,std::string trajectoryName,std::string debugColor)
{
	unsigned int i;

	TrajectoryNode * pTrajectoryNode;
	std::vector<TrajectoryNode *> mTrajectoryNodes;

	if(hasTrajectory(trajectoryName))
	{
		for(i=0;i<trajectoryContainer[trajectoryName]->getTrajectoryNodes().size();i++)
		{
			//create trajectory node and set the scene node and the rest of parameters
			pTrajectoryNode = new TrajectoryNode();
			pTrajectoryNode->setSceneNode(trajectoryContainer[trajectoryName]->getTrajectoryNodes()[i]->getSceneNode());
			pTrajectoryNode->setSpeed(trajectoryContainer[trajectoryName]->getTrajectoryNodes()[i]->getSpeed());

			mTrajectoryNodes.push_back(pTrajectoryNode);
		}

		trajectory.setTrajectoryNodes(mTrajectoryNodes,debugColor);
	}
	else
	{
		Logger::getInstance()->log("[TrajectoryManager] Trajectory with name "+trajectoryName+" does not exist.");
	}
}

std::vector<Ogre::SceneNode *> TrajectoryManager::calculatePathFinding(std::string walkabilityMapName,std::string source, std::string target)
{
	std::vector<Ogre::SceneNode *> path;
	if(hasWalkabilityMap(walkabilityMapName))
	{
		path=walkabilityMapContainer[walkabilityMapName]->pathFinding(mSceneManager->getSceneNode(source),mSceneManager->getSceneNode(target));
	}
	else
	{

		Logger::getInstance()->log("[TrajectoryManager] Walkability Map with name "+walkabilityMapName+" does not exist.");
	}
	return path;
}

void TrajectoryManager::destroyTrajectory(std::string name)
{
	if(hasTrajectory(name))
	{
		trajectoryContainer[name]->clear();
		delete trajectoryContainer[name];
	}
	else
	{
		Logger::getInstance()->log("[TrajectoryManager] Trajectory with name "+name+" does not exist.");
	}
}

void TrajectoryManager::destroyTrajectory(Trajectory * pTrajectory)
{
	pTrajectory->clear();
	delete pTrajectory;
}

std::string TrajectoryManager::getNearestNodeToTrajectory(std::string trajectory,Vector3 position)
{
	if(hasTrajectory(trajectory))
	{
		return trajectoryContainer[trajectory]->getNearestNode(position);
	}
	else
	{
		Logger::getInstance()->log("[TrajectoryManager] Trajectory with name "+trajectory+" does not exist.");
		return "";
	}
}

void TrajectoryManager::changeWorldTrajectories(int world)
{
	TTrajectoryIterator tit;

	std::string suffix_hide;
	std::string suffix_show;

	if(world==DREAMS)
	{
		suffix_show=SUFFIX_DREAMS;
		suffix_hide=SUFFIX_NIGHTMARES;
	}
	else if(world==NIGHTMARES)
	{
		suffix_show=SUFFIX_NIGHTMARES;
		suffix_hide=SUFFIX_DREAMS;
	}

	for(tit=trajectoryContainer.begin();tit!=trajectoryContainer.end();tit++)
	{
		if(tit->first.size()>=suffix_show.size() && tit->first.substr(tit->first.size()-suffix_show.size(),suffix_show.size()).compare(suffix_show)==0)
		{
			tit->second->setVisible(true);
		}
		else if(tit->first.size()>=suffix_hide.size() && tit->first.substr(tit->first.size()-suffix_hide.size(),suffix_hide.size()).compare(suffix_hide)==0)
		{
			tit->second->setVisible(false);
		}
		else
		{
			tit->second->setVisible(mVisible);
		}
	}
}

void TrajectoryManager::changeWorld(int currentWorld)
{
	if(mVisible)
	{
		if(currentWorld==DREAMS)
		{
			walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_DREAMS]->setVisible(true);
			walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_NIGHTMARES]->setVisible(false);
		}
		else if(currentWorld==NIGHTMARES)
		{
			walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_DREAMS]->setVisible(false);
			walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_NIGHTMARES]->setVisible(true);
		}
		changeWorldTrajectories(currentWorld);
	}
}

void TrajectoryManager::toggleDebugMode(int currentWorld)
{
	mVisible=!mVisible;

	TTrajectoryIterator tit;

	for(tit=trajectoryContainer.begin();tit!=trajectoryContainer.end();tit++)
	{
		tit->second->setVisible(mVisible);
	}

	if(mVisible)
	{
		if(!mDebugObjects->isInSceneGraph())
		{
			mSceneManager->getRootSceneNode()->addChild(mDebugObjects);
		}

		if(currentWorld==DREAMS)
		{
			if (walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_DREAMS])
				walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_DREAMS]->setVisible(true);
			if(walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_NIGHTMARES])
				walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_NIGHTMARES]->setVisible(false);
		}
		else if(currentWorld==NIGHTMARES)
		{
			if (walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_DREAMS])
				walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_DREAMS]->setVisible(false);
			if(walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_NIGHTMARES])
				walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_NIGHTMARES]->setVisible(true);
		}
		changeWorldTrajectories(currentWorld);
	}
	else
	{
		if (walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_DREAMS])
			walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_DREAMS]->setVisible(false);
		if (walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_NIGHTMARES])
		walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_NIGHTMARES]->setVisible(false);

		if(mDebugObjects->isInSceneGraph())
		{
			mSceneManager->getRootSceneNode()->removeChild(mDebugObjects->getName());
		}
	}
}


void TrajectoryManager::updateDebugNodes()
{
	TTrajectoryIterator tit;
	TWalkabilityMapIterator twalk_it;

	if(mVisible)
	{
		for(twalk_it=walkabilityMapContainer.begin();twalk_it!=walkabilityMapContainer.end();twalk_it++)
		{
			twalk_it->second->updateDebugNodes();
		}

		for(tit=trajectoryContainer.begin();tit!=trajectoryContainer.end();tit++)
		{
			tit->second->updateDebugNodes();
		}
	}
}