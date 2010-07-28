#ifndef PhysicsComponentWeaponH_H
#define PhysicsComponentWeaponH_H

#include "PhysicsComponentCharacter.h"

namespace OUAN
{
	class PhysicsComponentWeapon: public PhysicsComponentCharacter
	{
	public:
		PhysicsComponentWeapon(const std::string& type="");
		~PhysicsComponentWeapon();

		virtual void reset();
		virtual void update(double elapsedSeconds);

		virtual void setMovementFactor(double movementFactor);
		virtual double getMovementFactor();

		virtual void setInflateSpeed(double inflateSpeed);
		virtual double getInflateSpeed();

		virtual void setNxOgreMaxSize(NxOgre::Vec2 pNxOgreSize);
		virtual NxOgre::Vec2 getNxOgreMaxSize();

		virtual void startAttack();
		virtual void endAttack();

		virtual void setOuternMovement(Ogre::Vector3 outernMovement);

	protected:
		virtual void applyFallY(double elapsedSeconds);
		virtual void applyOuternMovement(double elapsedSeconds);
		void applyMove();
		virtual void updateSceneNode();
		double mMovementFactor;
		double mInflateSpeed;

		NxOgre::Vec2 mNxOgreMaxSize;
	};

	class TPhysicsComponentWeaponParameters: public TPhysicsComponentCharacterParameters
	{
	public:
		TPhysicsComponentWeaponParameters();
		~TPhysicsComponentWeaponParameters();
		double movementFactor;
		double inflateSpeed;
	};
}

#endif