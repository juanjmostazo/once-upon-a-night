#include "Trajectory.h"
#include "TrajectoryManager.h"
#include "TrajectoryNode.h"
#include "../Line3D/Line3D.h"
#include "../../Utils/Utils.h"
#include <stdlib.h>
using namespace OUAN;

Trajectory::Trajectory()
{

}

Trajectory::~Trajectory()
{

}
void Trajectory::init(std::string name,Ogre::SceneManager * pSceneManager,Ogre::SceneNode * debugObjects,TrajectoryManagerPtr pTrajectoryManager)
{
	mName=name;
	mSceneManager=pSceneManager;
	mTrajectoryManager=pTrajectoryManager;
	mDebugObjects=debugObjects->createChildSceneNode("trajectory#"+mName);
	mNextMovement=Vector3::ZERO;
	mTrajectory2d=false;
	mLoopTrajectory=true;
	mState=IDLE;
	mVisible=false;
	mDefaultSpeed=15;
	mRecalculateTime=0.2+Utils::Random::getInstance()->getRandomDouble();
	mTrajectoryNodes.clear();
	mCurrentNode=0;
	mMinNextNodeDistance=5;
}

std::string Trajectory::getParent() const
{
	return mParent;
}
void Trajectory::setParent(std::string parent)
{
	mParent=parent;
}

void Trajectory::setAs2DTrajectory()
{
	mTrajectory2d=true;
}

void Trajectory::setAs3DTrajectory()
{
	mTrajectory2d=false;
}

double Trajectory::calculateDistance(std::string node1,std::string node2)
{
	Ogre::Vector3 v1;
	Ogre::Vector3 v2;

	v1=mSceneManager->getSceneNode(node1)->getPosition();
	v2=mSceneManager->getSceneNode(node2)->getPosition();

	if(mTrajectory2d)
	{
		v1.y=0;
		v2.y=0;
	}

	return v1.distance(v2);
}

std::string Trajectory::getName()
{
	return mName;
}

bool Trajectory::getLoopTrajectory() const
{
	return mLoopTrajectory;
}
void Trajectory::setLoopTrajectory(bool loopTrajectory)
{
	mLoopTrajectory=loopTrajectory;
}

int Trajectory::getNextNode(int node)
{
	unsigned int nextNode=node+1;
	if(nextNode>=mTrajectoryNodes.size())
	{
		return 0;
	}
	else
	{
		return nextNode;
	}
}

int Trajectory::getNextNode()
{
	unsigned int nextNode=mCurrentNode+1;
	if(nextNode>=mTrajectoryNodes.size())
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
	return mTrajectoryNodes;
}

void Trajectory::updateChase()
{
	TrajectoryNode * pTrajectoryNode;
	clear();

	pTrajectoryNode = new TrajectoryNode();
	pTrajectoryNode->setSceneNode(mSceneManager->getSceneNode(mParent));
	pTrajectoryNode->setSpeed(mDefaultSpeed);

	pushBackNode(pTrajectoryNode,"red");

	pTrajectoryNode = new TrajectoryNode();
	pTrajectoryNode->setSceneNode(mSceneManager->getSceneNode(mPathfindingTarget));
	pTrajectoryNode->setSpeed(mDefaultSpeed);

	pushBackNode(pTrajectoryNode,"red");

	reset();
}

Ogre::Vector3 Trajectory::calculateNextMovement(std::string source,std::string target,bool Trajectory2d,double speed,double elapsedTime)
{
	//Calculate next movement
	Ogre::Vector3 nextMovement;
	Ogre::Vector3 direction;
	direction=mSceneManager->getSceneNode(target)->getPosition()-mSceneManager->getSceneNode(source)->getPosition();
	direction.normalise();
	nextMovement=direction*speed*elapsedTime;

	if(Trajectory2d)
	{
		nextMovement.y=0;
	}

	return nextMovement;
}

Ogre::Vector3 Trajectory::calculateNextPosition(std::string source,std::string target,bool Trajectory2d,double speed,double elapsedTime)
{
	//Calculate next position
	Ogre::Vector3 nextPosition;
	Ogre::Vector3 direction;
	direction=mSceneManager->getSceneNode(target)->getPosition()-mSceneManager->getSceneNode(source)->getPosition();
	direction.normalise();
	nextPosition=mSceneManager->getSceneNode(source)->getPosition()+direction*speed*elapsedTime;

	if(Trajectory2d)
	{
		nextPosition.y=0;
	}

	return nextPosition;
}

