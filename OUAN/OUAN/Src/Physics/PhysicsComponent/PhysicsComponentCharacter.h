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

		void setMovementFlags(int pMovementFlags);

	protected:
		double mNxOgreMass;
		NxOgre::Controller* mNxOgreController;
		NxOgre::Vec2 mNxOgreSize;
		NxOgre::ControllerDescription mNxOgreControllerDescription;

		/// Entity movement flags, will be updated every frame
		int mMovementFlags;

		// Physics states
		bool mJumping;
		bool mFalling;
		bool mSliding;
		bool mOnSurface;

		// Physics times
		double mJumpTime;
		double mFallTime;
		double mSlideTime;

		/// Physics speeds
		double mJumpSpeed;
		double mFallSpeed;
		double mSlideSpeed;

		void initJump();
		void initFall();

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