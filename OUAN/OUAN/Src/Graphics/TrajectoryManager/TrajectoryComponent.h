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

		void setTrajectory(Trajectory * pTrajectory);

		void update(double elapsedSeconds);

		void activateIdle(std::string idleNode,int currentWorld);
		void activatePathFinding(std::string target,int currentWorld);
		void activatePredefinedTrajectory(std::string trajectory,int currentWorld);
		void activateChase(std::string target);

		void setDefaultSpeed(double defaultSpeed);

		bool predefinedTrajectoryExists(std::string name);

		Vector3 getNextMovement();
		Vector3 getNextMovementAbsolute();
		Vector3 getCurrentPosition();
		Quaternion getCurrentOrientation();
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