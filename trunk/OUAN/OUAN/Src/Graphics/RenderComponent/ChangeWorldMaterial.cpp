#include "ChangeWorldMaterial.h"
#include "../../Utils/Utils.h"

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

std::string ChangeWorldMaterial::createMaterial(TChangeWorldMaterialParameters tChangeWorldMaterialParameters, std::string diffuseTexture1, std::string diffuseTexture2,TPassParameters passParameters)
{
	Ogre::MaterialPtr changeworld_clone;
	Ogre::MaterialPtr changeworld_material;

	std::string baseMaterialName;
	std::string newMaterialName;

	baseMaterialName=getChangeWorldTypeName(tChangeWorldMaterialParameters.type);
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
			switch(tChangeWorldMaterialParameters.type)
			{
			case CW_BLENDING:
				createMaterialBlending(tChangeWorldMaterialParameters,changeworld_clone,diffuseTexture1,diffuseTexture2,passParameters);
				break;
			case CW_EROSION:
				createMaterialErosion(tChangeWorldMaterialParameters,changeworld_clone,diffuseTexture1,diffuseTexture2,passParameters);
				break;
			case CW_EROSION_TRANSPARENT:
				createMaterialErosionTransparent(tChangeWorldMaterialParameters,changeworld_clone,diffuseTexture1,passParameters);
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

void ChangeWorldMaterial::setTPassParameters(Ogre::Pass * pass,TPassParameters passParameters)
{
	pass->setLightingEnabled(passParameters.lighting);
	pass->setDepthWriteEnabled(passParameters.depth_write);
}

void ChangeWorldMaterial::createMaterialBlending(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr clone,std::string diffuseTexture1, std::string diffuseTexture2,TPassParameters passParameters)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;

	technique=clone->getTechnique(0);
	pass=technique->getPass(0);
	setTPassParameters(pass,passParameters);

	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture1);

	pass=technique->getPass(1);
	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture2);
}

void ChangeWorldMaterial::createMaterialErosion(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr clone,std::string diffuseTexture1, std::string diffuseTexture2,TPassParameters passParameters)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;
	Ogre::GpuProgramParametersSharedPtr params;

	technique=clone->getTechnique(0);
	pass=technique->getPass(0);
	setTPassParameters(pass,passParameters);

	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture1);

	texture=pass->getTextureUnitState(1);
	texture->setTextureName(diffuseTexture2);

	//set shader constant parameters
	params = pass->getFragmentProgramParameters();
	params->setNamedConstant("blending",Ogre::Real(tChangeWorldMaterialParameters.blending_amount));
	params->setNamedConstant("tiling",Ogre::Real(tChangeWorldMaterialParameters.tiling));

	texture=pass->getTextureUnitState(2);
	texture->setTextureName(tChangeWorldMaterialParameters.blending_texture);
}

void ChangeWorldMaterial::createMaterialErosionTransparent(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr clone,std::string diffuseTexture1,TPassParameters passParameters)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;
	Ogre::GpuProgramParametersSharedPtr params;

	technique=clone->getTechnique(0);
	pass=technique->getPass(0);
	setTPassParameters(pass,passParameters);

	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture1);

	//set shader constant parameters
	params = pass->getFragmentProgramParameters();
	params->setNamedConstant("blending",Ogre::Real(tChangeWorldMaterialParameters.blending_amount));
	params->setNamedConstant("tiling",Ogre::Real(tChangeWorldMaterialParameters.tiling));

	texture=pass->getTextureUnitState(2);
	texture->setTextureName(tChangeWorldMaterialParameters.blending_texture);
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
			params->setNamedConstant("mix_factor",Ogre::Real(factor));
			break;
		case CW_EROSION_TRANSPARENT:
			pass = technique->getPass(0);
			params = pass->getFragmentProgramParameters();
			params->setNamedConstant("mix_factor",Ogre::Real(factor));
			break;
		default:
			break;
		}
	}
	//Ogre::LogManager::getSingleton().logMessage("[ChangeWorldMaterial] setChangeWorldFactor "+mName+" DONE");

}

