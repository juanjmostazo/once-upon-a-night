#ifndef TextureRendererH_H
#define TextureRendererH_H

#include "../OUAN.h"
#include "RenderSubsystem.h"
namespace OUAN
{
	class TextureRenderer
	{
	public:
		TextureRenderer();
		~TextureRenderer();


		void setDebugScreensActive(bool active);
		bool getDebugScreensActive() const;

		void init(Ogre::SceneManager * pSceneManager,Ogre::RenderWindow* pWindow,Ogre::Camera * pCamera);

		void renderToTextureDreams();
		void renderToTextureNightmares();
		void renderToTextureChangeWorld();

		void setCamera(Ogre::Camera * pCamera);
		Ogre::Camera * getCamera() const;

	protected:
		Ogre::SceneManager * mSceneManager;
		Ogre::RenderWindow* mWindow;
		Ogre::Camera * mCamera;

		bool mDebugScreensActive;

		Ogre::TexturePtr mTextureChangeWorld;
		Ogre::TexturePtr mTextureNightmares;
		Ogre::TexturePtr mTextureDreams;

		Ogre::RenderTexture	   *mRenderTextureDreams;
		Ogre::RenderTexture	   *mRenderTextureNightmares;
		Ogre::RenderTexture	   *mRenderTextureChangeWorld;

		Ogre::Rectangle2D *mMiniScreenDreams; 
		Ogre::Rectangle2D *mMiniScreenNightmares;
		Ogre::Rectangle2D *mMiniScreenChangeWorld;
	};

}

#endif