Ogre::Quaternion Trajectory::calculateNextOrientation(std::string lastNode,std::string source,std::string target,bool Trajectory2d,double speed,double elapsedTime)
{
	Ogre::Quaternion nextOrientation;

	Ogre::SceneNode * sourceNode=mSceneManager->getSceneNode(source);
	Ogre::SceneNode * targetNode=mSceneManager->getSceneNode(target);

	double distanceSourceTarget=calculateDistance(source,target);
	double fT;

	if(distanceSourceTarget!=0)
	{
		fT=calculateDistance(lastNode,target)/distanceSourceTarget;
	}
	else
	{
		fT=1;
	}

	nextOrientation=Ogre::Quaternion::Slerp(fT,sourceNode->getOrientation(),targetNode->getOrientation());

	return nextOrientation;
}

bool Trajectory::isLastNode()
{
	return (getNextNode()==0);
}

void Trajectory::advanceToNextNode(double elapsedTime)
{
	setCurrentNode(getNextNode());
	//switch(mState)
	//{
	//case PATH_FINDING:
	//	break;
	//case IDLE:
	//	break;
	//case CHASE:
	//	break;
	//case PATH_FINDING_TO_PREDEFINED_TRAJECTORY:
	//	break;
	//case PATH_FINDING_TO_IDLE:
	//	break;
	//case PREDEFINED_TRAJECTORY:
	//	break;
	//default:
		//break;	
	//}

	//std::string target;
	//setCurrentNode(getNextNode());
	//target=mTrajectoryNodes[getNextNode()]->getSceneNode()->getName();
	//mNextMovement=calculateNextMovement(mParent,target,mTrajectory2d,currentSpeed,elapsedTime);
}

void Trajectory::advanceToLastNode(double elapsedTime)
{
	std::string currentNodeName;

	currentNodeName=mTrajectoryNodes[mCurrentNode]->getSceneNode()->getName();
	switch(mState)
	{
	case PATH_FINDING:
		activateIdle(mParent,currentNodeName,mWalkabilityMap);
		break;
	case IDLE:
		break;
	case CHASE:
		break;
	case PATH_FINDING_TO_PREDEFINED_TRAJECTORY:
		activatePredefinedTrajectory(mPredefinedTrajectory);
		break;
	case PATH_FINDING_TO_IDLE:
		activateIdle(mParent,currentNodeName,mWalkabilityMap);
		break;
	case PREDEFINED_TRAJECTORY:
		activateIdle(mParent,currentNodeName,mWalkabilityMap);
		break;
	default:
		break;	
	}
}

void Trajectory::update(double elapsedTime)
{
	std::string target;
	std::string source;
	std::string lastNode;
	double currentSpeed;
	double distanceToTarget;

	if(isEmpty()) return;

	lastNode=mTrajectoryNodes[mCurrentNode]->getSceneNode()->getName();
	target=mTrajectoryNodes[getNextNode()]->getSceneNode()->getName();
	source=mParent;

	currentSpeed=mTrajectoryNodes[mCurrentNode]->getSpeed();
	
	mNextMovement=calculateNextMovement(source,target,mTrajectory2d,currentSpeed,elapsedTime);
	mCurrentPosition=calculateNextPosition(source,target,mTrajectory2d,currentSpeed,elapsedTime);
	mCurrentOrientation=calculateNextOrientation(lastNode,source,target,mTrajectory2d,currentSpeed,elapsedTime);

	distanceToTarget=calculateDistance(target,source);

	if(distanceToTarget<=mMinNextNodeDistance)
	{
		if(isLastNode() && !mLoopTrajectory)
		{
			advanceToLastNode(elapsedTime);
		}
		else
		{
			advanceToNextNode(elapsedTime);
		}
	}

	updateTrajectoryNodes(elapsedTime);

	//Ogre::LogManager::getSingleton().logMessage("Updating position "+Ogre::StringConverter::toString(currentPosition));
	//Ogre::LogManager::getSingleton().logMessage("Updating orientation "+Ogre::StringConverter::toString(currentPosition));
	//Ogre::LogManager::getSingleton().logMessage("Updating nextMovement "+Ogre::StringConverter::toString(nextMovement));
}

void Trajectory::updateTrajectoryNodes(double elapsedTime)
{
	mTimeSinceLastUpdateNodes+=elapsedTime;
	if(mTimeSinceLastUpdateNodes>mRecalculateTime)
	{
		mTimeSinceLastUpdateNodes=0;
		mRecalculateTime=0.2+Utils::Random::getInstance()->getRandomDouble();

		switch(mState)
		{
		case PATH_FINDING:
			updatePathfinding();
			break;
		case IDLE:
			break;
		case CHASE:
			updateChase();
			break;
		case PATH_FINDING_TO_PREDEFINED_TRAJECTORY:
			break;
		case PATH_FINDING_TO_IDLE:
			break;
		case PREDEFINED_TRAJECTORY:
			break;
		default:
			break;	
		}
	}
}

