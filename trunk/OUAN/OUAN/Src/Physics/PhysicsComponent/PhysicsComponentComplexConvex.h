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

		OGRE3DKinematicBody* getNxOgreKinematicBody();
		void setNxOgreKinematicBody(OGRE3DKinematicBody* pNxOgreKinematicBody);

		void setBalancingParams(double balanceRadiumX, double balanceRadiumY, double balanceRadiumZ, double balanceRadiumTime);

		virtual Ogre::Vector3 getPosition();
		virtual void setPosition(Ogre::Vector3 position);

	//	void setQueryFlags(QueryFlags queryFlags);

	protected:
		NxOgre::Convex* mNxOgreConvex;
		OGRE3DBody* mNxOgreBody;
		OGRE3DKinematicBody* mNxOgreKinematicBody;

		//double mBalanceRadiumX;
		//double mBalanceRadiumY;
		//double mBalanceRadiumZ;
		//double mBalanceRadiumTime;

		//Ogre::Vector3 mBalanceLastWasPositive;  // VALUES{1,0}
		//Ogre::Vector3 mBalanceLastWasCenter;    // VALUES{1,0}
		//Ogre::Vector3 mBalanceLastWasNegative;  // VALUES{1,0}
		//Ogre::Vector3 mBalanceDirection;        // VALUES{1,-1}
		//double mBalanceAccumulatedTime;

		//virtual bool canUpdateBalancing(double elapsedSeconds);
		//virtual void updateBalancing(double elapsedSeconds);
	};

	class TPhysicsComponentComplexConvexParameters: public TPhysicsComponentComplexParameters
	{
	public:
		TPhysicsComponentComplexConvexParameters();
		~TPhysicsComponentComplexConvexParameters();

		double balanceRadiumX;
		double balanceRadiumY;
		double balanceRadiumZ;
		double balanceRadiumTime;
	};
}

#endif