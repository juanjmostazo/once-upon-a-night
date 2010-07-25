#ifndef PhysicsComponentPillowH_H
#define PhysicsComponentPillowH_H

#include "PhysicsComponentCharacter.h"

namespace OUAN
{
	class PhysicsComponentPillow: public PhysicsComponentCharacter
	{
	public:
		PhysicsComponentPillow(const std::string& type="");
		~PhysicsComponentPillow();

		virtual void reset();
		virtual void update(double elapsedSeconds);

		virtual void setMovementFactor(double movementFactor);
		virtual double getMovementFactor();
	protected:
		virtual void applyFallY(double elapsedSeconds);
		virtual void applyOuternMovement(double elapsedSeconds);
		void applyMove();

		double mMovementFactor;
	};

	class TPhysicsComponentPillowParameters: public TPhysicsComponentCharacterParameters
	{
	public:
		TPhysicsComponentPillowParameters();
		~TPhysicsComponentPillowParameters();
		double movementFactor;
	};
}

#endif