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

		void processCollision(GameObjectPtr pGameObject);

		bool getIsBroken() const;
		void setIsBroken(bool isBroken);

		void update(double elapsedTime);

	private:
		bool mIsBroken;
	};

	class TLogicComponentBreakableParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentBreakableParameters();
		~TLogicComponentBreakableParameters();
	};
}

#endif