#include "OUAN_Precompiled.h"

#include "TrajectoryComponent.h"
#include "Trajectory.h"
#include "../../Game/GameObject/GameObject.h"
using namespace OUAN;

TrajectoryComponent::TrajectoryComponent(const std::string& type)
:Component(COMPONENT_TYPE_TRAJECTORY)
{
}

TrajectoryComponent::~TrajectoryComponent()
{
}

void TrajectoryComponent::update(double elapsedSeconds)
{
	mTrajectory->update(elapsedSeconds);
}

void TrajectoryComponent::setTrajectory(Trajectory * pTrajectory)
{
	mTrajectory=pTrajectory;
}

void TrajectoryComponent::activateChase(std::string target)
{
	mTrajectory->activateChase(getParent()->getName(),target);
}

void TrajectoryComponent::activateIdle(std::string idleNode,int currentWorld)
{
	if(currentWorld==DREAMS)
	{
		mTrajectory->activateIdle(idleNode,getParent()->getName(),DEFAULT_WALKABILITY_MAP_DREAMS);
	}
	else if(currentWorld==NIGHTMARES)
	{
		mTrajectory->activateIdle(idleNode,getParent()->getName(),DEFAULT_WALKABILITY_MAP_NIGHTMARES);
	}
}

void TrajectoryComponent::activatePathFinding(std::string target,int currentWorld)
{
	if(currentWorld==DREAMS)
	{
		mTrajectory->activatePathfinding(getParent()->getName(),target,DEFAULT_WALKABILITY_MAP_DREAMS);
	}
	else if(currentWorld==NIGHTMARES)
	{
		mTrajectory->activatePathfinding(getParent()->getName(),target,DEFAULT_WALKABILITY_MAP_NIGHTMARES);
	}
}

void TrajectoryComponent::activatePredefinedTrajectory(std::string trajectory,int currentWorld)
{
	if(currentWorld==DREAMS)
	{
		mTrajectory->activatePathfindingToPredefinedTrajectory(trajectory,getParent()->getName(),DEFAULT_WALKABILITY_MAP_DREAMS);
	}
	else if(currentWorld==NIGHTMARES)
	{
		mTrajectory->activatePathfindingToPredefinedTrajectory(trajectory,getParent()->getName(),DEFAULT_WALKABILITY_MAP_NIGHTMARES);
	}
}

bool TrajectoryComponent::predefinedTrajectoryExists(std::string name)
{
	return mTrajectory->predefinedTrajectoryExists(name);
}

Vector3 TrajectoryComponent::getNextMovement()
{
	return mTrajectory->getNextMovement();
}

Vector3 TrajectoryComponent::getNextMovementAbsolute()
{
	return mTrajectory->getNextMovementAbsolute();
}

Vector3 TrajectoryComponent::getCurrentPosition()
{
	return mTrajectory->getCurrentPosition();
}

Quaternion TrajectoryComponent::getCurrentOrientation()
{
	return mTrajectory->getCurrentOrientation();
}