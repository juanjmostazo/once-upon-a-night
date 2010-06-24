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

		virtual bool isJumping() const;
		virtual bool isFalling() const;
		virtual bool isFallingLimit() const;
		virtual bool isWalking() const;
		virtual bool isMoving() const;

		virtual void setOuternMovement(Ogre::Vector3 outernMovement);
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

		virtual void setNextMovement(Ogre::Vector3 nextMovement);
		virtual Ogre::Vector3 getNextMovement();

		virtual void setLastMovement(Ogre::Vector3 lastMovement);
		virtual Ogre::Vector3 getOuternMovement();

		virtual void updateSceneNode();

		virtual void performCyclicMovement(double elapsedSeconds);
		virtual void performClassicMovement(double elapsedSeconds);

		virtual void applyWalkXZ(double elapsedSeconds);
		virtual void applyJumpY(double elapsedSeconds);
		virtual void applyFallY(double elapsedSeconds);

		virtual void scaleNextMovementXZ(double elapsedSeconds);
		virtual void scaleNextMovementXYZ(double elapsedSeconds);
		virtual bool isWorthUpdating();

		virtual void setNewYaw();

		virtual void logStatus(Ogre::String label, double elapsedSeconds);

		bool mWalking;
		bool mMoving;
		bool mJumping;
		bool mFalling;

		double mJumpingTime;
		double mFallingTime;

		double mNxOgreMass;
		NxOgre::Controller* mNxOgreController;
		NxOgre::Vec2 mNxOgreSize;
		NxOgre::ControllerDescription mNxOgreControllerDescription;

		Ogre::Vector3 mOuternMovement;
		Ogre::Vector3 mNextMovement;
		Ogre::Vector3 mLastMovement;

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