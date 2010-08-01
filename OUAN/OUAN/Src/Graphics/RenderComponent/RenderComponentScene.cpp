#include "OUAN_Precompiled.h"

#include "RenderComponentScene.h"
#include "../../Game/WorldNameConverter.h"

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
	tRenderComponentSkyDomeParameters=tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters;

	mDreamsMaterial=tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.materialDreams;
	mNightmaresMaterial=tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.materialNightmares;
	mChangeWorldMaterial=WorldNameConverter::getChangeWorldName(mDreamsMaterial);
}

void RenderComponentScene::setMaterial(std::string material)
{
	mSceneManager->setSkyDome(tRenderComponentSkyDomeParameters.active,
		material,
		tRenderComponentSkyDomeParameters.curvature,
		tRenderComponentSkyDomeParameters.tiling,
		tRenderComponentSkyDomeParameters.distance);
}

void RenderComponentScene::setChangeWorldFactor(double factor)
{
	Ogre::Technique * technique;
	Ogre::GpuProgramParametersSharedPtr params;
	Ogre::Pass * pass;

	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(mChangeWorldMaterial);

	if(material.get())
	{
		technique= material->getTechnique(0);
		if(technique)
		{
			if(technique->getNumPasses()>0)
			{
				pass=technique->getPass(0);
				if(pass->hasFragmentProgram())
				{
					params=pass->getFragmentProgramParameters();

					if(params.get())
					{
						params->setNamedConstant("mix_factor",Ogre::Real(factor));
					}
				}
			}
		}
	}
}


void RenderComponentScene::setChangeWorldMaterials()
{
	setMaterial(mChangeWorldMaterial);
}

void RenderComponentScene::setDreamsMaterials()
{
	setMaterial(mDreamsMaterial);
}

void RenderComponentScene::setNightmaresMaterials()
{
	setMaterial(mNightmaresMaterial);
}

TRenderComponentSceneParameters::TRenderComponentSceneParameters() : TRenderComponentParameters()
{
}
TRenderComponentSceneParameters::~TRenderComponentSceneParameters()
{
}

TRenderComponentSkyDomeParameters::TRenderComponentSkyDomeParameters() : TRenderComponentParameters()
{
}
TRenderComponentSkyDomeParameters::~TRenderComponentSkyDomeParameters()
{
}

TRenderComponentFogParameters::TRenderComponentFogParameters() : TRenderComponentParameters()
{
}
TRenderComponentFogParameters::~TRenderComponentFogParameters()
{
}