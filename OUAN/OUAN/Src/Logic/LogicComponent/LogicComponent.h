#ifndef LogicComponentH_H
#define LogicComponentH_H

#include "../../Component/Component.h"
namespace OUAN
{
	class LogicComponent: public Component
	{
	public:
		LogicComponent(const std::string& type="");
		~LogicComponent();

		virtual void update(long elapsedTime);

		//Event handlers
		//void onDoSomething(EventData,emitter, ...);
		//void onDoSomethingElse(...);
	};

	class TLogicComponentParameters: public TComponentParameters
	{
	public:
		TLogicComponentParameters();
		~TLogicComponentParameters();
	};
}

#endif