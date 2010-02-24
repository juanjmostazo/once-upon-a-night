#ifndef PhysicsComponentH_H
#define PhysicsComponentH_H

#include "../../Component/Component.h"
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>
#include <NxOgreAddonCharacterController.h>

namespace OUAN
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(const std::string& name="");
		~PhysicsComponent();

		virtual void update(long elapsedTime);

		virtual Ogre::SceneNode* getSceneNode();
		virtual void setSceneNode(Ogre::SceneNode* sceneNode);
		
		virtual double getMass();
		virtual void setMass(double pNxOgreMass);

		virtual double getDensity();
		virtual void setDensity(double pNxOgreDensity);

	protected:
		Ogre::SceneNode* mSceneNode;
		double mNxOgreMass;
		double mNxOgreDensity;
	};

	class TPhysicsComponentParameters: public TComponentParameters
	{
	public:
		TPhysicsComponentParameters();
		~TPhysicsComponentParameters();

		double mass;
		double density;
	};
}

#endif