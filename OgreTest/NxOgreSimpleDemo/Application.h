#pragma once

#include <Ogre.h>
#include <NxOgre.h>
#include <NxOgreOGRE3D.h>

#include "SimpleInputManager.h"

class Application : SimpleInputManager
{
	public:
		Application();
		~Application();

		bool initialise();
		bool setup();
		void update();

		void updateOverlayInfo();
		virtual void loadResources();

		virtual bool keyPressed( const OIS::KeyEvent& e );
		virtual bool mouseMoved( const OIS::MouseEvent& e );

	private:
		Ogre::Root* m_root;
		Ogre::RenderWindow* m_window;
		Ogre::SceneManager* m_sceneMgr;
		Ogre::Viewport* m_viewport;
		Ogre::Camera* m_camera;

		NxOgre::World* m_NXOgreWorld;
		NxOgre::Scene* m_NXOgreScene;
		OGRE3DRenderSystem* m_NXOgreRenderSystem;
		NxOgre::TimeController* m_NXOgreTimeController;

		bool m_exitRequested;
		bool m_showInfo;
};