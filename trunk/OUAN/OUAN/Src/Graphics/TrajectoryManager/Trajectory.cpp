#include "Trajectory.h"
#include "TrajectoryManager.h"
#include "TrajectoryNode.h"
#include "../Line3D/Line3D.h"
#include "../../Utils/Utils.h"
#include <stdlib.h>
using namespace OUAN;

Trajectory::Trajectory()
{
	loopTrajectory=true;
	mIddle=false;
	mVisible=false;
	mChase=false;
	//double random;

	///* initialize random seed: */
	//srand ( time(NULL) );
	///* generate random number: */
	//random = (rand() % 100)/100;

	recalculateTime=1.5+Utils::Random::getInstance()->getRandomDouble();
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
	lastPathFindingTime=0;
	nextMovement=Vector3::ZERO;
	pathFindingActivated=false;
	twoDimensionsTrajectory=false;
}

void Trajectory::setAs2DTrajectory()
{
	twoDimensionsTrajectory=true;
}

void Trajectory::setAs3DTrajectory()
{
	twoDimensionsTrajectory=false;
}

double Trajectory::calculateDistance(Ogre::Vector3 v1,Ogre::Vector3 v2)
{
	if(twoDimensionsTrajectory)
	{
		v1.y=0;
		v2.y=0;
	}
	return v1.distance(v2);
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

int Trajectory::getNextNode(int node)
{
	unsigned int nextNode=node+1;
	if(nextNode>=trajectoryNodes.size())
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

	//Ogre::LogManager::getSingleton().logMessage("Last position "+Ogre::StringConverter::toString(currentPosition));
	Vector3 lastPosition=currentPosition;
	nextMovement=Vector3::ZERO;

	if(stop || trajectoryNodes.size()==0) return;

	//Calculate total time
	totalTime+=elapsedTime;
	//Ogre::LogManager::getSingleton().logMessage("Updating trajectory "+getName());

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
				if(moveToPredefinedTrajectory)
				{
					setPredefinedTrajectoryFromNode(mPredefinedTrajectory,
						mPathfindingTarget);
				}
				else
				{
					reachedLastNode=true;
					setCurrentNode(trajectoryNodes.size()-1);
				}
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

	//Calculate current position
	Vector3 direction;
	direction=trajectoryNodes[nextNode]->getSceneNode()->getPosition()-trajectoryNodes[currentNode]->getSceneNode()->getPosition();
	direction.normalise();
	currentPosition=currentPosition+direction*currentSpeed*elapsedTime;
	nextMovement=currentPosition-lastPosition;

	//Calculate current orientation
	currentOrientation= Quaternion::Slerp(1-(distanceToNextNode/completeDistanceToNextNode), 
		trajectoryNodes[currentNode]->getSceneNode()->getOrientation(), 
		trajectoryNodes[nextNode]->getSceneNode()->getOrientation(),true);

	if(twoDimensionsTrajectory)
	{
		currentPosition.y=0;
		nextMovement.y=0;
	}

	if(pathFindingActivated)
	{
		lastPathFindingTime+=elapsedTime;
		if(lastPathFindingTime>recalculateTime)
		{
			recalculatePathfinding();
			lastPathFindingTime=0;
		}
	}

	//Ogre::LogManager::getSingleton().logMessage("Updating position "+Ogre::StringConverter::toString(currentPosition));
	//Ogre::LogManager::getSingleton().logMessage("Updating orientation "+Ogre::StringConverter::toString(currentPosition));
	//Ogre::LogManager::getSingleton().logMessage("Updating nextMovement "+Ogre::StringConverter::toString(nextMovement));
}

OUAN::Quaternion Trajectory::getCurrentOrientation()
{
	return currentOrientation;
}

OUAN::Vector3 Trajectory::getCurrentPosition()
{
	return currentPosition;
}

OUAN::Vector3 Trajectory::getNextMovement()
{
	return nextMovement;
}

bool Trajectory::isEmpty()
{
	return trajectoryNodes.size()==0;
}

TrajectoryNode * Trajectory::getCurrentNode()
{
	return trajectoryNodes[currentNode];
}

void Trajectory::clear()
{
	myLines.clear();
	myNodes.clear();

	while(trajectoryNodes.size()>0)
	{
		popBackNode();
	}

	mDebugObjects->detachAllObjects();
	mDebugObjects->removeAndDestroyAllChildren();

	reset();
}

void Trajectory::setCurrentNode(int node)
{
	currentNode=node;
	totalTime=0;
	if(trajectoryNodes.size()>0)
	{
		//Ogre::LogManager::getSingleton().logMessage("Current Node "+trajectoryNodes[node]->getSceneNode()->getName());
		//Ogre::LogManager::getSingleton().logMessage("Current Node "+Ogre::StringConverter::toString(currentNode));

		currentPosition=trajectoryNodes[currentNode]->getSceneNode()->getPosition();
		currentOrientation=trajectoryNodes[currentNode]->getSceneNode()->getOrientation();
		completeDistanceToNextNode=calculateDistance(trajectoryNodes[currentNode]->getSceneNode()->getPosition(),trajectoryNodes[getNextNode()]->getSceneNode()->getPosition());
		distanceToNextNode=completeDistanceToNextNode;
	}
}

void Trajectory::reset()
{
	stop=false;
	setCurrentNode(0);
}

void Trajectory::setTrajectoryNodes(std::vector<TrajectoryNode *> trajectoryNodes,std::string debugColor)
{
	unsigned int i;
	TrajectoryNode * pTrajectoryNode;

	clear();

	for(i=0;i<trajectoryNodes.size();i++)
	{
		pTrajectoryNode=trajectoryNodes[i];

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

	pTrajectoryNode=trajectoryNodes[node];
	return mName+"#"+Ogre::StringConverter::toString(node)+"#"+pTrajectoryNode->getSceneNode()->getName();
}

std::string Trajectory::getLineDebugName(int node)
{
	TrajectoryNode * pTrajectoryNode;

	pTrajectoryNode=trajectoryNodes[node];
	return mName+"#"+Ogre::StringConverter::toString(node)+"#line#"+trajectoryNodes[node]->getSceneNode()->getName();
}

void Trajectory::createNodeDebugInfo(int node,std::string debugColor)
{
	TrajectoryNode * pTrajectoryNode;

	Ogre::SceneNode * pEntityDebugNode;
	Ogre::SceneNode * pLineDebugNode;
	Ogre::Entity * pEntity;

	pTrajectoryNode=trajectoryNodes[node];

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

	if(trajectoryNodes.size()>1)
	{
		std::string lineDebugName=getLineDebugName(node);;
		pLineDebugNode=mDebugObjects->createChildSceneNode(lineDebugName);
		Line3D *myLine; 
		//create graphics debug objects
		myLine = new Line3D();
		myLine->addPoint(trajectoryNodes[node]->getSceneNode()->getPosition());
		myLine->addPoint(trajectoryNodes[node-1]->getSceneNode()->getPosition());
		myLine->setMaterial(debugColor);
		myLine->drawLines();
		pLineDebugNode->attachObject(myLine);
		pLineDebugNode->setVisible(mVisible);
		myLines[lineDebugName]=myLine;
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

void Trajectory::setStop(bool stop)
{
	this->stop=stop;
}

void Trajectory::activateIdle(std::string gameObject,std::string node,std::string walkabilityMap)
{
	mChase=false;
	mIddle=true;
	moveToPredefinedTrajectory=false;
	doPathfinding(gameObject,node,walkabilityMap);
}

void Trajectory::activatePathfinding(std::string source,std::string target,std::string walkabilityMap)
{
	mChase=false;
	mIddle=false;
	moveToPredefinedTrajectory=false;
	doPathfinding(source,target,walkabilityMap);
}

void Trajectory::doPathfinding(std::string source,std::string target,std::string walkabilityMap)
{
	TrajectoryNode * pTrajectoryNode;

	loopTrajectory=false;
	pathFindingActivated=false;

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
		reachedLastNode=false;
		mPathfindingTarget=target;
		mPathfindingSource=source;
		mWalkabilityMap=walkabilityMap;
		//Ogre::LogManager::getSingleton().logMessage("Pathfinding target "+target);
		recalculatePathfinding();
		reset();
		pathFindingActivated=true;
	}
}

void Trajectory::fullPathfinding()
{
	unsigned int i;
	TrajectoryNode * pTrajectoryNode;
	std::vector<Ogre::SceneNode *> path;
	//Ogre::LogManager::getSingleton().logMessage("CAS 1");
	clear();
	path=mTrajectoryManager->calculatePathFinding(
		mWalkabilityMap,
		mPathfindingSource,
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

void Trajectory::partialPathfinding()
{
	unsigned int i;
	TrajectoryNode * pTrajectoryNode;
	std::vector<Ogre::SceneNode *> path;
	TrajectoryNode * pCurrentNode;
	TrajectoryNode * pNextNode;
	int nextNode=getNextNode();

	pCurrentNode = new TrajectoryNode();
	pCurrentNode->setSceneNode(trajectoryNodes[currentNode]->getSceneNode());
	pCurrentNode->setSpeed(trajectoryNodes[currentNode]->getSpeed());

	pNextNode = new TrajectoryNode();
	pNextNode->setSceneNode(trajectoryNodes[nextNode]->getSceneNode());
	pNextNode->setSpeed(trajectoryNodes[nextNode]->getSpeed());


	//Ogre::LogManager::getSingleton().logMessage("CAS 2");
	path=mTrajectoryManager->calculatePathFinding(
		mWalkabilityMap,
		trajectoryNodes[nextNode]->getSceneNode()->getName(),
		mPathfindingTarget);

	clear();

	pushBackNode(pCurrentNode,"green");
	pushBackNode(pNextNode,"green");
	currentNode=0;

	for(i=1;i<path.size();i++)
	{
		//create trajectory node and set the scene node and the rest of parameters
		pTrajectoryNode = new TrajectoryNode();
		pTrajectoryNode->setSceneNode(path[i]);
		pTrajectoryNode->setSpeed(15);

		pushBackNode(pTrajectoryNode,"green");
	}
}

void Trajectory::recalculatePathfinding()
{
	if(mChase)
	{
		activateChase(mPathfindingSource,mPathfindingTarget);
		return;
	}

	int nextNode=getNextNode();

	//if(pathFindingActivated)
	//{
	//	Ogre::LogManager::getSingleton().logMessage("next node "+trajectoryNodes[nextNode]->getSceneNode()->getName());
	//}
	if(reachedLastNode)
	{
		//Ogre::LogManager::getSingleton().logMessage("REACHED TARGET");
		if(!moveToPredefinedTrajectory && !mIddle)
		{
			fullPathfinding();
		}
	}
	else if(!pathFindingActivated ||
		trajectoryNodes.size()-(currentNode+1)<=0 ||
		trajectoryNodes[nextNode]->getSceneNode()->getName().compare(mPathfindingTarget)==0)
	{
		fullPathfinding();
	}
	else
	{
		partialPathfinding();
	}

	//Ogre::LogManager::getSingleton().logMessage("CURRENT TRAJECTORY");
	
	//for(i=0;i<trajectoryNodes.size();i++)
	//{
	//	Ogre::LogManager::getSingleton().logMessage(trajectoryNodes[i]->getSceneNode()->getName());
	//}

	lastPathFindingTime=0;
}

void Trajectory::activateChase(std::string source,std::string target)
{
	TrajectoryNode * pTrajectoryNode;

	clear();

	pTrajectoryNode = new TrajectoryNode();
	pTrajectoryNode->setSceneNode(mSceneManager->getSceneNode(mPathfindingSource));
	pTrajectoryNode->setSpeed(15);

	pushBackNode(pTrajectoryNode,"red");

	pTrajectoryNode = new TrajectoryNode();
	pTrajectoryNode->setSceneNode(mSceneManager->getSceneNode(mPathfindingTarget));
	pTrajectoryNode->setSpeed(15);

	pushBackNode(pTrajectoryNode,"red");

	mPathfindingSource=source;
	mPathfindingTarget=target;
	mChase=true;

	reset();
}

void Trajectory::pushBackNode(TrajectoryNode * pTrajectoryNode,std::string debugColor)
{
	trajectoryNodes.push_back(pTrajectoryNode);
	createNodeDebugInfo(trajectoryNodes.size()-1,debugColor);
}

void Trajectory::popBackNode()
{
	removeNodeDebugInfo(trajectoryNodes.size()-1);
	trajectoryNodes.pop_back();
}

void Trajectory::setPredefinedTrajectoryFromNode(std::string trajectory,std::string node)
{
	activatePredefinedTrajectory(trajectory);
	unsigned int i;
	int current=-1;

	//Ogre::LogManager::getSingleton().logMessage("Predefined Trajectory");

	for(i=0;i<trajectoryNodes.size();i++)
	{
		if(trajectoryNodes[i]->getSceneNode()->getName().compare(node)==0)
		{
			current=i;
			break;
		}
		//Ogre::LogManager::getSingleton().logMessage("Node "+trajectoryNodes[i]->getSceneNode()->getName());
	}

	if(current==-1)
	{
		Ogre::LogManager::getSingleton().logMessage("setPredefinedTrajectoryFromNode Node does not exist");
	}
	else
	{
		//Ogre::LogManager::getSingleton().logMessage("setPredefinedTrajectoryFromNode Node "+node+" "+trajectoryNodes[current]->getSceneNode()->getName());
		setCurrentNode(current);
	}

	mIddle=false;
	pathFindingActivated=false;
	moveToPredefinedTrajectory=false;
}

void Trajectory::activatePredefinedTrajectory(std::string trajectory)
{
	mChase=false;
	loopTrajectory=true;
	mPredefinedTrajectory=trajectory;
	mTrajectoryManager->setPredefinedTrajectory(*this,trajectory,"green");
}

std::string Trajectory::getNearestNode(Ogre::Vector3 position)
{
	double minDistance=-1;
	std::string minDistanceName="";
	double distance;
	for(unsigned int i=0;i<trajectoryNodes.size();i++)
	{
		distance=trajectoryNodes[i]->getSceneNode()->getPosition().distance(position);
		if(minDistance==-1 || distance<minDistance)
		{
			minDistance=distance;
			minDistanceName=trajectoryNodes[i]->getSceneNode()->getName();
		}
	}
	return minDistanceName;
}

void Trajectory::activatePathfindingToPredefinedTrajectory(std::string trajectory,std::string gameObject,std::string walkabilityMap)
{
	std::string target;

	//find nearest node
	target=mTrajectoryManager->getNearestNodeToTrajectory(trajectory,
		mSceneManager->getSceneNode(gameObject)->getPosition());

	mPredefinedTrajectory=trajectory;

	moveToPredefinedTrajectory=true;
	doPathfinding(gameObject,target,walkabilityMap);

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



