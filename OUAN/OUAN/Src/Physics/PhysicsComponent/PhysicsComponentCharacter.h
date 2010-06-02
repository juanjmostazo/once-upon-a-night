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

		void update(double elapsedSeconds);

		void setNxOgreController(NxOgre::Controller* pNxOgreController);
		NxOgre::Controller* getNxOgreController();

		void setNxOgreSize(NxOgre::Vec2 pNxOgreSize);
		NxOgre::Vec2 getNxOgreSize();

		void setNxOgreControllerDescription(NxOgre::ControllerDescription pNxOgreControllerDescription);
		NxOgre::ControllerDescription getNxOgreControllerDescription();

		void setNextMovement(NxOgre::Vec3 nextMovement);
		NxOgre::Vec3 getNextMovement();

		NxOgre::Vec3 getLastMovement();

		void correctSceneNodePosition();

		void setSlidingValues(NxOgre::Vec3 pNormal, double pNormalAngle);

		void jump();

		void walk();

		void reset();

		//Query methods used by the logic component, between others, to check if the
		//character is jumping/etc
		bool isJumping() const;
		bool isFalling() const;
		bool isFallingLimit() const;
		bool isSliding() const;
		bool isMoving() const;
		bool isOnSurface() const;
		void setOnSurface(bool pOnSurface);

		void setOffsetRenderPosition(Vector3 offsetRenderPosition);
		Vector3 getOffsetRenderPosition() const;

	protected:
		void applyDash(double elapsedSeconds);
		Vector3 getDashMovement(double elapsedSeconds);
		void calculateAngleDifference();
		void calculateAcceleration(double elapsedSeconds);

		void applyGravity(double elapsedSeconds);

		double getYawFromMovement(NxOgre::Vec3 movement);

		void setLastMovement(NxOgre::Vec3 lastMovement);
	
		//Uses mNextMovement to set Character's display yaw
		void setCharactersDisplayYaw();

		double mNxOgreMass;
		NxOgre::Controller* mNxOgreController;
		NxOgre::Vec2 mNxOgreSize;
		NxOgre::ControllerDescription mNxOgreControllerDescription;

		/// Entity next movement, will be updated and reset to zero at update()
		NxOgre::Vec3 mNextMovement;
		/// Entiti's last movement: it'll be used to follow a path.
		NxOgre::Vec3 mLastMovement;

		OGRE3DPointRenderable* mPointRenderable;

		// Physics states
		bool mJumping;
		bool mFalling;
		bool mFallingLimit;
		bool mSliding;
		bool mIsWalking;

		// Physics times
		double mFallTime;

		/// Physics components
		double mJumpSpeed;
		double mFallSpeed;
		NxOgre::Vec3 mSlideDisplacement;
		double mNormalAngle;

		/// Angle difference
		double mLastYaw;
		double mAngleDifference;

		/// Dash 
		double mDashAccelerationFactor;
		double mDash;
		Vector3 mDashDirection;
		bool mIsNotApplyingDash;

		/// Acceleration
		double mAccelerationFactor;

		// Other values
		Vector3 mOffsetRenderPosition;

		void initJump();
		void initFall();
		void resetSliding();

		void setJumpSpeed(double pJumpSpeed);
		void setFallSpeed(double pFallSpeed);
	};

	class TPhysicsComponentCharacterParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentCharacterParameters();
		~TPhysicsComponentCharacterParameters();

		double radius;
		double height;
		Vector3 scale_correction;
		Vector3 position_correction;
	};
}

#endif