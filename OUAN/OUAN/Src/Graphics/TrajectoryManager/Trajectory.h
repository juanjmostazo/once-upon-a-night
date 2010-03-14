#ifndef TrajectoryH_H
#define TrajectoryH_H

#include "../../OUAN.h"
#include "TrajectoryNode.h"
namespace OUAN
{
	class Trajectory
	{
	private:
		double totalTime;
		unsigned int currentNode;
		std::vector<TrajectoryNode *> trajectoryNodes;
		Vector3 currentPosition;
		Quaternion currentOrientation;

		bool loopTrajectory;

		int getNextNode();

	public:

		Trajectory();
		~Trajectory();

		Quaternion getCurrentOrientation();
		Vector3 getCurrentPosition();

		void reset();

		void update(double elapsedTime);

		void addTrajectoryNode(Ogre::SceneNode * sceneNode, double timeToNextNode);

		std::vector<TrajectoryNode *>  getTrajectoryNodes() const;

		bool getLoopTrajectory() const;
		void setLoopTrajectory(bool loopTrajectory);

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