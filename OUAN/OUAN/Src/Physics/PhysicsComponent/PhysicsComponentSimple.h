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

		virtual void update(double elapsedSeconds);

		OGRE3DBody* getNxOgreBody();
		void setNxOgreBody(OGRE3DBody* pNxOgreBody);

		OGRE3DKinematicBody* getNxOgreKinematicBody();
		void setNxOgreKinematicBody(OGRE3DKinematicBody* pNxOgreKinematicBody);

		NxOgre::Vec3 getNxOgrePosition();

	protected:
		OGRE3DBody* mNxOgreBody;
		OGRE3DKinematicBody* mNxOgreKinematicBody;

		double mHeight;
	};

	class TPhysicsComponentSimpleParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentSimpleParameters();
		~TPhysicsComponentSimpleParameters();
	};
}

#endif