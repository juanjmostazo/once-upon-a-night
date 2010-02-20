#ifndef PhysicsComponentH_H
#define PhysicsComponentH_H

#include "../../Component/Component.h"
namespace OUAN
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(const std::string& name="");
		~PhysicsComponent();

		virtual void update(long elapsedTime);

		//Event handlers
		//void onDoSomething(EventData,emitter, ...);
		//void onDoSomethingElse(...);
	};

	class TPhysicsComponentParameters: public TComponentParameters
	{
	public:
		TPhysicsComponentParameters();
		~TPhysicsComponentParameters();

		//'triangle' or 'convex'
		std::string nxsType; 

		//nxs file name
		std::string nxsFile; 
	};
}

#endif