bool ChangeWorldMaterial::init(std::string id,TChangeWorldMaterialParameters tChangeWorldMaterialParameters, Ogre::MaterialPtr pMaterial1, Ogre::MaterialPtr pMaterial2)
{
	std::string diffuseTexture1;
	std::string diffuseTexture2;

	diffuseTexture1=getDiffuseTexture(pMaterial1);
	diffuseTexture2=getDiffuseTexture(pMaterial2);

	if(diffuseTexture1.compare("")!=0 && diffuseTexture2.compare("")!=0)
	{
		mId=id;
		mType = tChangeWorldMaterialParameters.type;

		mScrollAnimationSpeed=tChangeWorldMaterialParameters.scroll_animation;
		mScrollBlendingSpeed=tChangeWorldMaterialParameters.scroll_blending;
		mScrollAnimationCurrent=getCurrentScrollAnimation(pMaterial1);
		mScrollBlendingCurrent=getCurrentScrollAnimation(pMaterial1);

		mName = createMaterial(tChangeWorldMaterialParameters,
			diffuseTexture1,
			diffuseTexture2,
			getPassParameters(pMaterial1)
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
	case CW_EROSION_TRANSPARENT:
		return MATERIAL_EROSION_TRANSPARENT_NAME;
		break;
	default:
		return MATERIAL_BLENDING_NAME;
		break;
	}
}

void ChangeWorldMaterial::randomize()
{
	Ogre::MaterialPtr material;
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	//Ogre::TextureUnitState * texture;
	Ogre::GpuProgramParametersSharedPtr params;

	material=findMaterial(mName);
	if(!material.isNull())
	{
		technique = material->getBestTechnique();

		switch(mType)
		{
		case CW_BLENDING:
			break;
		case CW_EROSION:
			pass = technique->getPass(0);
			params = pass->getFragmentProgramParameters();
			params->setNamedConstant("displacement",Vector3(
				Utils::Random::getInstance()->getRandomDouble(),
				Utils::Random::getInstance()->getRandomDouble(),
				0.0f)
				);
			break;
		case CW_EROSION_TRANSPARENT:
			pass = technique->getPass(0);
			params = pass->getFragmentProgramParameters();
			params->setNamedConstant("displacement",Vector3(
				Utils::Random::getInstance()->getRandomDouble(),
				Utils::Random::getInstance()->getRandomDouble(),
				0.0f)
				);
			break;
		default:
			break;
		}
	}
}

Vector3 ChangeWorldMaterial::getCurrentScrollAnimation(Ogre::MaterialPtr material)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;

	// Get diffuse texture
	technique = material->getBestTechnique();
	pass = technique->getPass(0);
	if(pass->getTextureUnitStateIterator().hasMoreElements())
	{
		return Vector3(pass->getTextureUnitState(0)->getTextureUScroll(),
					   pass->getTextureUnitState(0)->getTextureVScroll(),
					   0);
	}
	else
	{
		return Vector3::ZERO;
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

TPassParameters ChangeWorldMaterial::getPassParameters(Ogre::MaterialPtr material)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	TPassParameters passParameters;
	// Get diffuse texture
	technique = material->getBestTechnique();
	pass = technique->getPass(0);
	passParameters.lighting = pass->getLightingEnabled();
	passParameters.depth_write = pass->getDepthWriteEnabled();

	return passParameters;
}

void ChangeWorldMaterial::update(double elapsedSeconds)
{
	Ogre::MaterialPtr material;
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	//Ogre::TextureUnitState * texture;
	Ogre::GpuProgramParametersSharedPtr params;

	mScrollAnimationCurrent-=mScrollAnimationSpeed*elapsedSeconds;
	if(mScrollAnimationCurrent.x<=0) mScrollAnimationCurrent.x+=1;
	if(mScrollAnimationCurrent.y<=0) mScrollAnimationCurrent.y+=1;
	if(mScrollAnimationCurrent.z<=0) mScrollAnimationCurrent.z+=1;

	mScrollBlendingCurrent-=mScrollBlendingSpeed*elapsedSeconds;
	if(mScrollBlendingCurrent.x<=0) mScrollBlendingCurrent.x+=1;
	if(mScrollBlendingCurrent.y<=0) mScrollBlendingCurrent.y+=1;
	if(mScrollBlendingCurrent.z<=0) mScrollBlendingCurrent.z+=1;

	material=findMaterial(mName);
	if(!material.isNull())
	{
		technique = material->getBestTechnique();

		switch(mType)
		{
		case CW_BLENDING:
			break;
		case CW_EROSION:
			pass = technique->getPass(0);
			params = pass->getFragmentProgramParameters();
			params->setNamedConstant("scroll_animation",mScrollAnimationCurrent);
			params->setNamedConstant("scroll_blending",mScrollBlendingCurrent);
			break;
		case CW_EROSION_TRANSPARENT:
			pass = technique->getPass(0);
			params = pass->getFragmentProgramParameters();
			params->setNamedConstant("scroll_animation",mScrollAnimationCurrent);
			params->setNamedConstant("scroll_blending",mScrollBlendingCurrent);
			break;
		default:
			break;
		}
	}
}

TPassParameters::TPassParameters()
{

}

TPassParameters::~TPassParameters()
{

}

TChangeWorldMaterialParameters::TChangeWorldMaterialParameters()
{

}

TChangeWorldMaterialParameters::~TChangeWorldMaterialParameters()
{

}