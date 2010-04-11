#ifndef TrajectoryH_H
#define TrajectoryH_H

#include "../../OUAN.h"
#include "TrajectoryNode.h"
namespace OUAN
{
	class Trajectory
	{
	private:
		double distanceToNextNode;
		double completeDistanceToNextNode;
		double totalTime;
		unsigned int currentNode;
		std::vector<TrajectoryNode *> trajectoryNodes;
		Vector3 currentPosition;
		Quaternion currentOrientation;

		bool loopTrajectory;

		int getNextNode();
		void setCurrentNode(int node);

		std::string mName;

		bool startupDone;

		Vector3 mStartupPosition;
		Quaternion mStartupOrientation;

		Ogre::SceneNode * mDebugObjects;
		Ogre::SceneManager * mSceneManager;
	public:

		Trajectory();
		~Trajectory();

		Quaternion getCurrentOrientation();
		Vector3 getCurrentPosition();

		void reset();
		void clear();

		void update(double elapsedTime);

		void init(std::string name,Ogre::SceneManager * pSceneManager,Ogre::SceneNode * debugObjects);

		void addTrajectoryNode(TrajectoryNode * pTrajectoryNode,std::string debugColor);

		void setStartup(TrajectoryNode * pTrajectoryNode);

		std::vector<TrajectoryNode *>  getTrajectoryNodes() const;

		bool getLoopTrajectory() const;
		void setLoopTrajectory(bool loopTrajectory);

		std::string getName( );

	};

	class TTrajectoryParameters
	{
	public:
		TTrajectoryParameters();
		~TTrajectoryParameters();

		String name;

		std::vector<TTrajectoryNodeParameters> tTrajectoryNodeParameters;
	};


}

#endif