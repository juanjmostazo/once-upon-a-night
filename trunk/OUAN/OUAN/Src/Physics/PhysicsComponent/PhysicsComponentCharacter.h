#ifndef PhysicsComponentCharacterH_H
#define PhysicsComponentCharacterH_H

#include "PhysicsComponent.h"
namespace OUAN
{
	// Elements with physics which are moved by us: Ony, enemies, etc.
	// They are mapped as capsules
	class PhysicsComponentCharacter: public PhysicsComponent
	{
	public:
		PhysicsComponentCharacter(const std::string& type="");
		~PhysicsComponentCharacter();

		virtual void create();
		virtual void destroy();

		virtual void update(double elapsedSeconds);

		void setNxOgreController(NxOgre::Controller* pNxOgreController);
		NxOgre::Controller* getNxOgreController();

		void setNxOgreSize(NxOgre::Vec2 pNxOgreSize);
		NxOgre::Vec2 getNxOgreSize();

		void setNxOgreControllerDescription(NxOgre::ControllerDescription pNxOgreControllerDescription);
		NxOgre::ControllerDescription getNxOgreControllerDescription();

		void setNextMovement(NxOgre::Vec3 nextMovement);
		NxOgre::Vec3 getNextMovement();

		void setSlidingValues(NxOgre::Vec3 pNormal, double pNormalAngle);

	protected:
	
		//Uses mNextMovement to set Character's display yaw
		void setCharactersDisplayYaw();

		double mNxOgreMass;
		NxOgre::Controller* mNxOgreController;
		NxOgre::Vec2 mNxOgreSize;
		NxOgre::ControllerDescription mNxOgreControllerDescription;

		/// Entity next movement, will be updated and reset to zero at update()
		NxOgre::Vec3 mNextMovement;

		// Physics states
		bool mJumping;
		bool mFalling;
		bool mSliding;
		bool mOnSurface;

		// Physics times
		double mJumpTime;
		double mFallTime;

		/// Physics components
		double mJumpSpeed;
		double mFallSpeed;
		NxOgre::Vec3 mSlideDisplacement;
		double mNormalAngle;

		void initJump();
		void initFall();
		void resetSliding();

		void setJumpSpeed(double pJumpSpeed);
		void setFallSpeed(double pFallSpeed);
		void setOnSurface(bool pOnSurface);
	};

	class TPhysicsComponentCharacterParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentCharacterParameters();
		~TPhysicsComponentCharacterParameters();

		double radius;
		double height;
	};
}

#endif