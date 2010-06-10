#ifndef PhysicsComponentCharacterOnyH_H
#define PhysicsComponentCharacterOnyH_H

#include "PhysicsComponentCharacter.h"

namespace OUAN
{
	// Elements with physics which are moved by us: Ony, enemies, etc.
	// They are mapped as capsules
	class PhysicsComponentCharacterOny: public PhysicsComponentCharacter
	{
	public:
		PhysicsComponentCharacterOny(const std::string& type="");
		~PhysicsComponentCharacterOny();

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