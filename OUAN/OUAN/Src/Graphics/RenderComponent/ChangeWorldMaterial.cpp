#include "ChangeWorldMaterial.h"
#include "../../Utils/Utils.h"

using namespace OUAN;

ChangeWorldMaterial::ChangeWorldMaterial()
{
	mName="";
	mId="";
	mPointOfInterest=Vector3::ZERO;
	mChangeWorldBlendingTiling=Vector3(1,1,1);
	mTiling=Vector3(1,1,1);
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
		Logger::getInstance()->log("[ChangeWorldMaterial] material "+name+" does not exist.");
	}
	return material;
}

std::string ChangeWorldMaterial::createMaterial(TChangeWorldMaterialParameters tChangeWorldMaterialParameters, Ogre::MaterialPtr original_material,std::string diffuseTexture1, std::string diffuseTexture2)
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
				createMaterialBlending(tChangeWorldMaterialParameters,original_material,changeworld_clone,diffuseTexture1,diffuseTexture2);
				break;
			case CW_EROSION:
				createMaterialErosion(tChangeWorldMaterialParameters,original_material,changeworld_clone,diffuseTexture1,diffuseTexture2);
				break;
			case CW_EROSION_TRANSPARENT:
				createMaterialErosionTransparent(tChangeWorldMaterialParameters,original_material,changeworld_clone,diffuseTexture1);
				break;
			default:
				return "";
				break;
			}
		}
		else
		{
			Logger::getInstance()->log("[ChangeWorldMaterial] material "+baseMaterialName+" does not exist.");
			return "";
		}

	}
	return newMaterialName;
}

void ChangeWorldMaterial::setPassParameters(Ogre::Pass * pass,Ogre::MaterialPtr original_material)
{
	Ogre::Technique * technique;
	Ogre::Pass * original_pass;

	technique = original_material->getBestTechnique();
	original_pass = technique->getPass(0);

	pass->setAlphaRejectFunction(original_pass->getAlphaRejectFunction());
	pass->setAlphaRejectValue(original_pass->getAlphaRejectValue());
	pass->setAmbient(original_pass->getAmbient());
	pass->setColourWriteEnabled(original_pass->getColourWriteEnabled());
	pass->setCullingMode(original_pass->getCullingMode());
	pass->setDepthBias(original_pass->getDepthBiasConstant());
	pass->setDepthCheckEnabled(original_pass->getDepthCheckEnabled());
	pass->setDepthFunction(original_pass->getDepthFunction());
	pass->setDepthWriteEnabled(original_pass->getDepthWriteEnabled());
	pass->setSceneBlending(original_pass->getSourceBlendFactor(),original_pass->getDestBlendFactor());
	pass->setDiffuse(original_pass->getDiffuse());
	pass->setLightingEnabled(original_pass->getLightingEnabled());
	pass->setPolygonMode(original_pass->getPolygonMode());
	pass->setShadingMode(original_pass->getShadingMode());
	pass->setTransparentSortingEnabled(original_pass->getTransparentSortingEnabled());
	pass->setPointAttenuation(original_pass->isPointAttenuationEnabled(),original_pass->getPointAttenuationConstant(),original_pass->getPointAttenuationLinear(),original_pass->getPointAttenuationQuadratic());

}

void ChangeWorldMaterial::createMaterialBlending(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr original_material,Ogre::MaterialPtr change_world_material_clone,std::string diffuseTexture1, std::string diffuseTexture2)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;

	technique=change_world_material_clone->getTechnique(0);
	pass=technique->getPass(0);
	setPassParameters(pass,original_material);

	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture1);

	pass=technique->getPass(1);
	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture2);
}

void ChangeWorldMaterial::createMaterialErosion(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr original_material,Ogre::MaterialPtr change_world_material_clone,std::string diffuseTexture1, std::string diffuseTexture2)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;
	Ogre::GpuProgramParametersSharedPtr params;

	technique=change_world_material_clone->getTechnique(0);
	pass=technique->getPass(0);
	setPassParameters(pass,original_material);

	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture1);

	texture=pass->getTextureUnitState(1);
	texture->setTextureName(diffuseTexture2);

	//set shader constant parameters
	params = pass->getFragmentProgramParameters();
	params->setNamedConstant("blending",Ogre::Real(tChangeWorldMaterialParameters.blending_amount));
	params->setNamedConstant("blending_tiling",mChangeWorldBlendingTiling);
	params->setNamedConstant("tiling",mTiling);

	Logger::getInstance()->log("mTiling "+mId+" "+Ogre::StringConverter::toString(mTiling));

	texture=pass->getTextureUnitState(2);
	texture->setTextureName(tChangeWorldMaterialParameters.blending_texture);
}

void ChangeWorldMaterial::createMaterialErosionTransparent(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr original_material,Ogre::MaterialPtr change_world_material_clone,std::string diffuseTexture1)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;
	Ogre::GpuProgramParametersSharedPtr params;

	technique=change_world_material_clone->getTechnique(0);
	pass=technique->getPass(0);
	setPassParameters(pass,original_material);

	pass->setAlphaRejectSettings(Ogre::CMPF_GREATER,128);
	pass->setDepthWriteEnabled(true);
	pass->setTransparentSortingEnabled(true);

	texture=pass->getTextureUnitState(0);
	texture->setTextureName(diffuseTexture1);

	//set shader constant parameters
	params = pass->getFragmentProgramParameters();
	params->setNamedConstant("blending",Ogre::Real(tChangeWorldMaterialParameters.blending_amount));
	params->setNamedConstant("blending_tiling",mChangeWorldBlendingTiling);
	params->setNamedConstant("tiling",mTiling);

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

	Logger::getInstance()->log("[ChangeWorldMaterial] setChangeWorldFactor "+mName+" "+Ogre::StringConverter::toString(Ogre::Real(factor)));

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
	Logger::getInstance()->log("[ChangeWorldMaterial] setChangeWorldFactor "+mName+" DONE");

}

