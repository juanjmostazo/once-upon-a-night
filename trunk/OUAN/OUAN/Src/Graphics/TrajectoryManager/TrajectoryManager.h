#ifndef TrajectoryManagerH_H
#define TrajectoryManagerH_H

#include "../../OUAN.h"


namespace OUAN
{
	class TrajectoryManager
	{
	private:
		std::map<std::string,Trajectory *> trajectoryContainer;
		typedef std::map<std::string,Trajectory *>::iterator TTrajectoryIterator;

		std::map<std::string,WalkabilityMap *> walkabilityMapContainer;
		typedef std::map<std::string,WalkabilityMap *>::iterator TWalkabilityMapIterator;

		Ogre::SceneManager * mSceneManager;
		Ogre::SceneNode * mDebugObjects;

		int trajectoryID;

		bool mVisible;

	public:

		TrajectoryManager();
		~TrajectoryManager();
		
		void init(RenderSubsystemPtr pRenderSubsystem);
		void clear();

		void createTrajectory(TTrajectoryParameters tTrajectoryParameters);
		void createWalkabilityMap(TWalkabilityMapParameters tWalkabilityMapParameters);

		bool hasTrajectory(std::string name);
		bool hasWalkabilityMap(std::string name);
		void destroyTrajectory(std::string name);
		void destroyTrajectory(Trajectory * pTrajectory);

		Trajectory * getTrajectoryInstance();

		std::vector<Ogre::SceneNode *> calculatePathFinding(std::string walkabilityMapName,std::string source, std::string target);
		void setPredefinedTrajectory(Trajectory & trajectory,std::string trajectoryName,std::string debugColor);
		void stopTrajectory(Trajectory & trajectory);
		void setIdle(Trajectory & trajectory,std::string gameObjectName);

		std::string getNearestNodeToTrajectory(std::string trajectory,Vector3 position);

		void toggleDebugMode();
	};
}

#endif

