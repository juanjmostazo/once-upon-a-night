#include "TextureRenderer.h"
using namespace OUAN;
using namespace Ogre;
TextureRenderer::TextureRenderer()
{
	mDebugScreensActive=false;
}

TextureRenderer::~TextureRenderer()
{
}

void TextureRenderer::setDebugScreensActive(bool active)
{
	mDebugScreensActive=active;
	if(mDebugScreensActive)
	{
		mMiniScreenDreams->setVisible(true);
		mMiniScreenNightmares->setVisible(true);
		mMiniScreenChangeWorld->setVisible(true);
	}
	else
	{
		mMiniScreenDreams->setVisible(false);
		mMiniScreenNightmares->setVisible(false);
		mMiniScreenChangeWorld->setVisible(false);
	}
}

bool TextureRenderer::getDebugScreensActive() const
{
	return mDebugScreensActive;
}

void TextureRenderer::init(Ogre::SceneManager * pSceneManager,Ogre::RenderWindow* pWindow,Ogre::Camera * pCamera)
{
	mSceneManager=pSceneManager;
	mWindow=pWindow;
	mCamera=pCamera;

	//CREATE RENDER TEXTURES
		//dreams
	mTextureDreams = Ogre::TextureManager::getSingleton().createManual("mRenderTextureDreams",
	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, mWindow->getWidth(), mWindow->getHeight(), 0, PF_R8G8B8,
	TU_RENDERTARGET);
	mRenderTextureDreams = mTextureDreams->getBuffer()->getRenderTarget();
	mRenderTextureDreams->addViewport(mCamera);
	mRenderTextureDreams->getViewport(0)->setClearEveryFrame(true);
	mRenderTextureDreams->getViewport(0)->setBackgroundColour(ColourValue::Black);
	mRenderTextureDreams->setAutoUpdated(false);

		//nightmares
	mTextureNightmares = Ogre::TextureManager::getSingleton().createManual("mRenderTextureNightmares",
	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, mWindow->getWidth(), mWindow->getHeight(), 0, PF_R8G8B8,
	TU_RENDERTARGET);
	mRenderTextureNightmares = mTextureNightmares->getBuffer()->getRenderTarget();
	mRenderTextureNightmares->addViewport(mCamera);
	mRenderTextureNightmares->getViewport(0)->setClearEveryFrame(true);
	mRenderTextureNightmares->getViewport(0)->setBackgroundColour(ColourValue::Black);
	mRenderTextureNightmares->setAutoUpdated(false);

		//ChangeWorld
	mTextureChangeWorld = Ogre::TextureManager::getSingleton().createManual("mRenderTextureChangeWorld",
	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, mWindow->getWidth(), mWindow->getHeight(), 0, PF_R8G8B8,
	TU_RENDERTARGET);
	mRenderTextureChangeWorld = mTextureChangeWorld->getBuffer()->getRenderTarget();
	mRenderTextureChangeWorld->addViewport(mCamera);
	mRenderTextureChangeWorld->getViewport(0)->setClearEveryFrame(true);
	mRenderTextureChangeWorld->getViewport(0)->setBackgroundColour(ColourValue::Black);
	mRenderTextureChangeWorld->setAutoUpdated(false);

	//CREATE MINISCREENS
	Ogre::Technique * technique;
	//DREAMS
		//miniscreen
	mMiniScreenDreams = new Ogre::Rectangle2D(true);
	mMiniScreenDreams->setCorners(0.5, 1.0, 1.0, 0.5);
	mMiniScreenDreams->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE));
	Ogre::SceneNode *mMiniScreenDreamsNode = mSceneManager->getRootSceneNode()->createChildSceneNode("mMiniScreenDreamsNode");
	mMiniScreenDreamsNode->attachObject(mMiniScreenDreams);
		//material
	MaterialPtr materialDreams = MaterialManager::getSingleton().create("mMiniScreenMatDreams", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	technique = materialDreams->createTechnique();
	technique->createPass();
	materialDreams->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	materialDreams->getTechnique(0)->getPass(0)->createTextureUnitState("mRenderTextureDreams");
	mMiniScreenDreams->setMaterial("mMiniScreenMatDreams");

	//NIGHTMARES
	mMiniScreenNightmares = new Ogre::Rectangle2D(true);
	mMiniScreenNightmares->setCorners(0, 1.0, 0.5, 0.5);
	mMiniScreenNightmares->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE));
	Ogre::SceneNode *mMiniScreenNightmaresNode = mSceneManager->getRootSceneNode()->createChildSceneNode("mMiniScreenNightmaresNode");
	mMiniScreenNightmaresNode->attachObject(mMiniScreenNightmares);
		//material
	MaterialPtr materialNightmares = MaterialManager::getSingleton().create("mMiniScreenMatNightmares", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	technique = materialNightmares->createTechnique();
	technique->createPass();
	materialNightmares->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	materialNightmares->getTechnique(0)->getPass(0)->createTextureUnitState("mRenderTextureNightmares");
	mMiniScreenNightmares->setMaterial("mMiniScreenMatNightmares");

	//CHANGEWORLD
	mMiniScreenChangeWorld = new Ogre::Rectangle2D(true);
	mMiniScreenChangeWorld->setCorners(-0.5, 1.0, 0, 0.5);
	mMiniScreenChangeWorld->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE));
	Ogre::SceneNode *mMiniScreenChangeWorldNode = mSceneManager->getRootSceneNode()->createChildSceneNode("mMiniScreenChangeWorldNode");
	mMiniScreenChangeWorldNode->attachObject(mMiniScreenChangeWorld);
		//material
	MaterialPtr materialChangeWorld = MaterialManager::getSingleton().create("mMiniScreenMatChangeWorld", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	technique = materialChangeWorld->createTechnique();
	technique->createPass();
	materialChangeWorld->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	materialChangeWorld->getTechnique(0)->getPass(0)->createTextureUnitState("mRenderTextureChangeWorld");
	mMiniScreenChangeWorld->setMaterial("mMiniScreenMatChangeWorld");

	setDebugScreensActive(false);
}

