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

		virtual bool isInUse();
		virtual void setInUse(bool pInUse);

		virtual bool isStatic();
		virtual void setStatic(bool pStatic);

	protected:
		// Tells if the component is in use or not
		bool mInUse;

		// Tells if the game entiy is static or can be moved
		bool mStatic;

		// Related game entity scene node
		Ogre::SceneNode* mSceneNode;
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