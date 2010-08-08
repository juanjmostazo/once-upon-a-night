#include "OUAN_Precompiled.h"

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
	mTransparentMaterialTextures.clear();

}

void TransparentEntity::init(Ogre::Entity * pEntity,double minAlphaBlending,double alphaBlendingSpeed)
{

	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::SubEntity* subEnt;
	Ogre::MaterialPtr material;
	Ogre::MaterialPtr clone;
	unsigned int i,j;
	std::string materialName;

	clear();

	mState=TES_SOLID;
	mCurrentAlpha=1.0f;

	mEntity=pEntity;
	mMinAlphaBlending=minAlphaBlending;
	mAlphaBlendingSpeed=alphaBlendingSpeed;

//	originalRenderQueue=mEntity->getRenderQueueGroup();

	for ( i = 0; i < mEntity->getNumSubEntities(); i++)
	{
		// Get the material of this sub entity and build the clone material name
		subEnt = mEntity->getSubEntity(i);
		material = subEnt->getMaterial();

		materialName=mEntity->getName()+"#"+material->getName()+"#TRANSPARENT";

		// Get/Create the clone material

		if (Ogre::MaterialManager::getSingleton().resourceExists(materialName))
		{
			clone = Ogre::MaterialManager::getSingleton().getByName(materialName);
		}
		else
		{
			// Clone the material
			clone = material->clone(materialName);

				//get technique
			technique = clone->getBestTechnique();
				//set current pass attributes
			for(j=0;j<technique->getNumPasses();j++)
			{
				pass = technique->getPass(j);
				if(j==0)
				{
					pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);			
					pass->setDepthWriteEnabled(false);
				}
			}
		}

		//Add material to the material stack 
		mSolidMaterial.push_back(material->getName());
		mTransparentMaterial.push_back(clone->getName());
	}
	//Logger::getInstance()->log("[TransparentEntity] INIT transparent entity "+mEntity->getName());

}

void TransparentEntity::setSolidMaterials()
{
	unsigned int i;
	Ogre::SubEntity* subEnt;

	for ( i = 0; i < mEntity->getNumSubEntities(); i++)
	{
		// Apply the material to the sub entity.
		subEnt = mEntity->getSubEntity(i);
		subEnt->setMaterial(Ogre::MaterialManager::getSingleton().getByName(mSolidMaterial[i]));
	}	
}

void TransparentEntity::setTransparentMaterials()
{
	unsigned int i;
	Ogre::SubEntity* subEnt;

	for ( i = 0; i < mEntity->getNumSubEntities(); i++)
	{
		// Apply the material to the sub entity.
		subEnt = mEntity->getSubEntity(i);
		subEnt->setMaterial(Ogre::MaterialManager::getSingleton().getByName(mTransparentMaterial[i]));
	}
}

void TransparentEntity::makeSolid()
{
	mState=TES_MAKING_SOLID;
}

void TransparentEntity::makeTransparent()
{
	mState=TES_MAKING_TRANSPARENT;
	setTransparentMaterials();
}

void TransparentEntity::setTransparentMaterialsAlpha(double alpha)
{
	unsigned int i,j;
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::MaterialPtr material;

	for ( i = 0; i < mTransparentMaterial.size(); i++)
	{
		if (Ogre::MaterialManager::getSingleton().resourceExists(mTransparentMaterial[i]))
		{
			material = Ogre::MaterialManager::getSingleton().getByName(mTransparentMaterial[i]);
				//get technique
			technique = material->getBestTechnique();
				//set current pass attributes
			for(j=0;j<technique->getNumPasses();j++)
			{
				pass = technique->getPass(j);
				Ogre::GpuProgramParametersSharedPtr params = pass->getFragmentProgramParameters();
				if (params->_findNamedConstantDefinition("alpha_modulate"))
				{
					params->setNamedConstant("alpha_modulate", Ogre::Real(alpha));
				}	
			}
		}
	}
}

void TransparentEntity::update(double elapsedTime)
{
	//Logger::getInstance()->log("[TransparentEntity] updating transparent entity "+mEntity->getName()+" elapsed time "+Ogre::StringConverter::toString(Ogre::Real(elapsedTime))+" current alpha "+Ogre::StringConverter::toString(Ogre::Real(mCurrentAlpha)));
	//Logger::getInstance()->log("[TransparentEntity] updating transparent entity "+mEntity->getName()+" mAlphaBlendingSpeed "+Ogre::StringConverter::toString(Ogre::Real(mAlphaBlendingSpeed)));

	switch(mState)
	{
	case TES_SOLID:
		//Logger::getInstance()->log("[TransparentEntity] solid");
		break;
	case TES_TRANSPARENT:
		//Logger::getInstance()->log("[TransparentEntity] transparent");
		break;
	case TES_MAKING_SOLID:
		//Logger::getInstance()->log("[TransparentEntity] making solid");
		mCurrentAlpha+=elapsedTime*mAlphaBlendingSpeed;
		if(mCurrentAlpha>=1)
		{
			mCurrentAlpha=1.0f;
			setSolidMaterials();
			mState=TES_SOLID;
		}
		else
		{
			setTransparentMaterialsAlpha(mCurrentAlpha);
		}
		break;
	case TES_MAKING_TRANSPARENT:
		//Logger::getInstance()->log("[TransparentEntity] making transparent");
		mCurrentAlpha-=elapsedTime*mAlphaBlendingSpeed;
		if(mCurrentAlpha<=mMinAlphaBlending)
		{
			mCurrentAlpha=mMinAlphaBlending;
			setTransparentMaterialsAlpha(mMinAlphaBlending);
			mState=TES_TRANSPARENT;
		}
		else
		{
			setTransparentMaterialsAlpha(mCurrentAlpha);
		}
		break;
	default:
		break;
	}
}

bool TransparentEntity::isSolid()
{
	return mState==TES_SOLID;
}

bool TransparentEntity::isTransparent()
{
	return mState==TES_TRANSPARENT;
}
