#ifndef PhysicsComponentSimpleH_H
#define PhysicsComponentSimpleH_H

#include "PhysicsComponent.h"
namespace OUAN
{
	// Simple physics elements which interact with other elements
	class PhysicsComponentSimple: public PhysicsComponent
	{
	public:
		PhysicsComponentSimple(const std::string& type="");
		~PhysicsComponentSimple();

		virtual void create();
		virtual void destroy();

		OGRE3DBody* getNxOgreBody();
		void setNxOgreBody(OGRE3DBody* pNxOgreBody);

		NxOgre::RigidBodyDescription getNxOgreRigidBodyDescription();
		void setNxOgreRigidBodyDescription(NxOgre::RigidBodyDescription pNxOgreRigidBodyDescription);

	protected:
		OGRE3DBody* mNxOgreBody;
		NxOgre::RigidBodyDescription mNxOgreRigidBodyDescription;
	};

	class TPhysicsComponentSimpleParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentSimpleParameters();
		~TPhysicsComponentSimpleParameters();
	};
}

#endif