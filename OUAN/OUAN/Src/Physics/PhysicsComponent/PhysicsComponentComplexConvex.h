#ifndef PhysicsComponentComplexConvexH_H
#define PhysicsComponentComplexConvexH_H

#include "PhysicsComponentComplex.h"
namespace OUAN
{
	// Complex elements with low detail, shape will be Convex
	class PhysicsComponentComplexConvex: public PhysicsComponentComplex
	{
	public:
		PhysicsComponentComplexConvex(const std::string& type="");
		~PhysicsComponentComplexConvex();

		virtual void create();
		virtual void destroy();

		NxOgre::Convex* getNxOgreConvex();
		void setNxOgreConvex(NxOgre::Convex* pNxOgreConvex);

		OGRE3DBody* getNxOgreBody();
		void setNxOgreBody(OGRE3DBody* pNxOgreBody);

		NxOgre::RigidBodyDescription getNxOgreRigidBodyDescription();
		void setNxOgreRigidBodyDescription(NxOgre::RigidBodyDescription pNxOgreRigidBodyDescription);

	protected:
		NxOgre::Convex* mNxOgreConvex;
		OGRE3DBody* mNxOgreBody;
		NxOgre::RigidBodyDescription mNxOgreRigidBodyDescription;
	};

	class TPhysicsComponentComplexConvexParameters: public TPhysicsComponentComplexParameters
	{
	public:
		TPhysicsComponentComplexConvexParameters();
		~TPhysicsComponentComplexConvexParameters();
	};
}

#endif