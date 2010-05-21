#include "ChangeWorldMaterial.h"
using namespace OUAN;

ChangeWorldMaterial::ChangeWorldMaterial()
{
	mName="";
	mId="";
}

ChangeWorldMaterial::~ChangeWorldMaterial()
{
}

std::string ChangeWorldMaterial::getMaterialName()
{
	return mName;
}

Ogre::MaterialPtr ChangeWorldMaterial::findMaterial(std::string name)
{
	Ogre::MaterialPtr material;
	if (Ogre::MaterialManager::getSingleton().resourceExists(name))
	{	
		material=Ogre::MaterialManager::getSingleton().getByName(name);
	}
	else
	{
		Ogre::LogManager::getSingleton().logMessage("[ChangeWorldMaterial] material "+name+" does not exist.");
	}
	return material;
}

std::string ChangeWorldMaterial::createMaterial(ChangeWorldType type, std::string diffuseTexture1, std::string diffuseTexture2)
{
	Ogre::MaterialPtr changeworld_clone;
	Ogre::MaterialPtr changeworld_material;

	std::string baseMaterialName;
	std::string newMaterialName;

	baseMaterialName=getChangeWorldTypeName(type);
	newMaterialName=mId+"#"+baseMaterialName+"#"+diffuseTexture1+"#"+diffuseTexture2;

	if (Ogre::MaterialManager::getSingleton().resourceExists(newMaterialName))
	{	
		//material already exists, no need to create it
		return newMaterialName;
	}
	else
	{
		//create the material
		
		changeworld_material=findMaterial(baseMaterialName);
		if(!changeworld_material.isNull())
		{
			changeworld_clone=changeworld_material->clone(newMaterialName);
			switch(type)
			{
			case CW_BLENDING:
				createMaterialBlending(changeworld_clone,diffuseTexture1,diffuseTexture2);
				break;
			case CW_EROSION:
				createMaterialErosion(changeworld_clone,diffuseTexture1,diffuseTexture2);
				break;
			default:
				return "";
				break;
			}
		}
		else
		{
			Ogre::LogManager::getSingleton().logMessage("[ChangeWorldMaterial] material "+baseMaterialName+" does not exist.");
			return "";
		}

	}
	return newMaterialName;
}

void ChangeWorldMaterial::createMaterialBlending(Ogre::MaterialPtr clone,std::string diffuseTexture1, std::string diffuseTexture2)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;

	technique=clone->getTechnique(0);
	pass=technique->getPass(0);
	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture1);

	pass=technique->getPass(1);
	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture2);
}

void ChangeWorldMaterial::createMaterialErosion(Ogre::MaterialPtr clone,std::string diffuseTexture1, std::string diffuseTexture2)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;

	technique=clone->getTechnique(0);
	pass=technique->getPass(0);
	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture1);

	texture=pass->getTextureUnitState(1);
	texture->setTextureName(diffuseTexture2);
}

void ChangeWorldMaterial::setChangeWorldFactor(double factor)
{
	Ogre::MaterialPtr material;
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;
	Ogre::GpuProgramParametersSharedPtr params;

	//Ogre::LogManager::getSingleton().logMessage("[ChangeWorldMaterial] setChangeWorldFactor "+mName+" "+Ogre::StringConverter::toString(Ogre::Real(factor)));

	material=findMaterial(mName);
	if(!material.isNull())
	{
		technique = material->getBestTechnique();

		switch(mType)
		{
		case CW_BLENDING:
			pass = technique->getPass(1);
			texture = pass->getTextureUnitState(0);
			texture->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, factor);
			break;
		case CW_EROSION:
			pass = technique->getPass(0);
			params = pass->getFragmentProgramParameters();
			params->setNamedConstant("Factor",Ogre::Real(factor));
			break;
		default:
			break;
		}
	}
}

bool ChangeWorldMaterial::init(std::string id,ChangeWorldType type, Ogre::MaterialPtr pMaterial1, Ogre::MaterialPtr pMaterial2)
{
	std::string diffuseTexture1;
	std::string diffuseTexture2;

	diffuseTexture1=getDiffuseTexture(pMaterial1);
	diffuseTexture2=getDiffuseTexture(pMaterial2);

	if(diffuseTexture1.compare("")!=0 && diffuseTexture2.compare("")!=0)
	{
		mId=id;
		mType = type;

		mName = createMaterial(type,
			diffuseTexture1,
			diffuseTexture2
			);

		Ogre::LogManager::getSingleton().logMessage("[ChangeWorldMaterial] material "+mName+" initialized.");
	}

	return mName.compare("")!=0;
}

std::string ChangeWorldMaterial::getChangeWorldTypeName(ChangeWorldType type)
{
	switch(type)
	{
	case CW_BLENDING:
		return MATERIAL_BLENDING_NAME;
		break;
	case CW_EROSION:
		return MATERIAL_EROSION_NAME;
		break;
	default:
		return MATERIAL_BLENDING_NAME;
		break;
	}
}

std::string ChangeWorldMaterial::getDiffuseTexture(Ogre::MaterialPtr material)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;

	// Get diffuse texture
	technique = material->getBestTechnique();
	pass = technique->getPass(0);
	if(pass->getTextureUnitStateIterator().hasMoreElements())
	{
		return pass->getTextureUnitState(0)->getTextureName();
	}
	else
	{
		return "";
	}
}