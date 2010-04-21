#ifndef LOGIC_COMPONENT_USABLEH_H
#define LOGIC_COMPONENT_USABLEH_H

#include "LogicComponent.h"
namespace OUAN
{
	class LogicComponentUsable: public LogicComponent
	{
	public:
		LogicComponentUsable(const std::string& type="");
		~LogicComponentUsable();

		void processCollision(GameObjectPtr pGameObject);
		//void processActivate(ActivateEventPtr evt);
		//void processAnimationEnded(AnimationEndedEventPtr evt);
		//...
		
		void update(double elapsedTime);

		double getApproachDistance() const;
		void setApproachDistance(double approachDistance);
		
		double getActivateDistance() const;
		void setActivateDistance(double activateDistance);

		bool isActivated() const;
		void setIsActivated(bool isActivated);

		bool canBeActivated() const;
		void setCanBeActivated(bool canBeActivated);
		
	private:
		double mApproachDistance;
		double mActivateDistance;

		bool mIsActivated;
		bool mCanBeActivated;
	};

	class TLogicComponentUsableParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentUsableParameters();
		~TLogicComponentUsableParameters();

		double approachDistance;
		double activateDistance;

	};
}

#endif