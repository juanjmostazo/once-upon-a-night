#include "TrajectoryManager.h"
#include "Trajectory.h"
#include "TrajectoryNode.h"
using namespace OUAN;

TrajectoryManager::TrajectoryManager()
{
	mSceneManager = 0;
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

	trajectory[tTrajectoryParameters.name] = new Trajectory();

	for(i=0;i<tTrajectoryParameters.tTrajectoryNodeParameters.size();i++)
	{
		Ogre::SceneNode * sceneNode;
		TrajectoryNode * trajectoryNode;

		trajectoryNode = new TrajectoryNode();

		sceneNode=mSceneManager->getSceneNode(tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);

		if(!sceneNode)
		{
			mSceneManager->createSceneNode(tTrajectoryParameters.tTrajectoryNodeParameters[i].nodeName);
			sceneNode->setPosition(tTrajectoryParameters.tTrajectoryNodeParameters[i].position);
			sceneNode->setOrientation(tTrajectoryParameters.tTrajectoryNodeParameters[i].orientation);
		}

		trajectoryNode->node=sceneNode;

		trajectory[tTrajectoryParameters.name]->trajectoryNodes.push_back(trajectoryNode);
	}
}

void TrajectoryManager::clear()
{
	trajectory.clear();
}

Trajectory * TrajectoryManager::getTrajectory(std::string name)
{
	return trajectory[name];
}
		