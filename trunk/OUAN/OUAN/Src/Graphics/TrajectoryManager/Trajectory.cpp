#include "Trajectory.h"
#include "TrajectoryNode.h"
#include "../Line3D/Line3D.h"
using namespace OUAN;

Trajectory::Trajectory()
{
	loopTrajectory=true;
}

Trajectory::~Trajectory()
{

}
void Trajectory::init(std::string name,Ogre::SceneManager * pSceneManager,Ogre::SceneNode * debugObjects)
{
	mName=name;
	mSceneManager=pSceneManager;
	mDebugObjects=debugObjects->createChildSceneNode("trajectory#"+mName);
	mDebugObjects->setVisible(false);
}

std::string Trajectory::getName( )
{
	return mName;
}

bool Trajectory::getLoopTrajectory() const
{
	return loopTrajectory;
}
void Trajectory::setLoopTrajectory(bool loopTrajectory)
{
	this->loopTrajectory=loopTrajectory;
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
	//Ogre::LogManager::getSingleton().logMessage("Updating trajectory camera "+Ogre::StringConverter::toString(Ogre::Real(totalTime)));

	double currentSpeed;

	//currentSpeed= (1-totalDistance/trajectoryNodes[currentNode]->getPosition())*trajectoryNodes[currentNode]->getSceneNode()->getPosition()+
	//	(totalTime/trajectoryNodes[currentNode]->getSpeed())*trajectoryNodes[nextNode]->getSceneNode()->getPosition();

	currentSpeed=trajectoryNodes[currentNode]->getSpeed();

	distanceToNextNode-=elapsedTime*currentSpeed;

	//Calculate next node
	nextNode=getNextNode();

	//Calculate current node
	if(distanceToNextNode<0)
	{
		//calculate remaining elapsed time, which will be used for the next node
		elapsedTime=(-distanceToNextNode)/currentSpeed;

		if(currentNode+1>= trajectoryNodes.size())
		{
			//If we do not want to loop the trajectory we return and leave it where it is
			if (!loopTrajectory)
			{
				setCurrentNode(trajectoryNodes.size()-1);
				return;
			}
			else
			{
				//We set current node to the starting trajectory node
				setCurrentNode(0);
			}
		}
		else
		{
			setCurrentNode(currentNode+1);
		}

		//calculate displacement for remaining elapsed time
		currentSpeed=trajectoryNodes[currentNode]->getSpeed();
		distanceToNextNode-=elapsedTime*currentSpeed;
	}

	//Calculate next node
	nextNode=getNextNode();

	//Ogre::LogManager::getSingleton().logMessage("Updating orientation "+Ogre::StringConverter::toString(currentPosition));

	//Calculate current position
	Vector3 direction;
	direction=trajectoryNodes[nextNode]->getSceneNode()->getPosition()-trajectoryNodes[currentNode]->getSceneNode()->getPosition();
	direction.normalise();
	currentPosition=currentPosition+direction*currentSpeed*elapsedTime;

	//Calculate current orientation
	currentOrientation= Quaternion::Slerp(1-(distanceToNextNode/completeDistanceToNextNode), 
		trajectoryNodes[currentNode]->getSceneNode()->getOrientation(), 
		trajectoryNodes[nextNode]->getSceneNode()->getOrientation(),true);

	//Ogre::LogManager::getSingleton().logMessage("Updating position "+Ogre::StringConverter::toString(currentPosition));
}

OUAN::Quaternion Trajectory::getCurrentOrientation()
{
	return currentOrientation;
}

OUAN::Vector3 Trajectory::getCurrentPosition()
{
	return currentPosition;
}

void Trajectory::clear()
{
	reset();
	unsigned int i;

	mDebugObjects->removeAndDestroyAllChildren();

	for(i=0;i<trajectoryNodes.size();i++)
	{
		delete trajectoryNodes[i];
	}	
	trajectoryNodes.clear();
}

void Trajectory::setCurrentNode(int node)
{
	currentNode=node;
	totalTime=0;
	if(trajectoryNodes.size()>0)
	{
		currentPosition=trajectoryNodes[currentNode]->getSceneNode()->getPosition();
		currentOrientation=trajectoryNodes[currentNode]->getSceneNode()->getOrientation();
		completeDistanceToNextNode=trajectoryNodes[currentNode]->getSceneNode()->getPosition().distance(trajectoryNodes[getNextNode()]->getSceneNode()->getPosition());
		distanceToNextNode=completeDistanceToNextNode;
	}
}

void Trajectory::reset()
{
	setCurrentNode(0);
}

void Trajectory::addTrajectoryNode(TrajectoryNode * pTrajectoryNode,std::string debugColor)
{
	this->trajectoryNodes.push_back(pTrajectoryNode);

	Ogre::SceneNode * pEntityDebugNode;
	Ogre::Entity * pEntity;

	//create graphics debug objects
	std::string debugName="trajectory#"+mName+"#"+pTrajectoryNode->getSceneNode()->getName();
	pEntityDebugNode=mDebugObjects->createChildSceneNode(debugName);
	pEntityDebugNode->setPosition(pTrajectoryNode->getSceneNode()->getPosition());
	pEntity=mSceneManager->createEntity(debugName,"node.mesh");
	pEntity->setMaterialName(debugColor);
	pEntity->setVisible(false);
	pEntityDebugNode->setScale(Vector3(0.8,0.8,0.8));
	pEntityDebugNode->setVisible(false);
	pEntityDebugNode->attachObject(pEntity);

	if(trajectoryNodes.size()>=2)
	{
		Line3D *myLine; 
		//create graphics debug objects
		myLine = new Line3D();
		myLine->addPoint(pTrajectoryNode->getSceneNode()->getPosition());
		myLine->addPoint(trajectoryNodes[trajectoryNodes.size()-2]->getSceneNode()->getPosition());
		myLine->setMaterial(debugColor);
		myLine->drawLines();
		myLine->setVisible(false);
		mDebugObjects->attachObject(myLine);
	}
}

TrajectoryNode* Trajectory::getTrajectoryNode(int index)
{
	if (!trajectoryNodes.empty() && index>=0 && (unsigned)index<trajectoryNodes.size())
	{
		return trajectoryNodes.at(index);
	}
	return NULL;
}
int Trajectory::getNumberOfNodes() const
{
	return (trajectoryNodes.empty())?0:trajectoryNodes.size();
}

TTrajectoryParameters::TTrajectoryParameters()
{

}

TTrajectoryParameters::~TTrajectoryParameters()
{

}



