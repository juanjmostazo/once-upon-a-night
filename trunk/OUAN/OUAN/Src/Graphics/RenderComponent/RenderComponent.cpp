#include "OUAN_Precompiled.h"

#include "RenderComponent.h"
using namespace OUAN;

RenderComponent::RenderComponent(const std::string& type)
:Component(COMPONENT_TYPE_RENDER)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::update(long elapsedTime)
{
}

std::string RenderComponent::setChangeWorldMaterialTransparentTextures(std::string changeWorldMaterial,bool existInDreams,bool existInNightmares)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::TextureUnitState * texture;
	Ogre::MaterialPtr material;

	if(!existInDreams)
	{
		std::string dreams_material=changeWorldMaterial+"_transparent_d";
		if(Ogre::MaterialManager::getSingleton().resourceExists(dreams_material))
		{
			material=Ogre::MaterialManager::getSingleton().getByName(dreams_material);
		}
		else
		{
			material=Ogre::MaterialManager::getSingleton().getByName(changeWorldMaterial);
		
			if(material.get())
			{
				material=material->clone(dreams_material);
				technique= material->getTechnique(0);
				if(technique)
				{
					if(technique->getNumPasses()>0)
					{
						pass=technique->getPass(0);
						pass->setAlphaRejectFunction(Ogre::CMPF_GREATER);
						pass->setAlphaRejectValue(128);

						texture=pass->getTextureUnitState("dreams");
						if(texture)
						{
							texture->setTextureName(TRANSPARENT_TEXTURE);
						}		
					}
				}
			}
		}
		return dreams_material;
	}
	else if(!existInNightmares)
	{
		std::string nightmares_name=changeWorldMaterial+"_transparent_n";
		if(Ogre::MaterialManager::getSingleton().resourceExists(nightmares_name))
		{
			material=Ogre::MaterialManager::getSingleton().getByName(nightmares_name);
		}
		else
		{
			material=Ogre::MaterialManager::getSingleton().getByName(changeWorldMaterial);
		
			if(material.get())
			{
				material=material->clone(nightmares_name);
				technique= material->getTechnique(0);
				if(technique)
				{
					if(technique->getNumPasses()>0)
					{
						pass=technique->getPass(0);
						pass->setAlphaRejectFunction(Ogre::CMPF_GREATER);
						pass->setAlphaRejectValue(128);

						texture=pass->getTextureUnitState("nightmares");
						if(texture)
						{
							texture->setTextureName(TRANSPARENT_TEXTURE);
						}		
					}
				}
			}
		}
		return nightmares_name;
	}
	else
	{
		return changeWorldMaterial;
	}
}

TRenderComponentParameters::TRenderComponentParameters() : TComponentParameters()
{
}

TRenderComponentParameters::~TRenderComponentParameters()
{
}