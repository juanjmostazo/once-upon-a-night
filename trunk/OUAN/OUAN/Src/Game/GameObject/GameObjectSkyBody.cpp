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

void GameObjectSkyBody::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			if (mUseEntityDreams)
				mRenderComponentEntityDreams->setVisible(true);
			else
				mBBSComponentDreams->setVisible(true);

			if (mUseEntityNightmares)
				mRenderComponentEntityNightmares->setVisible(false);
			else
				mBBSComponentNightmares->setVisible(false);
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if (mUseEntityDreams)
				mRenderComponentEntityDreams->setVisible(true);
			else
				mBBSComponentDreams->setVisible(true);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			if (mUseEntityNightmares)
				mRenderComponentEntityNightmares->setVisible(false);
			else
				mBBSComponentNightmares->setVisible(false);
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			if (mUseEntityDreams)
				mRenderComponentEntityDreams->setVisible(false);
			else 
				mBBSComponentDreams->setVisible(false);
			
			if (mUseEntityNightmares)
				mRenderComponentEntityNightmares->setVisible(true);
			else mBBSComponentNightmares->setVisible(true);
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if (mUseEntityDreams)
				mRenderComponentEntityDreams->setVisible(false);
			else mBBSComponentDreams->setVisible(false);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			if (mUseEntityNightmares)
				mRenderComponentEntityNightmares->setVisible(true);
			else mBBSComponentNightmares->setVisible(true);
		}	
		break;
	default:break;
	}
}

void GameObjectSkyBody::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	if(mLogicComponent->existsInDreams())
	{
		if (mUseEntityDreams)
			mRenderComponentEntityDreams->randomizeChangeWorldMaterials();
		else mBBSComponentDreams->randomizeChangeWorldMaterials();
	}

	if(mLogicComponent->existsInNightmares())
	{
		if (mUseEntityNightmares)
			mRenderComponentEntityNightmares->randomizeChangeWorldMaterials();
		else mBBSComponentNightmares->randomizeChangeWorldMaterials();
	}

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if (mUseEntityDreams)
				mRenderComponentEntityDreams->setVisible(true);
			else mBBSComponentDreams->setVisible(true);
		}
		break;
	case NIGHTMARES:
		if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			if (mUseEntityNightmares)
				mRenderComponentEntityNightmares->setVisible(true);
			else mBBSComponentNightmares->setVisible(true);
		}	
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
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			if (mUseEntityDreams)
				mRenderComponentEntityDreams->setChangeWorldFactor(1-perc);
			else
				mBBSComponentDreams->setChangeWorldFactor(1-perc);
			if (mUseEntityNightmares)
				mRenderComponentEntityNightmares->setChangeWorldFactor(perc);
			else 
				mBBSComponentNightmares->setChangeWorldFactor(perc);
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if (mUseEntityDreams)
				mRenderComponentEntityDreams->setChangeWorldFactor(1-perc);
			else
				mBBSComponentDreams->setChangeWorldFactor(1-perc);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			if (mUseEntityNightmares)
				mRenderComponentEntityNightmares->setChangeWorldFactor(perc);
			else
				mBBSComponentNightmares->setChangeWorldFactor(perc);
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			if (mUseEntityDreams)
				mRenderComponentEntityDreams->setChangeWorldFactor(perc);
			else
				mBBSComponentDreams->setChangeWorldFactor(perc);
			if (mUseEntityNightmares)
				mRenderComponentEntityNightmares->setChangeWorldFactor(1-perc);
			else 
				mBBSComponentNightmares->setChangeWorldFactor(1-perc);
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if (mUseEntityDreams)
				mRenderComponentEntityDreams->setChangeWorldFactor(perc);
			else
				mBBSComponentDreams->setChangeWorldFactor(perc);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			if (mUseEntityNightmares)
				mRenderComponentEntityNightmares->setChangeWorldFactor(1-perc);
			else
				mBBSComponentNightmares->setChangeWorldFactor(1-perc);
		}		
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

void GameObjectSkyBody::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
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
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
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
//-------------------------------------------------------------------------------------------

TGameObjectSkyBodyParameters::TGameObjectSkyBodyParameters() : TGameObjectParameters()
{

}

TGameObjectSkyBodyParameters::~TGameObjectSkyBodyParameters()
{

}