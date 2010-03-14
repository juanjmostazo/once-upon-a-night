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

	};

	class TrajectoryNode
	{
	private:
		Ogre::SceneNode * mSceneNode;
	public:

		TrajectoryNode();
		~TrajectoryNode();
		
		Ogre::SceneNode * getSceneNode() const;
		void setSceneNode(Ogre::SceneNode * pSceneNode);

	};
}

#endif