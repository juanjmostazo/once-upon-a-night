#include "OUAN_Precompiled.h"

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

double TrajectoryNode::getSpeed() const
{
	return this->speed;
}
void TrajectoryNode::setSpeed(double Speed)
{
	this->speed=Speed;
}

TTrajectoryNodeParameters::TTrajectoryNodeParameters()
{

}

TTrajectoryNodeParameters::~TTrajectoryNodeParameters()
{

}