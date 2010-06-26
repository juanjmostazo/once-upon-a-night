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

		virtual void update(double elapsedSeconds);

		NxOgre::Convex* getNxOgreConvex();
		void setNxOgreConvex(NxOgre::Convex* pNxOgreConvex);

		OGRE3DBody* getNxOgreBody();
		void setNxOgreBody(OGRE3DBody* pNxOgreBody);

		OGRE3DKinematicBody* getNxOgreKinematicBody();
		void setNxOgreKinematicBody(OGRE3DKinematicBody* pNxOgreKinematicBody);

		void setBalancingParams(double balanceRadioX, double balanceRadioY, double balanceRadioZ, double balanceRadioTime);

	//	void setQueryFlags(QueryFlags queryFlags);

	protected:
		NxOgre::Convex* mNxOgreConvex;
		OGRE3DBody* mNxOgreBody;
		OGRE3DKinematicBody* mNxOgreKinematicBody;

		double mBalanceRadioX;
		double mBalanceRadioY;
		double mBalanceRadioZ;
		double mBalanceRadioTime;
	};

	class TPhysicsComponentComplexConvexParameters: public TPhysicsComponentComplexParameters
	{
	public:
		TPhysicsComponentComplexConvexParameters();
		~TPhysicsComponentComplexConvexParameters();

		double balanceRadioX;
		double balanceRadioY;
		double balanceRadioZ;
		double balanceRadioTime;
	};
}

#endif