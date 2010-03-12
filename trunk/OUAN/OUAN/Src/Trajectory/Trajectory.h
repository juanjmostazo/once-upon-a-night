#ifndef TrajectoryH_H
#define TrajectoryH_H

#include "../OUAN.h"
#include "TrajectoryNode.h"
namespace OUAN
{
	class Trajectory
	{
	private:

	public:

		Trajectory();
		~Trajectory();
		
		std::vector<TrajectoryNode *> trajectoryNodes;
		int currentNode;
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