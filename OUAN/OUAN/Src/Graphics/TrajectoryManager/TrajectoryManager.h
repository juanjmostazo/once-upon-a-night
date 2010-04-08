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


	public:

		TrajectoryManager();
		~TrajectoryManager();
		
		void init(RenderSubsystemPtr pRenderSubsystem);
		void clear();

		void createTrajectory(TTrajectoryParameters tTrajectoryParameters);
		void createWalkabilityMap(TWalkabilityMapParameters tWalkabilityMapParameters);

		Trajectory * getTrajectoryInstance(std::string name);

		bool hasTrajectory(std::string name);
		bool hasWalkabilityMap(std::string name);
	};
}

#endif

