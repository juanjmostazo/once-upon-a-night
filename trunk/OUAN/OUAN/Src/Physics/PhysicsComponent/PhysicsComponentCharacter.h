#ifndef PhysicsComponentCharacterH_H
#define PhysicsComponentCharacterH_H

#include "PhysicsComponent.h"
namespace OUAN
{
	// Elements with physics which are moved by us: Ony, enemies, etc.
	// They are mapped as capsules
	class PhysicsComponentCharacter: public PhysicsComponent
	{
	public:
		PhysicsComponentCharacter(const std::string& type="");
		~PhysicsComponentCharacter();

		virtual void create();
		virtual void destroy();

		virtual double getMass();
		virtual void setMass(double pNxOgreMass);

		void setNxOgreController(NxOgre::Controller* pNxOgreController);
		NxOgre::Controller* getNxOgreController();

		void setNxOgreSize(NxOgre::Vec2 pNxOgreSize);
		NxOgre::Vec2 getNxOgreSize();

		void setNxOgreControllerDescription(NxOgre::ControllerDescription pNxOgreControllerDescription);
		NxOgre::ControllerDescription getNxOgreControllerDescription();

	protected:
		double mNxOgreMass;
		NxOgre::Controller* mNxOgreController;
		NxOgre::Vec2 mNxOgreSize;
		NxOgre::ControllerDescription mNxOgreControllerDescription;
	};

	class TPhysicsComponentCharacterParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentCharacterParameters();
		~TPhysicsComponentCharacterParameters();

		double radius;
		double height;
	};
}

#endif