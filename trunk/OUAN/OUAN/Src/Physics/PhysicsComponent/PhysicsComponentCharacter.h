#ifndef PhysicsComponentCharacterH_H
#define PhysicsComponentCharacterH_H

#include "PhysicsComponent.h"
namespace OUAN
{
	class PhysicsComponentCharacter: public PhysicsComponent
	{
	public:
		PhysicsComponentCharacter(const std::string& name="");
		~PhysicsComponentCharacter();
	};

	class TPhysicsComponentCharacterParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentCharacterParameters();
		~TPhysicsComponentCharacterParameters();
	};
}

#endif