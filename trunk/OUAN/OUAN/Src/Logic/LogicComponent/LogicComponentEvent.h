#ifndef LogicComponentEventH_H
#define LogicComponentEventH_H

#include "LogicComponent.h"

namespace OUAN
{
	class LogicComponentEvent: public LogicComponent
	{
	private:
		std::string mEvent;
	public:

		LogicComponentEvent(const std::string& type="");
		~LogicComponentEvent();

		std::string getEventType() const;
		void setEventType(std::string eventtype);
	};

	class TLogicComponentEventParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentEventParameters();
		~TLogicComponentEventParameters();

		String eventtype;
	};

}

#endif