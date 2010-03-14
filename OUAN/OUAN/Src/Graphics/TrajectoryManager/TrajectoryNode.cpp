#include "TrajectoryNode.h"
using namespace OUAN;

TrajectoryNode::TrajectoryNode()
{

}

TrajectoryNode::~TrajectoryNode()
{

}

Ogre::SceneNode * TrajectoryNode::getSceneNode() const
{
	return mSceneNode;
}
void TrajectoryNode::setSceneNode(Ogre::SceneNode * pSceneNode)
{
	mSceneNode=pSceneNode;
}

double TrajectoryNode::getTimeToNextNode() const
{
	return this->timeToNextNode;
}
void TrajectoryNode::setTimeToNextNode(double timeToNextNode)
{
	this->timeToNextNode=timeToNextNode;
}

TTrajectoryNodeParameters::TTrajectoryNodeParameters()
{

}

TTrajectoryNodeParameters::~TTrajectoryNodeParameters()
{

}