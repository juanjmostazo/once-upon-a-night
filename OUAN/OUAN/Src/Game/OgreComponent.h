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
		Ogre::Camera* mCamera;
		Ogre::ParticleSystem* mParticleSystem;
		Ogre::BillboardSet* mBillboardSet;
		Ogre::Light* mLight;
		//[TODO] Other members
	public:
		OgreComponent(const std::string& name="");
		~OgreComponent();
		Ogre::SceneNode* getSceneNode() const;
		void setSceneNode(Ogre::SceneNode* sceneNode);
		Ogre::Entity* getEntity() const;
		void setEntity(Ogre::Entity* entity);
		Ogre::Camera* getCamera() const;
		void setCamera(Ogre::Camera* camera);
		Ogre::ParticleSystem* getParticleSystem() const;
		void setParticleSystem(Ogre::ParticleSystem* particleSystem);
		Ogre::BillboardSet* getBillboardSet() const;
		void setBillboardSet(Ogre::BillboardSet* billboardSet);
		Ogre::Light* getLight() const;
		void setLight(Ogre::Light* light);
		void update(long elapsedTime);

		//Event handlers
		//void onDoSomething(EventData,emitter, ...);
		//void onDoSomethingElse(...);
	};
}

#endif