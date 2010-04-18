#ifndef LogicComponentItemH_H
#define LogicComponentItemH_H

#include "LogicComponent.h"
namespace OUAN
{
	const int STATE_ITEM_NOT_TAKEN=0;
	const int STATE_ITEM_TAKEN=1;

	class LogicComponentItem: public LogicComponent
	{
	public:
		LogicComponentItem(const std::string& type="");
		~LogicComponentItem();

		void processCollision(GameObjectPtr pGameObject);

		bool getIsTaken() const;
		void setIsTaken(bool isTaken);

	private:

		bool mIsTaken;

	};
	
	class TLogicComponentItemParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentItemParameters();
		~TLogicComponentItemParameters();

	};
}

#endif