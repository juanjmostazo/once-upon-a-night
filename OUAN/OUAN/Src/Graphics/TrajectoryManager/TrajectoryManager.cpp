#include "TrajectoryManager.h"
#include "Trajectory.h"
#include "TrajectoryNode.h"
using namespace OUAN;

TrajectoryManager::TrajectoryManager()
{
	mSceneManager = 0;
	mTrajectory = 0;
	trajectoryExists=false;
}

TrajectoryManager::~TrajectoryManager()
{

}

void TrajectoryManager::init(Ogre::SceneManager * pSceneManager)
{
	mSceneManager=pSceneManager;

	clear();
}

void TrajectoryManager::createTrajectory(TTrajectoryParameters tTrajectoryParameters)
{
	unsigned int i;
	Ogre::SceneNode * pSceneNode;

	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating trajectory "+tTrajectoryParameters.name);
	
	mTrajectory= new Trajectory();

	for(i=0;i<tTrajectoryParameters.tTrajectoryNodeParameters.size();i++)
	{
		Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Creating trajectory node "+tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);
		pSceneNode=mSceneManager->createSceneNode(tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);

		pSceneNode->setPosition(tTrajectoryParameters.tTrajectoryNodeParameters[i].position);
		pSceneNode->setOrientation(tTrajectoryParameters.tTrajectoryNodeParameters[i].orientation);

		mTrajectory->addTrajectoryNode(pSceneNode);
	}

	trajectoryExists=true;
}

void TrajectoryManager::clear()
{
	Ogre::LogManager::getSingleton().logMessage("[TrajectoryManager] Clearing All Trajectories");
	delete mTrajectory;
	trajectoryExists=false;
	//trajectoryContainer.clear();
}

Trajectory * TrajectoryManager::getTrajectory(std::string name) const
{
	return mTrajectory;
}
bool TrajectoryManager::hasTrajectory(std::string name)
{
	return trajectoryExists;
}
