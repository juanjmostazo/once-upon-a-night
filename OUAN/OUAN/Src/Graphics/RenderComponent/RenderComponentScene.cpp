#include "RenderComponentScene.h"
#include "ChangeWorldMaterial.h"
using namespace OUAN;

RenderComponentScene::RenderComponentScene(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_SCENE)
{
}
RenderComponentScene::~RenderComponentScene()
{
	mSceneManager=NULL;
}
Ogre::SceneManager* RenderComponentScene::getSceneManager() const
{
	return mSceneManager;
}

void RenderComponentScene::setSceneManager(Ogre::SceneManager* sceneManager)
{
	mSceneManager=sceneManager;
}

void RenderComponentScene::setSkyMaterials(TRenderComponentSceneParameters tRenderComponentSceneParameters,TChangeWorldMaterialParameters tChangeWorldMaterialParameters)
{	
	this->tRenderComponentSkyDomeParameters=tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters;
	this->tRenderComponentSkyBoxParameters=tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters;

	initChangeWorldMaterials(tChangeWorldMaterialParameters);

	setChangeWorldMaterials(NIGHTMARES);
	setChangeWorldMaterials(DREAMS);
	setOriginalMaterials(NIGHTMARES);
	setOriginalMaterials(DREAMS);

}

void RenderComponentScene::changeToWorld(int newWorld, double perc)
{
	//if(mSceneManager->isSkyBoxEnabled())
	//{
	//	mSkyBoxChangeWorldMaterialDreams->setChangeWorldFactor(perc);
	//	mSkyBoxChangeWorldMaterialNightmares->setChangeWorldFactor(perc);
	//}
	if(mSceneManager->isSkyDomeEnabled())
	{
		switch(newWorld)
		{
		case DREAMS:
			mSkyDomeChangeWorldMaterialDreams->setChangeWorldFactor(1-perc);
			mSkyDomeChangeWorldMaterialNightmares->setChangeWorldFactor(perc);
			break;
		case NIGHTMARES:
			mSkyDomeChangeWorldMaterialNightmares->setChangeWorldFactor(1-perc);
			mSkyDomeChangeWorldMaterialDreams->setChangeWorldFactor(perc);
			break;
		default:break;
		}
	}
}

void RenderComponentScene::randomizeChangeWorldMaterials()
{
	mSkyDomeChangeWorldMaterialDreams->randomize();
	mSkyDomeChangeWorldMaterialNightmares->randomize();

	//mSkyBoxChangeWorldMaterialDreams->randomize();
	//mSkyBoxChangeWorldMaterialNightmares->randomize();
}

