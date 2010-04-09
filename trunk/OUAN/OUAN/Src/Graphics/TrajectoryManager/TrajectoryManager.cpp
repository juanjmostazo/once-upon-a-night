#include "TrajectoryManager.h"
#include "Trajectory.h"
#include "TrajectoryNode.h"
#include "WalkabilityMap.h"
#include "../RenderSubsystem.h"
using namespace OUAN;

TrajectoryManager::TrajectoryManager()
{
	mSceneManager = 0;

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

	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating trajectory "+tTrajectoryParameters.name);
	
	trajectoryContainer[tTrajectoryParameters.name]= new Trajectory();

	for(i=0;i<tTrajectoryParameters.tTrajectoryNodeParameters.size();i++)
	{
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating trajectory node "+tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);
		pSceneNode=mSceneManager->createSceneNode(tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);

		pSceneNode->setPosition(tTrajectoryParameters.tTrajectoryNodeParameters[i].position);
		pSceneNode->setOrientation(tTrajectoryParameters.tTrajectoryNodeParameters[i].orientation);

		trajectoryContainer[tTrajectoryParameters.name]->addTrajectoryNode(pSceneNode,tTrajectoryParameters.tTrajectoryNodeParameters[i].timeToNextNode);
	}
}

void TrajectoryManager::createWalkabilityMap(TWalkabilityMapParameters tWalkabilityMapParameters)
{
	WalkabilityMap * pWalkabilityMap;

	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating walkability map "+tWalkabilityMapParameters.name);

	pWalkabilityMap= new WalkabilityMap();

	pWalkabilityMap->init(tWalkabilityMapParameters,mSceneManager);

	walkabilityMapContainer[tWalkabilityMapParameters.name]=pWalkabilityMap;
}

void TrajectoryManager::clear()
{
	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Clearing All Trajectories and Walkability maps");

	trajectoryContainer.clear();
	walkabilityMapContainer.clear();
}

Trajectory * TrajectoryManager::getTrajectoryInstance(std::string name)
{
	unsigned int i;
	Trajectory * pTrajectory;

	if(hasTrajectory(name))
	{

		pTrajectory = new Trajectory();

		for(i=0;i<trajectoryContainer[name]->getTrajectoryNodes().size();i++)
		{
			pTrajectory->addTrajectoryNode(trajectoryContainer[name]->getTrajectoryNodes()[i]->getSceneNode(),
				trajectoryContainer[name]->getTrajectoryNodes()[i]->getTimeToNextNode()
				);
		}

		pTrajectory->reset();

		return pTrajectory;
	}
	else
	{
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Trajectory with name "+name+" does not exist.");
		return NULL;
	}
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

