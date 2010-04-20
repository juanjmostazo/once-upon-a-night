#ifndef LogicComponentItemH_H
#define LogicComponentItemH_H

#include "LogicComponent.h"
namespace OUAN
{
	const std::string PORTAL_STATE_IDLE="PORTAL_STATE_IDLE";
	const std::string PORTAL_STATE_ONY_APPROACHING="PORTAL_STATE_ONY_APPROACHING";
	const std::string PORTAL_STATE_ONY_MAY_ACTIVATE="PORTAL_STATE_ONY_MAY_ACTIVATE";
	const std::string PORTAL_STATE_CHANGING_WORLD="PORTAL_STATE_CHANGING_WORLD";

	const std::string PORTAL_ANIMATION_IDLE="";
	const std::string PORTAL_ANIMATION_ONY_APPROACHING="";
	const std::string PORTAL_ANIMATION_ONY_MAY_ACTIVATE="";
	const std::string PORTAL_ANIMATION_CHANGING_WORLD="";

	class LogicComponentPortal: public LogicComponent
	{
	public:
		LogicComponentPortal(const std::string& type="");
		~LogicComponentPortal();

		void processCollision(GameObjectPtr pGameObject);
		//void processActivate(ActivateEventPtr evt);
		//void processAnimationEnded(AnimationEndedEventPtr evt);
		//...
		
		void update(double elapsedTime);

		double getApproachDistance() const;
		void setApproachDistance(double approachDistance);
		
		double getActivateDistance() const;
		void setActivateDistance(double activateDistance);
		
	private:
		double mApproachDistance;
		double mActivateDistance;		
	};

	class TLogicComponentPortalParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentPortalParameters();
		~TLogicComponentPortalParameters();

		double approachDistance;
		double activateDistance;

	};
}

#endif