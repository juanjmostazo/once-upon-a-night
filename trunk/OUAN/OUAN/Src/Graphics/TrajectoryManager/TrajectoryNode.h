#ifndef TrajectoryNodeH_H
#define TrajectoryNodeH_H

#include "../../OUAN.h"

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
		double speed;

	};

	class TrajectoryNode
	{
	private:
		Ogre::SceneNode * mSceneNode;
		double speed;
	public:

		TrajectoryNode();
		~TrajectoryNode();
		
		Ogre::SceneNode * getSceneNode() const;
		void setSceneNode(Ogre::SceneNode * pSceneNode);

		double getSpeed() const;
		void setSpeed(double Speed);
	};
}

#endif