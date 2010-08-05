#ifndef TrajectoryComponentH_H
#define TrajectoryComponentH_H

#include "../../Component/Component.h"
namespace OUAN
{
	class TrajectoryComponent: public Component
	{
	private:
		Trajectory * mTrajectory;
	public:
		TrajectoryComponent(const std::string& type="");
		~TrajectoryComponent();

		//To add a trajectory component must be added to ht egame object, loaded at level Loader with its processor.
		//Parameters must be defined at the .ctp file of the object
		//must be initialized when creating the gameobject using component factory.

		//String are the name of the affected gameObjects
		//Activates idle state, which creates a trajectory of only one node at the current idleNode position, to which the parnet will go from its current position
		void activateIdle(std::string idleNode,int currentWorld);
		//Activates pathfinding state, which creates a trajectory to the target node from the current parent position
		void activatePathFinding(std::string target,int currentWorld);
		//Activates a predefined trajectory, first the parent will find a trajectory that leads to a node of
		//that trajectory and once arrives to the predefined trajectory it will follow it from there on
		//Predefined trajectories have to be defined in Ogitor, using "import in" trajectory.ctp" parameters and "trajectorynode.ctp" for its nodes, defined using Marker Objects.
		void activatePredefinedTrajectory(std::string trajectory,int currentWorld);
		//same as above but without finding a path to the trajectory first, starting directly from the first trajectory node
		void setTrajectory(Trajectory * pTrajectory);
		//Activates chase state, which recalculates a direct vector to the target
		void activateChase(std::string target);

		//sets speed for non-predefined trajectories
		void setDefaultSpeed(double defaultSpeed);

		//checks if a predefined trajectory exists
		bool predefinedTrajectoryExists(std::string name);

		void setAs2DTrajectory();
		void setAs3DTrajectory();

		//gets next movement scaled by time
		Vector3 getNextMovement();
		//gets next movement without being scaled by time
		Vector3 getNextMovementAbsolute();
		//gets current trajectory position
		Vector3 getCurrentPosition();
		//gets current trajectory orientation
		Quaternion getCurrentOrientation();
		//updates nextmovment, position and orientationfor the trajectory
		void update(double elapsedSeconds);
	};

	class TTrajectoryComponentParameters: public TComponentParameters
	{
	public:
		TTrajectoryComponentParameters();
		~TTrajectoryComponentParameters();
		bool twoDimensions;
		Real defaultSpeed;
	};

}

#endif