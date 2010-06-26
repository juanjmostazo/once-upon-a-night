#ifndef TrajectoryH_H
#define TrajectoryH_H

#include "../../OUAN.h"
#include "TrajectoryNode.h"
#include "../../Graphics/ObjectTextOverlay/ObjectTextDisplay.h"

namespace OUAN
{
	class Trajectory
	{
	private:

		double mTimeSinceLastUpdateNodes;
		double mRecalculateTime;

		Vector3 mCurrentPosition;
		Vector3 mNextMovement;
		Vector3 mNextMovementAbsolute;
		Quaternion mCurrentOrientation;

		unsigned int mCurrentNode;
		std::vector<TrajectoryNode *> mTrajectoryNodes;

		bool mLoopTrajectory;
		bool mTrajectory2d;

		enum TrajectoryState
		{
			PATH_FINDING,
			IDLE,
			CHASE,
			PATH_FINDING_TO_PREDEFINED_TRAJECTORY,
			PATH_FINDING_TO_IDLE,
			PREDEFINED_TRAJECTORY
		};

		TrajectoryState mState;
		
		double mMinNextNodeDistance;
		double mDefaultSpeed;

		int getNextNode();
		int getNextNode(int node);
		void setCurrentNode(int node);
		bool isLastNode();

		Vector3 calculateNextPosition(std::string source,std::string target,bool Trajectory2d,double speed,double elapsedTime);
		Vector3 calculateNextMovement(std::string source,std::string target,bool Trajectory2d,double speed,double elapsedTime);
		Vector3 calculateNextMovementAbsolute(std::string source,std::string target,bool Trajectory2d,double speed,double elapsedTime);
		Quaternion calculateNextOrientation(std::string lastNode,std::string source,std::string target,bool Trajectory2d,double speed,double elapsedTime);

		std::string mParent;

		std::string mName;
		std::string mWalkabilityMap;
		std::string mPathfindingTarget;

		Ogre::SceneNode * mDebugObjects;
		Ogre::SceneManager * mSceneManager;
		TrajectoryManagerPtr mTrajectoryManager;

		void advanceToNextNode(double elapsedTime);
		void advanceToLastNode(double elapsedTime);
		void updateTrajectoryNodes(double elapsedTime);

		void popBackNode();
		void pushBackNode(TrajectoryNode * pTrajectoryNode,std::string debugColor);

		double calculateDistance(std::string node1,std::string node2);

		//Pathfinding funcions
		void updatePathfinding();

		void initPathfinding();
		void recalculatePathfinding();
		void doPathfinding(std::string source,std::string target,std::string walkabilityMap);

		//Predefined trajectory functions
		std::string mPredefinedTrajectory;
		bool moveToPredefinedTrajectory;
		void setPredefinedTrajectoryFromNode(std::string trajectory,std::string node);

		//Chase functions
		void updateChase();

		//Debug functions
		void removeNodeDebugInfo(int node);
		void createNodeDebugInfo(int node,std::string debugColor);
		std::string getEntityDebugName(int node);
		std::string getLineDebugName(int node);
		bool mVisible;

		TrajectoryNode* getTrajectoryNode(int index);
		int getNumberOfNodes() const;

		std::map<std::string,Line3D *> myLines;
		std::map<std::string,Ogre::Entity *> myNodes;
		std::vector<ObjectTextDisplay*> mDisplays;

	public:

		Trajectory();
		~Trajectory();

		Quaternion getCurrentOrientation();
		Vector3 getCurrentPosition();
		Vector3 getNextMovement();
		Vector3 getNextMovementAbsolute();

		void reset();
		void clear();

		void updateDebugNodes();
		void destroyDebugNodes();

		bool trajectoryEnded();

		void update(double elapsedTime);
		void init(std::string name,Ogre::SceneManager * pSceneManager,Ogre::SceneNode * debugObjects,TrajectoryManagerPtr pTrajectoryManager, double defaultSpeed, double minNextNodeDistance);
		void setTrajectoryNodes(std::vector<TrajectoryNode *> mTrajectoryNodes,std::string debugColor);

		void setDefaultSpeed(double defaultSpeed);

		/////
		void setAs2DTrajectory();
		void setAs3DTrajectory();

		void activatePathfinding(std::string source,std::string target,std::string walkabilityMap);
		void activateIdle(std::string gameObject,std::string node,std::string walkabilityMap);
		void activatePredefinedTrajectory(std::string trajectory);
		void activatePathfindingToPredefinedTrajectory(std::string trajectory,std::string gameObject,std::string walkabilityMap);
		void activateChase(std::string source,std::string target);

		std::string getNearestNode(Ogre::Vector3 position);

		TrajectoryNode * getCurrentNode();

		bool isEmpty();

		std::vector<TrajectoryNode *>  getTrajectoryNodes() const;

		bool getLoopTrajectory() const;
		void setLoopTrajectory(bool loopTrajectory);

		void setVisible(bool visible);

		std::string getName();

		std::string getParent() const;
		void setParent(std::string parent);

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