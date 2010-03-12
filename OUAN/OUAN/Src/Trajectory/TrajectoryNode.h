#ifndef TrajectoryNodeH_H
#define TrajectoryNodeH_H

#include "../OUAN.h"

namespace OUAN
{
	class TTrajectoryNodeParameters
	{
	public:
		TTrajectoryNodeParameters();
		~TTrajectoryNodeParameters();

		String nodeName;

		Vector3 position;
		Quaternion orientation;
	};

	class TrajectoryNode
	{
	private:

	public:

		TrajectoryNode();
		~TrajectoryNode();
		
		Ogre::SceneNode * node;
	};
}

#endif