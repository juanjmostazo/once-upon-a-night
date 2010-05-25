#include "RenderComponentBillboardSet.h"
#include "ChangeWorldMaterial.h"
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
		Ogre::LogManager::getSingleton().logMessage("[RenderComponentBillboardSet] material "+material+" does not exist.");
	}

	mOriginalMaterial=material;
}

void RenderComponentBillboardSet::setOriginalMaterials()
{
	if (Ogre::MaterialManager::getSingleton().resourceExists(mOriginalMaterial))
	{
		mBillboardSet->setMaterialName(mOriginalMaterial);
	}
	else
	{
		Ogre::LogManager::getSingleton().logMessage("[RenderComponentBillboardSet] material "+mOriginalMaterial+" does not exist.");
	}
}

void RenderComponentBillboardSet::setChangeWorldMaterials()
{
	//if(!mChangeWorldMaterial.isNull())
	//{
		if (Ogre::MaterialManager::getSingleton().resourceExists(mChangeWorldMaterial->getMaterialName()))
		{
			mBillboardSet->setMaterialName(mChangeWorldMaterial->getMaterialName());
		}
		else
		{
			Ogre::LogManager::getSingleton().logMessage("[RenderComponentBillboardSet] material "+mChangeWorldMaterial->getMaterialName()+" does not exist.");
		}
	//}
}

void RenderComponentBillboardSet::initChangeWorldMaterials(TChangeWorldMaterialParameters tChangeWorldMaterialParameters)
{

	ChangeWorldMaterialPtr pChangeWorldMaterial;

	bool materialCreated;


	pChangeWorldMaterial.reset(new ChangeWorldMaterial());

	materialCreated=pChangeWorldMaterial->init(mBillboardSet->getName(),tChangeWorldMaterialParameters,
		mBillboardSet->getMaterial(),
		mBillboardSet->getMaterial());

	if(materialCreated)
	{
		mBillboardSet->setMaterialName(pChangeWorldMaterial->getMaterialName());
		mChangeWorldMaterial=pChangeWorldMaterial;
	}
	//else
	//{
	//	mChangeWorldMaterials.push_back(mEntity->getSubEntity(i)->getMaterial()->getName());
	//}


	//for ( ; i < mEntity->getNumSubEntities(); i++)
	//{
	//	mChangeWorldMaterials.push_back(mEntity->getSubEntity(i)->getMaterial()->getName());
	//}

	//setChangeWorldMaterials();
}

void RenderComponentBillboardSet::setChangeWorldFactor(double factor)
{
	mChangeWorldMaterial->setChangeWorldFactor(factor);
}

void RenderComponentBillboardSet::setChangeWorldMaterialsPointOfInterest(Vector3 pointOfInterest)
{
	mChangeWorldMaterial->setPointOfInterest(pointOfInterest);
}

void RenderComponentBillboardSet::randomizeChangeWorldMaterials()
{
	mChangeWorldMaterial->randomize();
}

void RenderComponentBillboardSet::update(double elapsedTime)
{
	mChangeWorldMaterial->update(elapsedTime);
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

