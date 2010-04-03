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

		Ogre::SceneManager * mSceneManager;

	public:

		TrajectoryManager();
		~TrajectoryManager();
		
		void init(RenderSubsystemPtr pRenderSubsystem);
		void clear();

		void createTrajectory(TTrajectoryParameters tTrajectoryParameters);

		Trajectory * getTrajectoryInstance(std::string name);

		bool hasTrajectory(std::string name);

	};
}

#endif

