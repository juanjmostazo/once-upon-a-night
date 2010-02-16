#include "Trajectory.h"

Trajectory::Trajectory(void)
{
}

Trajectory::~Trajectory(void)
{
}

void Trajectory::initialise(Ogre::SceneManager *pSceneManager)
{
	currentNode=0;
	this->pSceneManager = pSceneManager;
	this->trajectoryNodes.clear();
	timeElapsedSinceLastNode=0;
}

Ogre::Vector3 Trajectory::getNextPosition( const float elapsedSeconds )
{

	Ogre::Vector3 nextPosition;
	Ogre::Vector3 currentNodePosition;
	Ogre::Vector3 nextNodePosition;
	Ogre::SceneNode *pCurrentSceneNode;
	Ogre::SceneNode *pNextSceneNode;
	nextPosition= Ogre::Vector3(0,0,0);
	unsigned int nextNode;

	//update Time elapsed since last node change
	timeElapsedSinceLastNode+=elapsedSeconds;

	//calculate current Node
	if( timeElapsedSinceLastNode>=TIME_PER_NODE)
	{
		timeElapsedSinceLastNode=0;
		currentNode++;
		if(currentNode>=trajectoryNodes.size())
		{
			currentNode=0;
		}
	}

	//calculate next node
	nextNode=currentNode+1;
	if(nextNode>=trajectoryNodes.size())
	{
		nextNode=0;
	}

	//calculate next position
	if (trajectoryNodes.size()>0)
	{
		pCurrentSceneNode=pSceneManager->getSceneNode(trajectoryNodes[currentNode]);
		pNextSceneNode=pSceneManager->getSceneNode(trajectoryNodes[nextNode]);

		currentNodePosition=pCurrentSceneNode->getPosition();
		nextNodePosition=pNextSceneNode->getPosition();

		nextPosition=(1.0f-timeElapsedSinceLastNode/TIME_PER_NODE)*currentNodePosition+(timeElapsedSinceLastNode/TIME_PER_NODE)*nextNodePosition;
		
	}	
	Ogre::LogManager::getSingleton().logMessage("Next position is "+Ogre::StringConverter::toString(nextPosition));
	return nextPosition;
}

void Trajectory::restartTrajectory()
{
	currentNode=0;
	timeElapsedSinceLastNode=0;
}

void Trajectory::addNode(std::string nodeName)
{
	Ogre::LogManager::getSingleton().logMessage("Node "+nodeName+" added to trajectory");
	trajectoryNodes.push_back(nodeName);
}