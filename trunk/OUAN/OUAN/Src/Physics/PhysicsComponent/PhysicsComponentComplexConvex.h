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

		bool mBalanceLastWasTop;
		bool mBalanceLastWasCenter;
		bool mBalanceLastWasBottom;
		double mBalanceDirection;
		double mBalanceAccumulatedTime;

		virtual bool canUpdateBalancing(double elapsedSeconds);
		virtual void updateBalancing(double elapsedSeconds);
		
		virtual Ogre::Vector3 getPosition();
		virtual void setPosition(Ogre::Vector3 position);
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