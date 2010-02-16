#ifndef __TRAJECTORY__H__
#define __TRAJECTORY__H__

#include <Ogre.h>
#include <string>
#include <vector>

#define TIME_PER_NODE 0.5

class Trajectory
{
public:
	Trajectory(void);
	~Trajectory(void);

	Ogre::SceneManager *pSceneManager;

	std::vector<std::string> trajectoryNodes;

	void initialise(Ogre::SceneManager *pSceneManager);
	Ogre::Vector3 getNextPosition( const float elapsedSeconds );
	void restartTrajectory();
	void addNode(std::string nodeName);

private:
	unsigned int currentNode;
	float timeElapsedSinceLastNode;

};

#endif