void RenderComponentScene::setOriginalMaterials(int world)
{
	//if(mSceneManager->isSkyBoxEnabled())
	//{
	//	switch(world)
	//	{
	//	case DREAMS:
	//	//Set SkyBox
	//	mSceneManager->setSkyBox(tRenderComponentSkyBoxParameters.active,
	//		tRenderComponentSkyBoxParameters.materialDreams,
	//		tRenderComponentSkyBoxParameters.distance);

	//		break;
	//	case NIGHTMARES:
	//	//Set SkyBox
	//	mSceneManager->setSkyBox(tRenderComponentSkyBoxParameters.active,
	//		tRenderComponentSkyBoxParameters.materialNightmares,
	//		tRenderComponentSkyBoxParameters.distance);

	//		break;
	//	default:break;
	//	}
	//}
	if(mSceneManager->isSkyDomeEnabled())
	{
		switch(world)
		{
		case DREAMS:
		//Set SkyDome
		mSceneManager->setSkyDome(tRenderComponentSkyDomeParameters.active,
			tRenderComponentSkyDomeParameters.materialDreams,
			tRenderComponentSkyDomeParameters.curvature,
			tRenderComponentSkyDomeParameters.tiling,
			tRenderComponentSkyDomeParameters.distance);
			break;
		case NIGHTMARES:
		//Set SkyDome
		mSceneManager->setSkyDome(tRenderComponentSkyDomeParameters.active,
			tRenderComponentSkyDomeParameters.materialNightmares,
			tRenderComponentSkyDomeParameters.curvature,
			tRenderComponentSkyDomeParameters.tiling,
			tRenderComponentSkyDomeParameters.distance);
			break;
		default:break;
		}
	}
}
void RenderComponentScene::setChangeWorldMaterials(int world)
{
	//if(mSceneManager->isSkyBoxEnabled())
	//{
	//	switch(world)
	//	{
	//	case DREAMS:
	//	//Set SkyBox
	//	mSceneManager->setSkyBox(tRenderComponentSkyBoxParameters.active,
	//		mSkyBoxChangeWorldMaterialDreams->getMaterialName(),
	//		tRenderComponentSkyBoxParameters.distance);

	//		break;
	//	case NIGHTMARES:
	//	//Set SkyBox
	//	mSceneManager->setSkyBox(tRenderComponentSkyBoxParameters.active,
	//		mSkyBoxChangeWorldMaterialNightmares->getMaterialName(),
	//		tRenderComponentSkyBoxParameters.distance);

	//		break;
	//	default:break;
	//	}
	//}
	if(mSceneManager->isSkyDomeEnabled())
	{
		switch(world)
		{
		case DREAMS:
		//Set SkyDome
		mSceneManager->setSkyDome(tRenderComponentSkyDomeParameters.active,
			mSkyDomeChangeWorldMaterialDreams->getMaterialName(),
			tRenderComponentSkyDomeParameters.curvature,
			tRenderComponentSkyDomeParameters.tiling,
			tRenderComponentSkyDomeParameters.distance);
			break;
		case NIGHTMARES:
		//Set SkyDome
		mSceneManager->setSkyDome(tRenderComponentSkyDomeParameters.active,
			mSkyDomeChangeWorldMaterialNightmares->getMaterialName(),
			tRenderComponentSkyDomeParameters.curvature,
			tRenderComponentSkyDomeParameters.tiling,
			tRenderComponentSkyDomeParameters.distance);
			break;
		default:break;
		}
	}

	//Logger::getInstance()->log("[setChangeWorldMaterials] materials");
}
void RenderComponentScene::initChangeWorldMaterials(TChangeWorldMaterialParameters tChangeWorldMaterialParameters)
{
	//mSkyBoxChangeWorldMaterialDreams.reset(new ChangeWorldMaterial);
	//mSkyBoxChangeWorldMaterialDreams->init("skyboxdreams",type,
	//	Ogre::MaterialManager::getSingleton().getByName(tRenderComponentSkyBoxParameters.materialDreams),
	//	Ogre::MaterialManager::getSingleton().getByName(tRenderComponentSkyBoxParameters.materialNightmares));

	//mSkyBoxChangeWorldMaterialNightmares.reset(new ChangeWorldMaterial);
	//mSkyBoxChangeWorldMaterialNightmares->init("skyboxnightmares",type,
	//	Ogre::MaterialManager::getSingleton().getByName(tRenderComponentSkyBoxParameters.materialNightmares),
	//	Ogre::MaterialManager::getSingleton().getByName(tRenderComponentSkyBoxParameters.materialDreams));

	mSkyDomeChangeWorldMaterialDreams.reset(new ChangeWorldMaterial);
	mSkyDomeChangeWorldMaterialDreams->init("skydomedreams",tChangeWorldMaterialParameters,
		Ogre::MaterialManager::getSingleton().getByName(tRenderComponentSkyDomeParameters.materialDreams),
		Ogre::MaterialManager::getSingleton().getByName(tRenderComponentSkyDomeParameters.materialNightmares));

	mSkyDomeChangeWorldMaterialNightmares.reset(new ChangeWorldMaterial);
	mSkyDomeChangeWorldMaterialNightmares->init("skydomenightmares",tChangeWorldMaterialParameters,
		Ogre::MaterialManager::getSingleton().getByName(tRenderComponentSkyDomeParameters.materialNightmares),
		Ogre::MaterialManager::getSingleton().getByName(tRenderComponentSkyDomeParameters.materialDreams));

}

void RenderComponentScene::update(double elapsedSeconds)
{
	//mSkyBoxChangeWorldMaterialDreams->update(elapsedSeconds);
	//mSkyBoxChangeWorldMaterialNightmares->update(elapsedSeconds);

	mSkyDomeChangeWorldMaterialDreams->update(elapsedSeconds);
	mSkyDomeChangeWorldMaterialNightmares->update(elapsedSeconds);
}

TRenderComponentSceneParameters::TRenderComponentSceneParameters() : TRenderComponentParameters()
{
}
TRenderComponentSceneParameters::~TRenderComponentSceneParameters()
{
}

TRenderComponentSkyBoxParameters::TRenderComponentSkyBoxParameters() : TRenderComponentParameters()
{
}
TRenderComponentSkyBoxParameters::~TRenderComponentSkyBoxParameters()
{
}

TRenderComponentSkyDomeParameters::TRenderComponentSkyDomeParameters() : TRenderComponentParameters()
{
}
TRenderComponentSkyDomeParameters::~TRenderComponentSkyDomeParameters()
{
}