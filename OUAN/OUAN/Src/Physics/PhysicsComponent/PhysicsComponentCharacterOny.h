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

		virtual bool isWorthUpdating();
		virtual bool canJump();

	protected:
		
	};

	class TPhysicsComponentCharacterOnyParameters: public TPhysicsComponentCharacterParameters
	{
	public:
		TPhysicsComponentCharacterOnyParameters();
		~TPhysicsComponentCharacterOnyParameters();
	};
}

#endif