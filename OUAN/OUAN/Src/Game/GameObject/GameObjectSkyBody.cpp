#include "OUAN_Precompiled.h"

#include "GameObjectSkyBody.h"
#include "../GameWorldManager.h"
#include "../../Graphics/Effects/LensFlare.h"

using namespace OUAN;

GameObjectSkyBody::GameObjectSkyBody(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SKYBODY)
{

}

GameObjectSkyBody::~GameObjectSkyBody()
{
	mRenderComponentEntityDreams.reset();
	mRenderComponentEntityNightmares.reset();
	mRenderComponentGlowDreams.reset();
	mRenderComponentGlowNightmares.reset();
	mRenderComponentPositional.reset();
	mRenderComponentInitial.reset();
	mBBSComponentDreams.reset();
	mBBSComponentNightmares.reset();
	mLogicComponent.reset();
	mLightComponentDreams.reset();
	mLightComponentNightmares.reset();
	mLensFlare.reset();
}

void GameObjectSkyBody::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectSkyBody::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectSkyBody::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectSkyBody::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectSkyBody::setRenderComponentGlowDreams(RenderComponentGlowPtr pRenderComponentGlow)
{
	mRenderComponentGlowDreams=pRenderComponentGlow;
}

void GameObjectSkyBody::setRenderComponentGlowNightmares(RenderComponentGlowPtr pRenderComponentGlow)
{
	mRenderComponentGlowNightmares=pRenderComponentGlow;
}

RenderComponentGlowPtr GameObjectSkyBody::getRenderComponentGlowDreams() const
{
	return mRenderComponentGlowDreams;
}

RenderComponentGlowPtr GameObjectSkyBody::getRenderComponentGlowNightmares() const
{
	return mRenderComponentGlowNightmares;
}

void GameObjectSkyBody::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectSkyBody::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectSkyBody::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectSkyBody::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectSkyBody::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
		if (mUseEntityDreams)
		{
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentGlowDreams->setVisible(true);
		}
		else
		{
			mBBSComponentDreams->setVisible(true);
		}

		if (mUseEntityNightmares)
		{
			mRenderComponentEntityNightmares->setVisible(false);
			mRenderComponentGlowNightmares->setVisible(false);
		}
		else
		{
			mBBSComponentNightmares->setVisible(false);
		}
	}
	else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
	{
		if (mUseEntityDreams)
		{
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentGlowDreams->setVisible(true);
		}
		else
		{
			mBBSComponentDreams->setVisible(true);
		}
	}
	else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
	{
		if (mUseEntityNightmares)
		{
			mRenderComponentEntityNightmares->setVisible(false);
			mRenderComponentGlowNightmares->setVisible(false);
		}
		else
		{
			mBBSComponentNightmares->setVisible(false);
		}
	}		
}

void GameObjectSkyBody::setNightmaresRender()
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
		if (mUseEntityDreams)
		{
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentGlowDreams->setVisible(false);
		}
		else 
		{
			mBBSComponentDreams->setVisible(false);
		}
		
		if (mUseEntityNightmares)
		{
			mRenderComponentEntityNightmares->setVisible(true);
			mRenderComponentGlowNightmares->setVisible(true);
		}
		else
		{
			mBBSComponentNightmares->setVisible(true);
		}
	}
	else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
	{
		if (mUseEntityDreams)
		{
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentGlowDreams->setVisible(false);
		}
		else
		{
			mBBSComponentDreams->setVisible(false);
		}
	}
	else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
	{
		if (mUseEntityNightmares)
		{
			mRenderComponentEntityNightmares->setVisible(true);
			mRenderComponentGlowNightmares->setVisible(true);
		}
		else
		{
			mBBSComponentNightmares->setVisible(true);
		}
	}	
}

void GameObjectSkyBody::setChangeWorldRender()
{
	if (!isEnabled()) return;
}

void GameObjectSkyBody::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		setDreamsRender();
		break;
	case NIGHTMARES:
		setNightmaresRender();
		break;
	default:break;
	}
}

void GameObjectSkyBody::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:	
		break;
	default:
		break;
	}
}

void GameObjectSkyBody::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectSkyBody::reset()
{
	GameObject::reset();
}

bool GameObjectSkyBody::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectSkyBody::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectSkyBody::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectSkyBody::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectSkyBody::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectSkyBody::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectSkyBody::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectSkyBody::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

bool GameObjectSkyBody::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectSkyBody::getEntityComponent() const
{
	return (mWorld==DREAMS) ? mRenderComponentEntityDreams : mRenderComponentEntityNightmares;
}

RenderComponentBillboardSetPtr GameObjectSkyBody::getRenderComponentBillboardSetDreams() const
{
	return mBBSComponentDreams;
}

void GameObjectSkyBody::setRenderComponentBillboardSetDreams(RenderComponentBillboardSetPtr bbsDreams)
{
	mBBSComponentDreams=bbsDreams;
}

RenderComponentBillboardSetPtr GameObjectSkyBody::getRenderComponentBillboardSetNightmares() const
{
	return mBBSComponentNightmares;
}

void GameObjectSkyBody::setRenderComponentBillboardSetNightmares(RenderComponentBillboardSetPtr bbsNightmares)
{
	mBBSComponentNightmares=bbsNightmares;
}

RenderComponentLightPtr GameObjectSkyBody::getLightDreams() const
{
	return mLightComponentDreams;
}

void GameObjectSkyBody::setLightDreams(RenderComponentLightPtr lightComponent)
{
	mLightComponentDreams=lightComponent;
}

RenderComponentLightPtr GameObjectSkyBody::getLightNightmares() const
{
	return mLightComponentNightmares;
}

void GameObjectSkyBody::setLightNightmares(RenderComponentLightPtr lightComponent)
{
	mLightComponentNightmares=lightComponent;
}

bool GameObjectSkyBody::isUsingEntityDreams()
{
	return mUseEntityDreams;
}

void GameObjectSkyBody::setUseEntityDreams(bool useEntity)
{
	mUseEntityDreams=useEntity;
}

bool GameObjectSkyBody::isUsingEntityNightmares()
{
	return mUseEntityNightmares;
}

void GameObjectSkyBody::setUseEntityNightmares(bool useEntity)
{
	mUseEntityNightmares=useEntity;
}

LensFlarePtr GameObjectSkyBody::getLensFlare() const
{
	return mLensFlare;
}

void GameObjectSkyBody::setLensFlare(LensFlarePtr lensFlare)
{
	mLensFlare=lensFlare;
}

void GameObjectSkyBody::initLensFlare(Ogre::Camera* cam, Ogre::SceneManager* sceneMgr)
{
	Ogre::SceneNode* currentNode = mRenderComponentPositional->getSceneNode();
	mLensFlare.reset(new LensFlare(cam,sceneMgr,currentNode));
}

void GameObjectSkyBody::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	if (mLensFlare.get())
	{
		mLensFlare->update();
	}
}
void GameObjectSkyBody::setVisible(bool visible)
{

}
//-------------------------------------------------------------------------------------------

TGameObjectSkyBodyParameters::TGameObjectSkyBodyParameters() : TGameObjectParameters()
{

}

TGameObjectSkyBodyParameters::~TGameObjectSkyBodyParameters()
{

}