OUAN::Quaternion Trajectory::getCurrentOrientation()
{
	return mCurrentOrientation;
}

OUAN::Vector3 Trajectory::getCurrentPosition()
{
	return mCurrentPosition;
}

OUAN::Vector3 Trajectory::getNextMovement()
{
	return mNextMovement;
}

bool Trajectory::isEmpty()
{
	return mTrajectoryNodes.size()==0;
}

TrajectoryNode * Trajectory::getCurrentNode()
{
	return mTrajectoryNodes[mCurrentNode];
}

void Trajectory::clear()
{
	myLines.clear();
	myNodes.clear();

	while(mTrajectoryNodes.size()>0)
	{
		popBackNode();
	}

	mDebugObjects->detachAllObjects();
	mDebugObjects->removeAndDestroyAllChildren();

	reset();
}

void Trajectory::setCurrentNode(int node)
{
	mCurrentNode=node;

	//if(mTrajectoryNodes.size()>0)
	//{
	//	//Ogre::LogManager::getSingleton().logMessage("Current Node "+mTrajectoryNodes[node]->getSceneNode()->getName());
	//	//Ogre::LogManager::getSingleton().logMessage("Current Node "+Ogre::StringConverter::toString(currentNode));

	//	//mCurrentPosition=mTrajectoryNodes[currentNode]->getSceneNode()->getPosition();
	//	//mCurrentOrientation=mTrajectoryNodes[currentNode]->getSceneNode()->getOrientation();

	//}
}

void Trajectory::reset()
{
	setCurrentNode(0);
}

void Trajectory::setTrajectoryNodes(std::vector<TrajectoryNode *> mTrajectoryNodes,std::string debugColor)
{
	unsigned int i;
	TrajectoryNode * pTrajectoryNode;

	clear();

	for(i=0;i<mTrajectoryNodes.size();i++)
	{
		pTrajectoryNode=mTrajectoryNodes[i];

		pushBackNode(pTrajectoryNode,debugColor);

	}

	reset();
}

void Trajectory::removeNodeDebugInfo(int node)
{
	mSceneManager->getSceneNode(getEntityDebugName(node))->detachAllObjects();
	mSceneManager->destroySceneNode(getEntityDebugName(node));

	mSceneManager->destroyEntity(getEntityDebugName(node));

	if(mSceneManager->hasSceneNode(getLineDebugName(node)))
	{
		mSceneManager->getSceneNode(getLineDebugName(node))->detachAllObjects();
		mSceneManager->destroySceneNode(getLineDebugName(node));
	}

}

std::string Trajectory::getEntityDebugName(int node)
{
	TrajectoryNode * pTrajectoryNode;

	pTrajectoryNode=mTrajectoryNodes[node];
	return mName+"#"+Ogre::StringConverter::toString(node)+"#"+pTrajectoryNode->getSceneNode()->getName();
}

std::string Trajectory::getLineDebugName(int node)
{
	TrajectoryNode * pTrajectoryNode;

	pTrajectoryNode=mTrajectoryNodes[node];
	return mName+"#"+Ogre::StringConverter::toString(node)+"#line#"+mTrajectoryNodes[node]->getSceneNode()->getName();
}

void Trajectory::createNodeDebugInfo(int node,std::string debugColor)
{
	TrajectoryNode * pTrajectoryNode;

	Ogre::SceneNode * pEntityDebugNode;
	Ogre::SceneNode * pLineDebugNode;
	Ogre::Entity * pEntity;

	pTrajectoryNode=mTrajectoryNodes[node];

	//create graphics debug objects
	std::string entityDebugName=getEntityDebugName(node);
	pEntityDebugNode=mDebugObjects->createChildSceneNode(entityDebugName);
	pEntityDebugNode->setPosition(pTrajectoryNode->getSceneNode()->getPosition());
	pEntityDebugNode->setVisible(mVisible);
	pEntity=mSceneManager->createEntity(entityDebugName,"node.mesh");
	pEntity->setMaterialName(debugColor);
	pEntity->setVisible(mVisible);
	pEntityDebugNode->setScale(Vector3(0.8,0.8,0.8));
	pEntityDebugNode->attachObject(pEntity);

	myNodes[entityDebugName]=pEntity;

	if(mTrajectoryNodes.size()>1)
	{
		std::string lineDebugName=getLineDebugName(node);;
		pLineDebugNode=mDebugObjects->createChildSceneNode(lineDebugName);
		Line3D *myLine; 
		//create graphics debug objects
		myLine = new Line3D();
		myLine->addPoint(mTrajectoryNodes[node]->getSceneNode()->getPosition());
		myLine->addPoint(mTrajectoryNodes[node-1]->getSceneNode()->getPosition());
		myLine->setMaterial(debugColor);
		myLine->drawLines();
		pLineDebugNode->attachObject(myLine);
		pLineDebugNode->setVisible(mVisible);
		myLines[lineDebugName]=myLine;
	}
}

