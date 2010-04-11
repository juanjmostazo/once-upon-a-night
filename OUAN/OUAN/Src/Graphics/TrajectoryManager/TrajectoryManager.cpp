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
	trajectoryID=0;
}

TrajectoryManager::~TrajectoryManager()
{

}

void TrajectoryManager::init(RenderSubsystemPtr pRenderSubsystem)
{
	mSceneManager=pRenderSubsystem->getSceneManager();

	mDebugObjects=mSceneManager->getRootSceneNode()->createChildSceneNode("trajectory manager debug");

	mDebugObjects->setVisible(false);

	clear();

}

void TrajectoryManager::createTrajectory(TTrajectoryParameters tTrajectoryParameters)
{
	unsigned int i;
	Ogre::SceneNode * pSceneNode;
	TrajectoryNode * pTrajectoryNode;
	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating trajectory "+tTrajectoryParameters.name);
	
	trajectoryContainer[tTrajectoryParameters.name]= new Trajectory();

	trajectoryContainer[tTrajectoryParameters.name]->init(tTrajectoryParameters.name,mSceneManager,mDebugObjects);

	for(i=0;i<tTrajectoryParameters.tTrajectoryNodeParameters.size();i++)
	{
		//create scene node
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating trajectory node "+tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);
		pSceneNode=mSceneManager->createSceneNode(tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);

		pSceneNode->setPosition(tTrajectoryParameters.tTrajectoryNodeParameters[i].position);
		pSceneNode->setOrientation(tTrajectoryParameters.tTrajectoryNodeParameters[i].orientation);


		//create trajectory node and set the scene node and the rest of parameters
		pTrajectoryNode = new TrajectoryNode();
		pTrajectoryNode->setSceneNode(pSceneNode);
		pTrajectoryNode->setSpeed(tTrajectoryParameters.tTrajectoryNodeParameters[i].speed);

		trajectoryContainer[tTrajectoryParameters.name]->addTrajectoryNode(pTrajectoryNode,"blue");
	}

	trajectoryContainer[tTrajectoryParameters.name]->reset();

}

void TrajectoryManager::createWalkabilityMap(TWalkabilityMapParameters tWalkabilityMapParameters)
{
	WalkabilityMap * pWalkabilityMap;

	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating walkability map "+tWalkabilityMapParameters.name);

	pWalkabilityMap= new WalkabilityMap();

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
		mDebugObjects->removeAndDestroyAllChildren();
	}
}

Trajectory * TrajectoryManager::getTrajectoryInstance()
{
	Trajectory * pTrajectory;
	pTrajectory = new Trajectory();

	pTrajectory->init("trajectory#"+Ogre::StringConverter::toString(trajectoryID++),mSceneManager,mDebugObjects);

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

void TrajectoryManager::setPredefinedTrajectory(Trajectory & trajectory,std::string trajectoryName)
{
	unsigned int i;

	TrajectoryNode * pTrajectoryNode;
	if(hasTrajectory(trajectoryName))
	{
		for(i=0;i<trajectoryContainer[trajectoryName]->getTrajectoryNodes().size();i++)
		{
			//create trajectory node and set the scene node and the rest of parameters
			pTrajectoryNode = new TrajectoryNode();
			pTrajectoryNode->setSceneNode(trajectoryContainer[trajectoryName]->getTrajectoryNodes()[i]->getSceneNode());
			pTrajectoryNode->setSpeed(trajectoryContainer[trajectoryName]->getTrajectoryNodes()[i]->getSpeed());

			trajectory.addTrajectoryNode(pTrajectoryNode,"blue");
		}

		trajectory.reset();
	}
	else
	{
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Trajectory with name "+trajectoryName+" does not exist.");
	}
}

void TrajectoryManager::calculatePathFinding(Trajectory & trajectory,std::string walkabilityMapName,std::string source, std::string target,double speed)
{
	unsigned int i;

	TrajectoryNode * pTrajectoryNode;

	std::vector<Ogre::SceneNode *> path;

	if(hasWalkabilityMap(walkabilityMapName))
	{
		//todo link walkability node with

		path=walkabilityMapContainer[walkabilityMapName]->pathFinding(mSceneManager->getSceneNode(source),mSceneManager->getSceneNode(target));

		trajectory.clear();

		//source node has to be set as trajectory startup
		for(i=0;i<path.size();i++)
		{
			//create trajectory node and set the scene node and the rest of parameters
			pTrajectoryNode = new TrajectoryNode();
			pTrajectoryNode->setSceneNode(path[i]);
			pTrajectoryNode->setSpeed(speed);

			trajectory.addTrajectoryNode(pTrajectoryNode,"green");
		}

	}
	else
	{
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Walkability Map with name "+walkabilityMapName+" does not exist.");
	}
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

void TrajectoryManager::toggleDebugMode()
{
	mDebugObjects->flipVisibility();
}
