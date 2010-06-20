#ifndef PhysicsComponentCharacterH_H
#define PhysicsComponentCharacterH_H

#include "PhysicsComponent.h"

namespace OUAN
{
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

		virtual void setCyclicCharacter(bool pCyclicCharacter);
		virtual bool isCyclicCharacter();

		virtual void setNxOgreController(NxOgre::Controller* pNxOgreController);
		virtual NxOgre::Controller* getNxOgreController();

		virtual void setNxOgreSize(NxOgre::Vec2 pNxOgreSize);
		virtual NxOgre::Vec2 getNxOgreSize();

		virtual void setNxOgreControllerDescription(NxOgre::ControllerDescription pNxOgreControllerDescription);
		virtual NxOgre::ControllerDescription getNxOgreControllerDescription();

		virtual void walk();
		virtual void jump();

		virtual void setOuternMovement(NxOgre::Vec3 outernMovement);

		virtual bool isJumping() const;
		virtual bool isFalling() const;
		virtual bool isFallingLimit() const;
		virtual bool isWalking() const;
		virtual bool isMoving() const;

		virtual Ogre::Vector3 getLastMovement();
		virtual Ogre::Vector3 getPosition();
		virtual double getYaw();

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

		virtual void setNextMovement(NxOgre::Vec3 nextMovement);
		virtual NxOgre::Vec3 getNextMovement();

		virtual void setLastMovement(NxOgre::Vec3 lastMovement);
		virtual NxOgre::Vec3 getOuternMovement();

		virtual void updateSceneNode();

		virtual void performCyclicMovement(double elapsedSeconds);
		virtual void performClassicMovement(double elapsedSeconds);

		virtual void scaleNextMovement(double elapsedSeconds);
		virtual bool isWorthUpdating();

		virtual void setNewYaw();
		virtual void setJumpingSpeed(double pJumpingSpeed);
		virtual void setFallingSpeed(double pFallingSpeed);

		virtual void logStatus(Ogre::String label);

		bool mWalking;
		bool mMoving;
		bool mJumping;
		bool mFalling;

		double mJumpingTime;
		double mJumpingSpeed;
		double mFallingTime;
		double mFallingSpeed;

		double mNxOgreMass;
		NxOgre::Controller* mNxOgreController;
		NxOgre::Vec2 mNxOgreSize;
		NxOgre::ControllerDescription mNxOgreControllerDescription;

		NxOgre::Vec3 mOuternMovement;
		NxOgre::Vec3 mNextMovement;
		NxOgre::Vec3 mLastMovement;

		Vector3 mOffsetRenderPosition;

		bool mCyclicCharacter;
		double mCyclicDirection;
		double mCyclicOffset;
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