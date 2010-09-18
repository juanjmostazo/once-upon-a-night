#ifndef PhysicsComponentCharacterOnyH_H
#define PhysicsComponentCharacterOnyH_H

#include "PhysicsComponentCharacter.h"

namespace OUAN
{
	class PhysicsComponentCharacterOny: public PhysicsComponentCharacter
	{
	public:
		PhysicsComponentCharacterOny(const std::string& type="");
		~PhysicsComponentCharacterOny();

		virtual void reset();
		virtual void update(double elapsedSeconds);

		void disactivateGravityNextFrame();

		double getLastFallingTime() const;

	protected:
		virtual bool isWorthUpdating();
		virtual bool canJump();
		virtual void applyOuternMovement(double elapsedSeconds);
		virtual void applyFallY(double elapsedSeconds);
		void resetFallingVars();

		bool mApplyGravityNextFrame;
	private:
		double mLastFallingTime;
	};

	class TPhysicsComponentCharacterOnyParameters: public TPhysicsComponentCharacterParameters
	{
	public:
		TPhysicsComponentCharacterOnyParameters();
		~TPhysicsComponentCharacterOnyParameters();
	};
}

#endif