void ChangeWorldMaterial::getMaterialParameters(TChangeWorldMaterialParameters tChangeWorldMaterialParameters,Ogre::MaterialPtr material)
{
	mType = tChangeWorldMaterialParameters.type;
	mRandomize=tChangeWorldMaterialParameters.randomize;

	mScrollAnimationSpeed=tChangeWorldMaterialParameters.scroll_animation;
	mScrollBlendingSpeed=tChangeWorldMaterialParameters.scroll_blending;
    mChangeWorldBlendingTiling=Vector3(tChangeWorldMaterialParameters.tiling,tChangeWorldMaterialParameters.tiling,tChangeWorldMaterialParameters.tiling);

	getTextureParameters(material);
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
		getMaterialParameters(tChangeWorldMaterialParameters,pMaterial1);

		mName = createMaterial(tChangeWorldMaterialParameters,
			pMaterial1,
			diffuseTexture1,
			diffuseTexture2
			);

		Logger::getInstance()->log("[ChangeWorldMaterial] material "+mName+" initialized.");
	}

	return mName.compare("")!=0;
}

bool ChangeWorldMaterial::init(std::string id,TChangeWorldMaterialParameters tChangeWorldMaterialParameters, Ogre::MaterialPtr pMaterial1)
{
	std::string diffuseTexture1;

	diffuseTexture1=getDiffuseTexture(pMaterial1);

	if(diffuseTexture1.compare("")!=0)
	{
		mId=id;
		tChangeWorldMaterialParameters.type=CW_EROSION_TRANSPARENT;
		getMaterialParameters(tChangeWorldMaterialParameters,pMaterial1);

		mName = createMaterial(tChangeWorldMaterialParameters,
			pMaterial1,
			diffuseTexture1,
			diffuseTexture1
			);

		Logger::getInstance()->log("[ChangeWorldMaterial] material "+mName+" initialized.");
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
	if(!material.isNull() && mRandomize)
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
				2*Utils::Random::getInstance()->getRandomDouble()-1,
				2*Utils::Random::getInstance()->getRandomDouble()-1,
				Utils::Random::getInstance()->getRandomDouble()*Ogre::Math::TWO_PI)
				);
			break;
		case CW_EROSION_TRANSPARENT:
			pass = technique->getPass(0);
			params = pass->getFragmentProgramParameters();
			params->setNamedConstant("displacement",Vector3(
				2*Utils::Random::getInstance()->getRandomDouble()-1,
				2*Utils::Random::getInstance()->getRandomDouble()-1,
				Utils::Random::getInstance()->getRandomDouble()*Ogre::Math::TWO_PI)
				);
			break;
		default:
			break;
		}
	}
}

void ChangeWorldMaterial::getTextureParameters(Ogre::MaterialPtr material)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;

	// Get diffuse texture
	technique = material->getBestTechnique();
	pass = technique->getPass(0);
	if(pass->getTextureUnitStateIterator().hasMoreElements())
	{
		if(mScrollAnimationSpeed==Vector3::ZERO)
		{
			//mScrollAnimationSpeed.x=pass->getTextureUnitState(0)->getTextureUScroll();
			//mScrollAnimationSpeed.y=pass->getTextureUnitState(0)->getTextureVScroll();
		}
		mTiling=Vector3(1.0f/pass->getTextureUnitState(0)->getTextureUScale(),1.0f/pass->getTextureUnitState(0)->getTextureVScale(),0.0f);
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
	if(mScrollAnimationCurrent.z<=0) mScrollAnimationCurrent.z+=Ogre::Math::TWO_PI;

	mScrollBlendingCurrent-=mScrollBlendingSpeed*elapsedSeconds;
	if(mScrollBlendingCurrent.x<=0) mScrollBlendingCurrent.x+=1;
	if(mScrollBlendingCurrent.y<=0) mScrollBlendingCurrent.y+=1;
	if(mScrollBlendingCurrent.z<=0) mScrollBlendingCurrent.z+=Ogre::Math::TWO_PI;

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
			//params = pass->getVertexProgramParameters();
			//params->setNamedConstant("point_of_interest",Vector4(mPointOfInterest.x,mPointOfInterest.y,mPointOfInterest.z,0.0f));
			params = pass->getFragmentProgramParameters();
			params->setNamedConstant("scroll_animation",mScrollAnimationCurrent);
			params->setNamedConstant("scroll_blending",mScrollBlendingCurrent);
			break;
		case CW_EROSION_TRANSPARENT:
			pass = technique->getPass(0);
			//params = pass->getVertexProgramParameters();
			//params->setNamedConstant("point_of_interest",Vector4(mPointOfInterest.x,mPointOfInterest.y,mPointOfInterest.z,0.0f));
			params = pass->getFragmentProgramParameters();
			params->setNamedConstant("scroll_animation",mScrollAnimationCurrent);
			params->setNamedConstant("scroll_blending",mScrollBlendingCurrent);
			break;
		default:
			break;
		}
	}
}


void ChangeWorldMaterial::setPointOfInterest(Vector3 pointOfInterest)
{
	mPointOfInterest=pointOfInterest;
}

TChangeWorldMaterialParameters::TChangeWorldMaterialParameters()
{

}

TChangeWorldMaterialParameters::~TChangeWorldMaterialParameters()
{

}