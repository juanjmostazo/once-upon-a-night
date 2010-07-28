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
	protected:
		virtual void applyFallY(double elapsedSeconds);
		virtual void applyOuternMovement(double elapsedSeconds);
		void applyMove();
		virtual void updateSceneNode();
		double mMovementFactor;
	};

	class TPhysicsComponentWeaponParameters: public TPhysicsComponentCharacterParameters
	{
	public:
		TPhysicsComponentWeaponParameters();
		~TPhysicsComponentWeaponParameters();
		double movementFactor;
	};
}

#endif