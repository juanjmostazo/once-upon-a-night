#include "RenderComponentScene.h"
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

void RenderComponentScene::setSkyMaterials(TRenderComponentSceneParameters tRenderComponentSceneParameters)
{	
	this->tRenderComponentSkyDomeParameters=tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters;
	this->tRenderComponentSkyBoxParameters=tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters;
}

void RenderComponentScene::changeToWorld(int world, double perc)
{
	if(mSceneManager->isSkyBoxEnabled())
	{
		switch(world)
		{
		case DREAMS:
		//Set SkyBox
		mSceneManager->setSkyBox(tRenderComponentSkyBoxParameters.active,
			tRenderComponentSkyBoxParameters.materialDreams,
			tRenderComponentSkyBoxParameters.distance);

			break;
		case NIGHTMARES:
		//Set SkyBox
		mSceneManager->setSkyBox(tRenderComponentSkyBoxParameters.active,
			tRenderComponentSkyBoxParameters.materialNightmares,
			tRenderComponentSkyBoxParameters.distance);

			break;
		default:break;
		}
	}
	else if(mSceneManager->isSkyDomeEnabled())
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