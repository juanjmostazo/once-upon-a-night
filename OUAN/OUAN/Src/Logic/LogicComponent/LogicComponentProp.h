#ifndef LOGIC_COMPONENT_PROPH_H
#define LOGIC_COMPONENT_PROPH_H
#include "LogicComponent.h"
namespace OUAN
{
	class LogicComponentProp: public LogicComponent
	{
	public:
		LogicComponentProp(const std::string& type="");
		~LogicComponentProp();

		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);
		//void processActivate(ActivateEventPtr evt);
		//void processAnimationEnded(AnimationEndedEventPtr evt);
		//...

		void update(double elapsedTime);

		double getApproachDistance() const;
		void setApproachDistance(double approachDistance);

		double getTimeSpent() const;
		void setTimeSpent(double timeSpent);

		double getDelay() const;
		void setDelay(double delay);

		bool hasTakenHit() const;
		void setHasTakenHit(bool hasTakenHit);

		bool isReload() const;
		void setReload(bool reload);

	private:
		double mApproachDistance;
		double mDelay;
		double mTimeSpent;
		bool mHasTakenHit;
		double mHitRecoveryTime;
		bool mReload;
	};

	class TLogicComponentPropParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentPropParameters();
		~TLogicComponentPropParameters();

		double approachDistance;
		double delay;
	};
}
#endif