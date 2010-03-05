#ifndef PhysicsComponentH_H
#define PhysicsComponentH_H

#include "../../Component/Component.h"
#include "../../Application.h"
#include "../PhysicsSubsystem.h"
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>
#include <NxOgreAddonCharacterController.h>

namespace OUAN
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(const std::string& type="");
		~PhysicsComponent();

		virtual void create();
		virtual void destroy();

		virtual void update(long elapsedTime);

		virtual Ogre::SceneNode* getSceneNode();
		virtual void setSceneNode(Ogre::SceneNode* sceneNode);
		
		virtual double getMass();
		virtual void setMass(double pNxOgreMass);

	protected:
		Ogre::SceneNode* mSceneNode;
		double mNxOgreMass;
	};

	class TPhysicsComponentParameters: public TComponentParameters
	{
	public:
		TPhysicsComponentParameters();
		~TPhysicsComponentParameters();

		double mass;
	};
}

#endif