TrajectoryNode* Trajectory::getTrajectoryNode(int index)
{
	if (!mTrajectoryNodes.empty() && index>=0 && (unsigned)index<mTrajectoryNodes.size())
	{
		return mTrajectoryNodes.at(index);
	}
	return NULL;
}
int Trajectory::getNumberOfNodes() const
{
	return (mTrajectoryNodes.empty())?0:mTrajectoryNodes.size();
}

void Trajectory::activateIdle(std::string gameObject,std::string node,std::string walkabilityMap)
{
	mState=PATH_FINDING_TO_IDLE;
	doPathfinding(gameObject,node,walkabilityMap);
}

void Trajectory::activatePathfinding(std::string source,std::string target,std::string walkabilityMap)
{
	mState=PATH_FINDING;
	doPathfinding(source,target,walkabilityMap);
}

void Trajectory::activateChase(std::string source,std::string target)
{
	//TrajectoryNode * pTrajectoryNode;

	mState=CHASE;
	mPathfindingTarget=target;
	updateChase();
}

void Trajectory::activatePathfindingToPredefinedTrajectory(std::string trajectory,std::string gameObject,std::string walkabilityMap)
{
	std::string target;

	//find nearest node
	target=mTrajectoryManager->getNearestNodeToTrajectory(trajectory,
		mSceneManager->getSceneNode(gameObject)->getPosition());

	mPredefinedTrajectory=trajectory;

	mState=PATH_FINDING_TO_PREDEFINED_TRAJECTORY;

	mPathfindingTarget=target;
	mParent=gameObject;
	mWalkabilityMap=walkabilityMap;

	initPathfinding();

	//Ogre::LogManager::getSingleton().logMessage("Pathfinding to predefined trajectory "+trajectory);

}

void Trajectory::activatePredefinedTrajectory(std::string trajectory)
{
	mState=PREDEFINED_TRAJECTORY;

	mLoopTrajectory=true;
	mPredefinedTrajectory=trajectory;
	mTrajectoryManager->setPredefinedTrajectory(*this,trajectory,"green");
}



void Trajectory::doPathfinding(std::string source,std::string target,std::string walkabilityMap)
{
	TrajectoryNode * pTrajectoryNode;

	mLoopTrajectory=false;

	if(source.compare(target)==0)
	{
		clear();
		pTrajectoryNode = new TrajectoryNode();
		pTrajectoryNode->setSceneNode(mSceneManager->getSceneNode(target));
		pTrajectoryNode->setSpeed(15);

		pushBackNode(pTrajectoryNode,"green");
		reset();
	}
	else
	{

		mPathfindingTarget=target;
		mParent=source;
		mWalkabilityMap=walkabilityMap;

		initPathfinding();
		reset();
	}
}

void Trajectory::initPathfinding()
{
	unsigned int i;
	TrajectoryNode * pTrajectoryNode;
	std::vector<Ogre::SceneNode *> path;

	//Ogre::LogManager::getSingleton().logMessage("FULL");

	clear();
	path=mTrajectoryManager->calculatePathFinding(
		mWalkabilityMap,
		mParent,
		mPathfindingTarget);

	for(i=0;i<path.size();i++)
	{
		//create trajectory node and set the scene node and the rest of parameters
		pTrajectoryNode = new TrajectoryNode();
		pTrajectoryNode->setSceneNode(path[i]);
		pTrajectoryNode->setSpeed(15);

		pushBackNode(pTrajectoryNode,"green");
	}
	reset();

}

