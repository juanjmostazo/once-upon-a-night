#ifndef LogicComponentBreakableH_H
#define LogicComponentBreakableH_H

#include "LogicComponent.h"

namespace OUAN
{
	const int STATE_BREAKABLE_NOT_BROKEN=0;
	const int STATE_BREAKABLE_BROKEN=1;

	class LogicComponentBreakable: public LogicComponent
	{
	public:
		LogicComponentBreakable(const std::string& type="");
		~LogicComponentBreakable();

		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);

		bool getIsBroken() const;
		void setIsBroken(bool isBroken);

		double getDisableTime() const;
		void setDisableTime(double disableTime);

		void update(double elapsedTime);

	private:
		bool mIsBroken;
		double mDisableTime;
		double mElapsedTimeSinceBreakup;
	};

	class TLogicComponentBreakableParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentBreakableParameters();
		~TLogicComponentBreakableParameters();

		double mDisableTime;
	};
}

#endif