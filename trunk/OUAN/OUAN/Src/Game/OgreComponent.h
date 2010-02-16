#ifndef OGRECOMPONENTH_H
#define OGRECOMPONENTH_H

#include "../OUAN.h"
#include "Component.h"
namespace OUAN
{
	class OgreComponent: public Component
	{
	private:
		Ogre::SceneNode* mSceneNode;
		Ogre::Entity* mEntity;
		//[TODO] Other members
	public:
		OgreComponent(const std::string& name="");
		~OgreComponent();
		Ogre::SceneNode* getSceneNode() const;
		void setSceneNode(Ogre::SceneNode* sceneNode);
		Ogre::Entity* getEntity() const;
		void setEntity(Ogre::Entity* entity);

		void update(long elapsedTime);

		//Event handlers
		//void onDoSomething(EventData,emitter, ...);
		//void onDoSomethingElse(...);
	};
}

#endif