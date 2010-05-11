#include "TransparentEntity.h"

using namespace OUAN;
using namespace Ogre;

TransparentEntity::TransparentEntity()
{
	clear();
}

TransparentEntity::~TransparentEntity()
{
}

std::string TransparentEntity::getName()
{
	return mEntity->getName();
}

void TransparentEntity::clear()
{
	mEntity=NULL;
	mSolidMaterial.clear();
	mTransparentMaterial.clear();

	mMakingTransparent=false;
	mMakingSolid=false;

	mIsSolid=true;
	mCurrentElapsedTime=0;
}

void TransparentEntity::init(Ogre::Entity * pEntity,double minAlphaBlending,double alphaBlendingTime)
{
	unsigned int i;
	std::string materialName;

	clear();
	
	mEntity=pEntity;
	mMinAlphaBlending=minAlphaBlending;
	mAlphaBlendingTime=alphaBlendingTime;

	for ( i = 0; i < mEntity->getNumSubEntities(); ++i)
	{
		// Get the material of this sub entity and build the clone material name
		Ogre::SubEntity* subEnt = mEntity->getSubEntity(i);
		Ogre::MaterialPtr material = subEnt->getMaterial();

		materialName=mEntity->getName()+"#"+material->getName()+"#TRANSPARENT";

		// Get/Create the clone material
		Ogre::MaterialPtr clone;
		if (Ogre::MaterialManager::getSingleton().resourceExists(materialName))
		{
			clone = Ogre::MaterialManager::getSingleton().getByName(materialName);
		}
		else
		{
			// Clone the material
			clone = material->clone(materialName);
		}

		//Add material to the material stack 
		mSolidMaterial.push_back(material);
		mTransparentMaterial.push_back(clone);
	}
}

void TransparentEntity::setSolidMaterials()
{
	unsigned int i;

	mIsSolid=true;

	for ( i = 0; i < mEntity->getNumSubEntities(); ++i)
	{
		// Apply the material to the sub entity.
		Ogre::SubEntity* subEnt = mEntity->getSubEntity(i);
		subEnt->setMaterial(mSolidMaterial[i]);
	}
}

void TransparentEntity::setTransparentMaterials()
{
	unsigned int i;

	mIsSolid=true;

	for ( i = 0; i < mEntity->getNumSubEntities(); ++i)
	{
		// Apply the material to the sub entity.
		Ogre::SubEntity* subEnt = mEntity->getSubEntity(i);
		subEnt->setMaterial(mTransparentMaterial[i]);
	}
}

void TransparentEntity::makeSolid()
{
	mMakingTransparent=false;
	mMakingSolid=true;
}

void TransparentEntity::makeTransparent()
{
	mMakingTransparent=true;
	mMakingSolid=false;
	setTransparentMaterials();
}

void TransparentEntity::setTransparentMaterialsAlpha(double alpha)
{
	Ogre::MaterialPtr material;

	unsigned int i;

	for(i=0;i<mTransparentMaterial.size();i++)
	{
		// Get the material
		material=mTransparentMaterial[i];

		// Make it translucid
		Ogre::Technique * technique;
		Ogre::Pass * pass;
		Ogre::TextureUnitState * texture;
			//get technique
		technique = material->getBestTechnique();
			//set current pass attributes
		pass = technique->getPass(0);
		pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);			
		pass->setDepthCheckEnabled(false);
		texture=pass->getTextureUnitState(0);
		texture->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, alpha);
	}
}

void TransparentEntity::update(double elapsedTime)
{
	double alpha;
	mCurrentElapsedTime+=elapsedTime;

	if(mCurrentElapsedTime>=mAlphaBlendingTime)
	{
		mCurrentElapsedTime=mAlphaBlendingTime;
		mMakingTransparent=false;
		mMakingSolid=false;

		if(mMakingSolid)
		{
			setSolidMaterials();
		}
	}

	if(mMakingTransparent)
	{
		alpha=1.0f-(1.0f-mMinAlphaBlending)*mCurrentElapsedTime/mAlphaBlendingTime;
		setTransparentMaterialsAlpha(alpha);
	}

	if(mMakingSolid)
	{
		alpha=mMinAlphaBlending+(1.0f-mMinAlphaBlending)*mCurrentElapsedTime/mAlphaBlendingTime;
		setTransparentMaterialsAlpha(alpha);
	}
}

bool TransparentEntity::isSolid()
{
	return mIsSolid;
}

bool TransparentEntity::isTransparent()
{
	return !mIsSolid;
}
