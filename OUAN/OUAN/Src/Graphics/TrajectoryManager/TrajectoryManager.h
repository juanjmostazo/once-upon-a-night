#ifndef TrajectoryManagerH_H
#define TrajectoryManagerH_H

#include "../../OUAN.h"

namespace OUAN
{
	class TrajectoryManager
	{
	private:
		//std::vector<Trajectory *> trajectoryContainer;
		//typedef std::map<std::string,Trajectory *>::iterator TTrajectoryIterator;

		Ogre::SceneManager * mSceneManager;
		Trajectory * mTrajectory;

	public:

		TrajectoryManager();
		~TrajectoryManager();
		
		void init(Ogre::SceneManager * pSceneManager);
		void clear();

		void createTrajectory(TTrajectoryParameters tTrajectoryParameters);
		Trajectory * getTrajectory(std::string name) const;
		bool hasTrajectory(std::string name);

	};
}

#endif

