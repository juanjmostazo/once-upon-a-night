#ifndef TrajectoryManagerH_H
#define TrajectoryManagerH_H

#include "../../OUAN.h"

namespace OUAN
{
	class TrajectoryManager
	{
	private:
		Ogre::SceneManager * mSceneManager;

		std::map<std::string,Trajectory *> trajectory;
		typedef std::map<std::string,Trajectory *>::iterator TTrajectoryIterator;

	public:

		TrajectoryManager();
		~TrajectoryManager();
		
		void init(Ogre::SceneManager * pSceneManager);
		void clear();

		void createTrajectory(TTrajectoryParameters tTrajectoryParameters);
		Trajectory * getTrajectory(std::string name);

	};
}

#endif

