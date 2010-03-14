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
TTrajectoryNodeParameters::TTrajectoryNodeParameters()
{

}

TTrajectoryNodeParameters::~TTrajectoryNodeParameters()
{

}