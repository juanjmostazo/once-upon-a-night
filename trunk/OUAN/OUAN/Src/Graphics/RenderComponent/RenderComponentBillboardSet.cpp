#include "OUAN_Precompiled.h"

#include "RenderComponentBillboardSet.h"
#include "RenderComponentPositional.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/WorldNameConverter.h"
using namespace OUAN;

RenderComponentBillboardSet::RenderComponentBillboardSet(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_BILLBOARD_SET)
{

}

RenderComponentBillboardSet::~RenderComponentBillboardSet()
{
	mBillboardSet=NULL;
}

Ogre::BillboardSet* RenderComponentBillboardSet::getBillboardSet() const
{
	return mBillboardSet;
}

void RenderComponentBillboardSet::setBillboardSet(Ogre::BillboardSet* billboardSet)
{
	mBillboardSet=billboardSet;

	if(mBillboardSet)
	{
		mDreamsMaterial=WorldNameConverter::getDreamsName(mBillboardSet->getMaterialName());
		mNightmaresMaterial=WorldNameConverter::getNightmaresName(mBillboardSet->getMaterialName());
		mChangeWorldMaterial=WorldNameConverter::getChangeWorldName(mBillboardSet->getMaterialName());
	}
}

void RenderComponentBillboardSet::setMaterial(std::string material)
{

	Ogre::MaterialPtr original_material;

	if (Ogre::MaterialManager::getSingleton().resourceExists(material))
	{
		mBillboardSet->setMaterialName(material);
	}
	else
	{
		Logger::getInstance()->log("[RenderComponentBillboardSet] material "+material+" does not exist.");
	}
}

void RenderComponentBillboardSet::setChangeWorldMaterials()
{
	setMaterial(mChangeWorldMaterial);
}

void RenderComponentBillboardSet::setDreamsMaterials()
{
	setMaterial(mDreamsMaterial);
}

void RenderComponentBillboardSet::setNightmaresMaterials()
{
	setMaterial(mNightmaresMaterial);
}

void RenderComponentBillboardSet::setVisible(bool visible)
{
	Ogre::SceneNode * pSceneNode;
	pSceneNode=getParent()->getPositionalComponent()->getSceneNode();

	if(visible)
	{
		if(!mBillboardSet->isAttached())
		{
			pSceneNode->attachObject(mBillboardSet);
		}
	}
	else
	{
		if(mBillboardSet->isAttached() && mBillboardSet->getParentSceneNode()->getName().compare(pSceneNode->getName())==0)
		{
			pSceneNode->detachObject(mBillboardSet->getName());
		}
	}
}

void RenderComponentBillboardSet::setChangeWorldFactor(double factor)
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



TRenderComponentBillboardSetParameters::TRenderComponentBillboardSetParameters() : TRenderComponentParameters()
{
}
TRenderComponentBillboardSetParameters::~TRenderComponentBillboardSetParameters()
{
}

TRenderComponentBillboardParameters::TRenderComponentBillboardParameters() : TRenderComponentParameters()
{
}
TRenderComponentBillboardParameters::~TRenderComponentBillboardParameters()
{
}

