#ifndef PhysicsComponentCharacterH_H
#define PhysicsComponentCharacterH_H

#include "PhysicsComponent.h"

namespace OUAN
{
	const double SAFE_SURFACE_DISTANCE=0.1;

	class PhysicsComponentCharacter: public PhysicsComponent
	{
	public:
		PhysicsComponentCharacter(const std::string& type="");
		~PhysicsComponentCharacter();

		virtual void reset();
		virtual void update(double elapsedSeconds);

		virtual void create();
		virtual void destroy();

		virtual void setOffsetRenderPosition(Vector3 offsetRenderPosition);
		virtual Vector3 getOffsetRenderPosition() const;

		virtual void setOffsetDisplayYaw(double offsetDisplayYaw);
		virtual double getOffsetDisplayYaw() const;

		virtual void setCyclicCharacter(bool pCyclicCharacter);
		virtual bool isCyclicCharacter();

		virtual void setFlyingCharacter(bool pFlyingCharacter);
		virtual bool isFlyingCharacter();


		virtual void calculateSliding(Ogre::Vector3 normal);


		virtual void setNxOgreController(NxOgre::Controller* pNxOgreController);
		virtual NxOgre::Controller* getNxOgreController();

		virtual void setNxOgreSize(NxOgre::Vec2 pNxOgreSize);
		virtual NxOgre::Vec2 getNxOgreSize();

		virtual void setNxOgreControllerDescription(NxOgre::ControllerDescription pNxOgreControllerDescription);
		virtual NxOgre::ControllerDescription getNxOgreControllerDescription();

		virtual void walk();
		virtual void jump();

		virtual void setLastSurfacePosition(Ogre::Vector3 lastSurfacePosition);
		virtual Vector3 getLastSurfacePosition() const;

		virtual bool isJumping() const;
		virtual bool isFalling() const;
		virtual bool isFallingLimit() const;
		virtual bool isWalking() const;
		virtual bool isMoving() const;
		virtual bool isSliding() const;

		virtual void setOuternMovement(Ogre::Vector3 outernMovement);
		virtual Ogre::Vector3 getOuternMovement();
		virtual Ogre::Vector3 getLastMovement();

		virtual void setPosition(Ogre::Vector3 position);
		virtual Ogre::Vector3 getPosition();

		virtual double getYaw();

		virtual void setDisplayYaw(double displayYaw);
		virtual double getDisplayYaw();

		virtual void stabilize(double elapsedSeconds);

		virtual void updateSceneNode();

	protected:
		virtual void resetJumpingVars();
		virtual void resetFallingVars();
		virtual void resetCyclicVars();
		virtual void resetMovementVars();

		virtual void initJumpingVars();
		virtual void initFallingVars();

		virtual bool canJump();

		virtual void setMoving (bool pMoving);
		virtual void setWalking (bool pWalking);
		virtual void setOnSurface(bool pOnSurface);
		virtual void setLastElapsedSeconds(double pLastElapsedSeconds);

		virtual void applyOuternMovement(double elapsedSeconds);

		virtual void setNextMovement(Ogre::Vector3 nextMovement);
		virtual Ogre::Vector3 getNextMovement();

		virtual void setLastMovement(Ogre::Vector3 lastMovement);

		virtual void performCyclicMovement(double elapsedSeconds);
		virtual void performClassicMovement(double elapsedSeconds);

		virtual void applyWalkXZ(double elapsedSeconds);
		virtual void applyJumpY(double elapsedSeconds);
		virtual void applyFallY(double elapsedSeconds);
		virtual void applySlideY(double elapsedSeconds);

		virtual void applyMove();

		virtual void scaleNextMovementXZ(double elapsedSeconds);
		virtual void scaleNextMovementXYZ(double elapsedSeconds);
		virtual bool isWorthUpdating();

		virtual void setNewYaw(double elapsedSeconds);
		virtual double calculateMovementDisplayYaw();
		virtual void setRotationMovementFactor(double angleDifference);

		virtual void logStatus(Ogre::String label, double elapsedSeconds);

		double calculateAngleDifference(double angle1, double angle2);

		bool mWalking;
		bool mMoving;
		bool mJumping;
		bool mFalling;
		bool mSliding;
		bool mSlidingCalculatedThisFrame;

		double mJumpingTime;
		double mFallingTime;

		double mNxOgreMass;
		NxOgre::Controller* mNxOgreController;
		NxOgre::Vec2 mNxOgreSize;
		NxOgre::ControllerDescription mNxOgreControllerDescription;

		Ogre::Vector3 mOuternMovement;
		Ogre::Vector3 mNextMovement;
		Ogre::Vector3 mLastMovement;
		Ogre::Vector3 mLastSurfacePosition;
		Ogre::Vector3 mSlidingDirection;

		Vector3 mOffsetRenderPosition;
		double mOffsetDisplayYaw;

		bool mCyclicCharacter;
		double mCyclicDirection;
		double mCyclicOffset;

		double mFlyingCharacter;

		double mLastElapsedSeconds;
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
		double yaw_correction;
	};
}

#endif