void Trajectory::recalculatePathfinding()
{
	unsigned int i;
	TrajectoryNode * pTrajectoryNode;
	std::vector<Ogre::SceneNode *> path;
	TrajectoryNode * pCurrentNode;
	TrajectoryNode * pNextNode;
	int nextNode=getNextNode();

	//Ogre::LogManager::getSingleton().logMessage("PARTIAL");

	pCurrentNode = new TrajectoryNode();
	pCurrentNode->setSceneNode(mTrajectoryNodes[mCurrentNode]->getSceneNode());
	pCurrentNode->setSpeed(mTrajectoryNodes[mCurrentNode]->getSpeed());

	pNextNode = new TrajectoryNode();
	pNextNode->setSceneNode(mTrajectoryNodes[nextNode]->getSceneNode());
	pNextNode->setSpeed(mTrajectoryNodes[nextNode]->getSpeed());

	path=mTrajectoryManager->calculatePathFinding(
		mWalkabilityMap,
		mTrajectoryNodes[nextNode]->getSceneNode()->getName(),
		mPathfindingTarget);

	clear();

	pushBackNode(pCurrentNode,"green");
	pushBackNode(pNextNode,"green");
	mCurrentNode=0;

	for(i=1;i<path.size();i++)
	{
		//create trajectory node and set the scene node and the rest of parameters
		pTrajectoryNode = new TrajectoryNode();
		pTrajectoryNode->setSceneNode(path[i]);
		pTrajectoryNode->setSpeed(15);

		pushBackNode(pTrajectoryNode,"green");
	}
}

void Trajectory::updatePathfinding()
{
	int nextNode=getNextNode();

	if( mTrajectoryNodes.size()-(mCurrentNode+1)<=0 ||
		mTrajectoryNodes[nextNode]->getSceneNode()->getName().compare(mPathfindingTarget)==0)
	{
		initPathfinding();
	}
	else
	{
		recalculatePathfinding();
	}
}

void Trajectory::pushBackNode(TrajectoryNode * pTrajectoryNode,std::string debugColor)
{
	mTrajectoryNodes.push_back(pTrajectoryNode);
	createNodeDebugInfo(mTrajectoryNodes.size()-1,debugColor);
}

void Trajectory::popBackNode()
{
	removeNodeDebugInfo(mTrajectoryNodes.size()-1);
	mTrajectoryNodes.pop_back();
}

void Trajectory::setPredefinedTrajectoryFromNode(std::string trajectory,std::string node)
{
	activatePredefinedTrajectory(trajectory);
	unsigned int i;
	int current=-1;
	//Ogre::LogManager::getSingleton().logMessage("setPredefinedTrajectoryFromNode");
	//Ogre::LogManager::getSingleton().logMessage("Predefined Trajectory");

	for(i=0;i<mTrajectoryNodes.size();i++)
	{
		if(mTrajectoryNodes[i]->getSceneNode()->getName().compare(node)==0)
		{
			current=i;
			break;
		}
		//Ogre::LogManager::getSingleton().logMessage("Node "+mTrajectoryNodes[i]->getSceneNode()->getName());
	}

	if(current==-1)
	{
		Ogre::LogManager::getSingleton().logMessage("setPredefinedTrajectoryFromNode Node does not exist");
	}
	else
	{
		//Ogre::LogManager::getSingleton().logMessage("setPredefinedTrajectoryFromNode Node "+node+" "+mTrajectoryNodes[current]->getSceneNode()->getName());
		setCurrentNode(current);
	}

	moveToPredefinedTrajectory=false;
}

std::string Trajectory::getNearestNode(Ogre::Vector3 position)
{
	double minDistance=-1;
	std::string minDistanceName="";
	double distance;
	for(unsigned int i=0;i<mTrajectoryNodes.size();i++)
	{
		distance=mTrajectoryNodes[i]->getSceneNode()->getPosition().distance(position);
		if(minDistance==-1 || distance<minDistance)
		{
			minDistance=distance;
			minDistanceName=mTrajectoryNodes[i]->getSceneNode()->getName();
		}
	}
	return minDistanceName;
}

void Trajectory::setVisible(bool visible)
{
	mVisible=visible;

	std::map<std::string,Line3D *>::iterator it1;

	for(it1=myLines.begin();it1!=myLines.end();it1++)
	{
		it1->second->setVisible(mVisible);
	}

	std::map<std::string,Ogre::Entity *>::iterator it2;

	for(it2=myNodes.begin();it2!=myNodes.end();it2++)
	{
		it2->second->setVisible(mVisible);
	}
}

bool Trajectory::predefinedTrajectoryExists(std::string name)
{
	return mTrajectoryManager->hasTrajectory(name);
}

TTrajectoryParameters::TTrajectoryParameters()
{

}

TTrajectoryParameters::~TTrajectoryParameters()
{

}



