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
		//Event handlers
		//void onDoSomething(EventData,emitter, ...);
		//void onDoSomethingElse(...);
	protected:
		Ogre::SceneNode* sceneNode;
	};

	class TPhysicsComponentParameters: public TComponentParameters
	{
	public:
		TPhysicsComponentParameters();
		~TPhysicsComponentParameters();

		float mass;
		float density;
	};
}

#endif