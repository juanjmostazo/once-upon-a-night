#ifndef PhysicsComponentH_H
#define PhysicsComponentH_H

#include "../../Component/Component.h"
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>
#include <NxOgreAddonCharacterController.h>

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

		virtual NxOgre::Mesh* getMesh();
		virtual void setMesh(NxOgre::Mesh* mesh);

	private:
		NxOgre::Mesh* mesh;
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