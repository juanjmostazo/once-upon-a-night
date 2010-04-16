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
		double lastPathFindingTime;
		double recalculateTime;
		unsigned int currentNode;
		std::vector<TrajectoryNode *> trajectoryNodes;
		Vector3 currentPosition;
		Vector3 nextMovement;
		Quaternion currentOrientation;

		bool loopTrajectory;
		bool stop;
		bool pathFindingActivated;
		bool reachedLastNode;
		bool twoDimensionsTrajectory;

		int getNextNode();
		void setCurrentNode(int node);

		std::string mName;
		std::string mWalkabilityMap;
		std::string mPathfindingTarget;
		std::string mPathfindingSource;
		bool startupDone;

		Vector3 mStartupPosition;
		Quaternion mStartupOrientation;

		Ogre::SceneNode * mDebugObjects;
		Ogre::SceneManager * mSceneManager;
		TrajectoryManagerPtr mTrajectoryManager;

		void recalculatePathfinding();
		void removeNodeDebugInfo(int node);
		void createNodeDebugInfo(int node,std::string debugColor);

		void popBackNode();
		void pushBackNode(TrajectoryNode * pTrajectoryNode,std::string debugColor);
		double calculateDistance(Ogre::Vector3 v1,Ogre::Vector3 v2);

		std::string getEntityDebugName(int node);
		std::string getLineDebugName(int node);

		TrajectoryNode* getTrajectoryNode(int index);
		int getNumberOfNodes() const;

		bool mVisible;

		std::string mPredefinedTrajectory;
		bool moveToPredefinedTrajectory;

		void doPathfinding(std::string source,std::string target,std::string walkabilityMap);
		void setPredefinedTrajectoryFromNode(std::string trajectory,std::string node);


	public:

		Trajectory();
		~Trajectory();

		Quaternion getCurrentOrientation();
		Vector3 getCurrentPosition();
		Vector3 getNextMovement();

		void reset();
		void clear();

		void update(double elapsedTime);
		void init(std::string name,Ogre::SceneManager * pSceneManager,Ogre::SceneNode * debugObjects,TrajectoryManagerPtr pTrajectoryManager);
		void setTrajectoryNodes(std::vector<TrajectoryNode *> trajectoryNodes,std::string debugColor);

		void setAs2DTrajectory();
		void setAs3DTrajectory();

		void activatePathfinding(std::string source,std::string target,std::string walkabilityMap);
		void activateIdle(std::string gameObject,std::string node,std::string walkabilityMap);
		void activatePredefinedTrajectory(std::string trajectory);
		void activatePathfindingToPredefinedTrajectory(std::string trajectory,std::string gameObject,std::string walkabilityMap);

		std::string getNearestNode(Ogre::Vector3 position);

		TrajectoryNode * getCurrentNode();

		bool isEmpty();

		std::vector<TrajectoryNode *>  getTrajectoryNodes() const;

		bool getLoopTrajectory() const;
		void setLoopTrajectory(bool loopTrajectory);

		void setStop(bool stop);

		void setVisible(bool visible);

		std::string getName();

		bool predefinedTrajectoryExists(std::string name);

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