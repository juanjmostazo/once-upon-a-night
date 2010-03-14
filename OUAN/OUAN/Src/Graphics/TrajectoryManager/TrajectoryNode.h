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
		double timeToNextNode;

	};

	class TrajectoryNode
	{
	private:
		Ogre::SceneNode * mSceneNode;
		double timeToNextNode;
	public:

		TrajectoryNode();
		~TrajectoryNode();
		
		Ogre::SceneNode * getSceneNode() const;
		void setSceneNode(Ogre::SceneNode * pSceneNode);

		double getTimeToNextNode() const;
		void setTimeToNextNode(double timeToNextNode);
	};
}

#endif