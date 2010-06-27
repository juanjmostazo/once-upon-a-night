#include "OUAN_Precompiled.h"

#include "ChangeWorldRenderer.h"
#include "../Application.h"
#include "../Game/GameWorldManager.h"
using namespace OUAN;
using namespace Ogre;
ChangeWorldRenderer::ChangeWorldRenderer()
{
	mDebugScreensActive=false;
}

ChangeWorldRenderer::~ChangeWorldRenderer()
{
}

void ChangeWorldRenderer::setDebugScreensActive(bool active)
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

	if(mChangingWorldTo==NIGHTMARES)
	{
		setToNightmares();
	}
	else if(mChangingWorldTo==DREAMS)
	{
		setToDreams();
	}
}

bool ChangeWorldRenderer::getDebugScreensActive() const
{
	return mDebugScreensActive;
}

void ChangeWorldRenderer::init(Ogre::SceneManager * pSceneManager,Ogre::RenderWindow* pWindow,Ogre::Camera * pCamera)
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

		//dreams with screens
	mTextureDreamsWithMiniScreen = Ogre::TextureManager::getSingleton().createManual("mRenderTextureDreamsWithMiniScreen",
	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, mWindow->getWidth(), mWindow->getHeight(), 0, PF_R8G8B8,
	TU_RENDERTARGET);
	mRenderTextureDreamsWithMiniScreen = mTextureDreamsWithMiniScreen->getBuffer()->getRenderTarget();
	mRenderTextureDreamsWithMiniScreen->addViewport(mCamera);
	mRenderTextureDreamsWithMiniScreen->getViewport(0)->setClearEveryFrame(true);
	mRenderTextureDreamsWithMiniScreen->getViewport(0)->setBackgroundColour(ColourValue::Black);
	mRenderTextureDreamsWithMiniScreen->setAutoUpdated(false);

		//nightmares with screens
	mTextureNightmaresWithMiniScreen = Ogre::TextureManager::getSingleton().createManual("mRenderTextureNightmaresWithMiniScreen",
	ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, mWindow->getWidth(), mWindow->getHeight(), 0, PF_R8G8B8,
	TU_RENDERTARGET);
	mRenderTextureNightmaresWithMiniScreen = mTextureNightmaresWithMiniScreen->getBuffer()->getRenderTarget();
	mRenderTextureNightmaresWithMiniScreen->addViewport(mCamera);
	mRenderTextureNightmaresWithMiniScreen->getViewport(0)->setClearEveryFrame(true);
	mRenderTextureNightmaresWithMiniScreen->getViewport(0)->setBackgroundColour(ColourValue::Black);
	mRenderTextureNightmaresWithMiniScreen->setAutoUpdated(false);

	createDebugMiniScreens();

}

void ChangeWorldRenderer::createDebugMiniScreens()
{
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

void ChangeWorldRenderer::setToDreams()
{
	Ogre::Technique * technique;
	//FINAL SCREEN
	   //set textures to changeworld compositor
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("changeworld");
	technique= material->getTechnique(0);
	technique->getPass(0)->getTextureUnitState(0)->setTextureName("mRenderTextureChangeWorld");
	if(mDebugScreensActive)
	{
		technique->getPass(0)->getTextureUnitState(1)->setTextureName("mRenderTextureNightmaresWithMiniScreen");
	}
	else
	{
		technique->getPass(0)->getTextureUnitState(1)->setTextureName("mRenderTextureNightmares");
	}
	mChangingWorldTo=DREAMS;
}

void ChangeWorldRenderer::setToNightmares()
{
	Ogre::Technique * technique;
	//FINAL SCREEN
	   //set textures to changeworld compositor
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("changeworld");
	technique= material->getTechnique(0);
	technique->getPass(0)->getTextureUnitState(0)->setTextureName("mRenderTextureChangeWorld");
	if(mDebugScreensActive)
	{
		technique->getPass(0)->getTextureUnitState(1)->setTextureName("mRenderTextureDreamsWithMiniScreen");
	}
	else
	{
		technique->getPass(0)->getTextureUnitState(1)->setTextureName("mRenderTextureDreams");
	}
	mChangingWorldTo=NIGHTMARES;
}

void ChangeWorldRenderer::setChangeWorldFactor(float factor)
{
	Ogre::Technique * technique;
	Ogre::GpuProgramParametersSharedPtr params;
	//FINAL SCREEN
	   //set textures to changeworld compositor
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("changeworld");
	technique= material->getTechnique(0);
	params=technique->getPass(0)->getFragmentProgramParameters();

	params->setNamedConstant("mix_factor",factor);
}

void ChangeWorldRenderer::renderToTextureDreams()
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
		mRenderTextureDreamsWithMiniScreen->update();
	}
}

void ChangeWorldRenderer::renderToTextureNightmares()
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
		mRenderTextureNightmaresWithMiniScreen->update();
	}
}

void ChangeWorldRenderer::renderToTextureChangeWorld()
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

void ChangeWorldRenderer::setCamera(Ogre::Camera * pCamera)
{
	mCamera=pCamera;
}

Ogre::Camera * ChangeWorldRenderer::getCamera() const
{
	return mCamera;
}


