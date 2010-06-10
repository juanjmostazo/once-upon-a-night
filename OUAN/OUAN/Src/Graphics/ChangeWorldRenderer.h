#ifndef ChangeWorldRendererH_H
#define ChangeWorldRendererH_H

#include "../OUAN.h"
#include "RenderSubsystem.h"
namespace OUAN
{

	class ChangeWorldCompositorListener : public Ogre::CompositorInstance::Listener
	{
	   public:
		  void notifyMaterialSetup( Ogre::uint32 pass_id, Ogre::MaterialPtr & mat )
		  {
				// modify material here (wont alter the base material!) in the setup stage
		  }

			void setChangeWorldFactor(float factor)
			{
				
			}
	 
	};

	class ChangeWorldRenderer
	{
	public:
		ChangeWorldRenderer();
		~ChangeWorldRenderer();


		void setDebugScreensActive(bool active);
		bool getDebugScreensActive() const;

		void init(Ogre::SceneManager * pSceneManager,Ogre::RenderWindow* pWindow,Ogre::Camera * pCamera);

		void renderToTextureDreams();
		void renderToTextureNightmares();
		void renderToTextureChangeWorld();

		void setCamera(Ogre::Camera * pCamera);
		Ogre::Camera * getCamera() const;

		void setToDreams();
		void setToNightmares();
		void setChangeWorldFactor(float factor);

	protected:
		Ogre::SceneManager * mSceneManager;
		Ogre::RenderWindow* mWindow;
		Ogre::Camera * mCamera;

		bool mDebugScreensActive;
		int mChangingWorldTo;

		Ogre::TexturePtr mTextureChangeWorld;
		Ogre::TexturePtr mTextureNightmares;
		Ogre::TexturePtr mTextureDreams;

		Ogre::TexturePtr mTextureNightmaresWithMiniScreen;
		Ogre::TexturePtr mTextureDreamsWithMiniScreen;

		Ogre::RenderTexture	   *mRenderTextureDreams;
		Ogre::RenderTexture	   *mRenderTextureNightmares;
		Ogre::RenderTexture	   *mRenderTextureChangeWorld;

		Ogre::RenderTexture	   *mRenderTextureDreamsWithMiniScreen;
		Ogre::RenderTexture	   *mRenderTextureNightmaresWithMiniScreen;

		Ogre::Rectangle2D *mMiniScreenDreams; 
		Ogre::Rectangle2D *mMiniScreenNightmares;
		Ogre::Rectangle2D *mMiniScreenChangeWorld;
	};

}

#endif