void TextureRenderer::renderToTextureDreams()
{
	mMiniScreenDreams->setVisible(false);
	mMiniScreenNightmares->setVisible(false);
	mMiniScreenChangeWorld->setVisible(false);

	mRenderTextureDreams->update();
	//mRenderTextureDreams->writeContentsToFile("dreams_render.png");

	if(mDebugScreensActive)
	{
		mMiniScreenDreams->setVisible(true);
		mMiniScreenNightmares->setVisible(true);
		mMiniScreenChangeWorld->setVisible(true);
	}
}

void TextureRenderer::renderToTextureNightmares()
{
	mMiniScreenDreams->setVisible(false);
	mMiniScreenNightmares->setVisible(false);
	mMiniScreenChangeWorld->setVisible(false);

	mRenderTextureNightmares->update();
	//mRenderTextureNightmares->writeContentsToFile("nightmares_render.png");

	if(mDebugScreensActive)
	{
		mMiniScreenDreams->setVisible(true);
		mMiniScreenNightmares->setVisible(true);
		mMiniScreenChangeWorld->setVisible(true);
	}
}

void TextureRenderer::renderToTextureChangeWorld()
{
	mMiniScreenDreams->setVisible(false);
	mMiniScreenNightmares->setVisible(false);
	mMiniScreenChangeWorld->setVisible(false);

	mRenderTextureChangeWorld->update();
	//mRenderTextureChangeWorld->writeContentsToFile("changeworld_render.png");

	if(mDebugScreensActive)
	{
		mMiniScreenDreams->setVisible(true);
		mMiniScreenNightmares->setVisible(true);
		mMiniScreenChangeWorld->setVisible(true);
	}
}

void TextureRenderer::setCamera(Ogre::Camera * pCamera)
{
	mCamera=pCamera;
}

Ogre::Camera * TextureRenderer::getCamera() const
{
	return mCamera;
}


