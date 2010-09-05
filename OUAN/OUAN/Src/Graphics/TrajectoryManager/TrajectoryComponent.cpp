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
	//if (getParent()->isWorthUpdatingPhysicsComponents())
	//{
		mTrajectory->update(elapsedSeconds+getParent()->getElapsedTimeSinceLastPhysicsUpdate());
	//}
}

void TrajectoryComponent::setTrajectory(Trajectory * pTrajectory)
{
	mTrajectory=pTrajectory;
}
Trajectory* TrajectoryComponent::getTrajectory() const
{
	return mTrajectory;
}
bool TrajectoryComponent::hasEnded() const

{
	if (mTrajectory)
	{
		return mTrajectory->trajectoryEnded();
	}
	return true;
}
void TrajectoryComponent::activateChase(const std::string& target)
{
	mTrajectory->activateChase(getParent()->getName(),target);
}
void TrajectoryComponent::activateFlee(const std::string& target, double safeDistance)
{
	mTrajectory->activateFlee(getParent()->getName(),target, safeDistance);
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

void TrajectoryComponent::activatePathfindingToPredefinedTrajectory(std::string trajectory,int currentWorld,bool useDefaultTrajectorySpeed)
{
	if(currentWorld==DREAMS)
	{
		mTrajectory->activatePathfindingToPredefinedTrajectory(trajectory,getParent()->getName(),DEFAULT_WALKABILITY_MAP_DREAMS,useDefaultTrajectorySpeed);
	}
	else if(currentWorld==NIGHTMARES)
	{
		mTrajectory->activatePathfindingToPredefinedTrajectory(trajectory,getParent()->getName(),DEFAULT_WALKABILITY_MAP_NIGHTMARES,useDefaultTrajectorySpeed);
	}
}

void TrajectoryComponent::activateTrajectory(std::string trajectory,bool useDefaultTrajectorySpeed)
{
	mTrajectory->activatePredefinedTrajectory(trajectory,useDefaultTrajectorySpeed);
}


bool TrajectoryComponent::predefinedTrajectoryExists(std::string name)
{
	return mTrajectory->predefinedTrajectoryExists(name);
}

void TrajectoryComponent::setDefaultSpeed(double defaultSpeed)
{
	mTrajectory->setDefaultSpeed(defaultSpeed);
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

void TrajectoryComponent::setAs2DTrajectory()
{
	mTrajectory->setAs2DTrajectory();
}

void TrajectoryComponent::setAs3DTrajectory()
{
	mTrajectory->setAs3DTrajectory();
}
void TrajectoryComponent::setLoopingTrajectory(bool looping)
{
	if (mTrajectory)
		mTrajectory->setLoopTrajectory(looping);
}
bool TrajectoryComponent::isLoopingTrajectory() const
{
	if (mTrajectory)
		return mTrajectory->getLoopTrajectory();
	return false;
}
TTrajectoryComponentParameters::TTrajectoryComponentParameters()
{
}

TTrajectoryComponentParameters::~TTrajectoryComponentParameters()
{
}