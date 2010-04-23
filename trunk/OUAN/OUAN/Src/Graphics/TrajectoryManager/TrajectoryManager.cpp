#include "TrajectoryManager.h"
#include "Trajectory.h"
#include "TrajectoryNode.h"
#include "WalkabilityMap.h"
#include "../RenderComponent/RenderComponentPositional.h"
#include "../RenderSubsystem.h"
using namespace OUAN;

TrajectoryManager::TrajectoryManager()
{
	mSceneManager = 0;
	mDebugObjects = 0;
	trajectoryID = 0;
	mVisible=false;
}

TrajectoryManager::~TrajectoryManager()
{

}

void TrajectoryManager::init(RenderSubsystemPtr pRenderSubsystem)
{
	mSceneManager=pRenderSubsystem->getSceneManager();

	clear();

}

void TrajectoryManager::createTrajectory(TTrajectoryParameters tTrajectoryParameters)
{
	unsigned int i;
	Ogre::SceneNode * pSceneNode;
	std::vector<TrajectoryNode *> trajectoryNodes;
	TrajectoryNode * pTrajectoryNode;
	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating trajectory "+tTrajectoryParameters.name);
	
	trajectoryContainer[tTrajectoryParameters.name]= new Trajectory();

	trajectoryContainer[tTrajectoryParameters.name]->setVisible(mVisible);

	trajectoryContainer[tTrajectoryParameters.name]->init(tTrajectoryParameters.name,mSceneManager,mDebugObjects,TrajectoryManagerPtr(this));

	for(i=0;i<tTrajectoryParameters.tTrajectoryNodeParameters.size();i++)
	{
		//create scene node
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating trajectory node "+tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);
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

		trajectoryNodes.push_back(pTrajectoryNode);
	}

	trajectoryContainer[tTrajectoryParameters.name]->setTrajectoryNodes(trajectoryNodes,"blue");


}

void TrajectoryManager::createWalkabilityMap(TWalkabilityMapParameters tWalkabilityMapParameters)
{
	WalkabilityMap * pWalkabilityMap;

	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating walkability map "+tWalkabilityMapParameters.name);

	pWalkabilityMap= new WalkabilityMap();

	pWalkabilityMap->setVisible(mVisible);

	pWalkabilityMap->init(tWalkabilityMapParameters,mSceneManager,mDebugObjects);

	walkabilityMapContainer[tWalkabilityMapParameters.name]=pWalkabilityMap;


	////walkabilityMapContainer[tWalkabilityMapParameters.name]->pathFinding(
	////	mSceneManager->getSceneNode("tree1#4"),mSceneManager->getSceneNode("terrain#tower1"));

}

void TrajectoryManager::clear()
{
	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Clearing All Trajectories and Walkability maps");

	trajectoryContainer.clear();
	walkabilityMapContainer.clear();

	if(mSceneManager->hasSceneNode("trajectory manager debug"))
	{
		mDebugObjects->detachAllObjects();
		mDebugObjects->removeAndDestroyAllChildren();

		mSceneManager->destroySceneNode(mDebugObjects);
	}

	mDebugObjects=mSceneManager->getRootSceneNode()->createChildSceneNode("trajectory manager debug");
	//mDebugObjects->setVisible(false);
}

Trajectory * TrajectoryManager::getTrajectoryInstance()
{
	Trajectory * pTrajectory;

	pTrajectory = new Trajectory();

	pTrajectory->init("trajectory#"+Ogre::StringConverter::toString(trajectoryID++),mSceneManager,mDebugObjects,TrajectoryManagerPtr(this));

	trajectoryContainer[pTrajectory->getName()]=pTrajectory;

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

void TrajectoryManager::stopTrajectory(Trajectory & trajectory)
{
	trajectory.setStop(true);
}

void TrajectoryManager::setIdle(Trajectory & trajectory,std::string gameObjectName)
{
		TrajectoryNode * pTrajectoryNode;
		std::vector<TrajectoryNode *> trajectoryNodes;
		//create trajectory node and set the scene node and the rest of parameters
		pTrajectoryNode = new TrajectoryNode();
		pTrajectoryNode->setSceneNode(mSceneManager->getSceneNode(gameObjectName));
		pTrajectoryNode->setSpeed(0);

		trajectoryNodes.push_back(pTrajectoryNode);

		trajectory.setTrajectoryNodes(trajectoryNodes,"green");

		trajectory.setStop(true);
}

void TrajectoryManager::setPredefinedTrajectory(Trajectory & trajectory,std::string trajectoryName,std::string debugColor)
{
	unsigned int i;

	TrajectoryNode * pTrajectoryNode;
	std::vector<TrajectoryNode *> trajectoryNodes;

	if(hasTrajectory(trajectoryName))
	{
		for(i=0;i<trajectoryContainer[trajectoryName]->getTrajectoryNodes().size();i++)
		{
			//create trajectory node and set the scene node and the rest of parameters
			pTrajectoryNode = new TrajectoryNode();
			pTrajectoryNode->setSceneNode(trajectoryContainer[trajectoryName]->getTrajectoryNodes()[i]->getSceneNode());
			pTrajectoryNode->setSpeed(trajectoryContainer[trajectoryName]->getTrajectoryNodes()[i]->getSpeed());

			trajectoryNodes.push_back(pTrajectoryNode);
		}

		trajectory.setTrajectoryNodes(trajectoryNodes,debugColor);
	}
	else
	{
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Trajectory with name "+trajectoryName+" does not exist.");
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

		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Walkability Map with name "+walkabilityMapName+" does not exist.");
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
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Trajectory with name "+name+" does not exist.");
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
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Trajectory with name "+trajectory+" does not exist.");
		return "";
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
	}
	else
	{
		walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_DREAMS]->setVisible(false);
		walkabilityMapContainer[DEFAULT_WALKABILITY_MAP_NIGHTMARES]->setVisible(false);
	}

}
