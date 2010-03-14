#include "Trajectory.h"
#include "TrajectoryNode.h"
using namespace OUAN;

Trajectory::Trajectory()
{
	totalTime=0;
	currentNode=0;
	TIME_PER_NODE=3;
}

Trajectory::~Trajectory()
{

}

int Trajectory::getNextNode()
{
	unsigned int nextNode=currentNode+1;
	if(nextNode>=trajectoryNodes.size())
	{
		return 0;
	}
	else
	{
		return nextNode;
	}
}

std::vector<TrajectoryNode *>  Trajectory::getTrajectoryNodes() const
{
	return trajectoryNodes;
}

void Trajectory::update(double elapsedTime)
{
	unsigned int nextNode;

	//Calculate total time
	totalTime+=elapsedTime;
	Ogre::LogManager::getSingleton().logMessage("Updating trajectory camera "+Ogre::StringConverter::toString(Ogre::Real(totalTime)));

	//Calculate current node
	if(totalTime>=TIME_PER_NODE)
	{
		currentNode++;

		if(currentNode>= trajectoryNodes.size())
		{
			currentNode=0;
		}

		totalTime=0;
	}

	//Calculate next node
	nextNode=getNextNode();

	//Calculate current orientation
	currentOrientation= Quaternion::Slerp((totalTime/TIME_PER_NODE), trajectoryNodes[currentNode]->getSceneNode()->getOrientation(), trajectoryNodes[nextNode]->getSceneNode()->getOrientation(),true);

	Ogre::LogManager::getSingleton().logMessage("Updating orientation "+Ogre::StringConverter::toString(currentPosition));

	//Calculate current position
	currentPosition= (1-totalTime/TIME_PER_NODE)*trajectoryNodes[currentNode]->getSceneNode()->getPosition()+
		(totalTime/TIME_PER_NODE)*trajectoryNodes[nextNode]->getSceneNode()->getPosition();

	Ogre::LogManager::getSingleton().logMessage("Updating position "+Ogre::StringConverter::toString(currentPosition));
}

Quaternion Trajectory::getCurrentOrientation()
{
	return currentOrientation;
}

Vector3 Trajectory::getCurrentPosition()
{
	return currentPosition;
}

void Trajectory::reset()
{
	totalTime = 0;
	currentNode = 0;
}

void Trajectory::addTrajectoryNode(Ogre::SceneNode * sceneNode)
{
	TrajectoryNode * pTrajectoryNode;

	pTrajectoryNode = new TrajectoryNode();

	pTrajectoryNode->setSceneNode(sceneNode);

	this->trajectoryNodes.push_back(pTrajectoryNode);
}

TTrajectoryParameters::TTrajectoryParameters()
{

}

TTrajectoryParameters::~TTrajectoryParameters()
{

}



