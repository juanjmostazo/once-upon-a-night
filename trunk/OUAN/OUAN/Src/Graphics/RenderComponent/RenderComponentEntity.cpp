#include "OUAN_Precompiled.h"

#include "RenderComponentEntity.h"
#include "../RenderSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameWorldManager.h"
#include "../../Event/EventDefs.h"
#include "../../Game/WorldNameConverter.h"

using namespace OUAN;

RenderComponentEntity::RenderComponentEntity(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_ENTITY)
{
	mCurrentAnimation=NULL;
	mCurrentAnimationName="";
	mEntity=NULL;
	mOldMaterials.clear();
}

RenderComponentEntity::~RenderComponentEntity()
{
	mEntity=NULL;
	for (TAnimationStateMap::iterator it=mAnimations.begin();it!=mAnimations.end();++it)
	{
		it->second=NULL;
	}
	mAnimations.clear();
}

Ogre::Entity* RenderComponentEntity::getEntity() const
{
	return mEntity;
}

void RenderComponentEntity::setEntity(Ogre::Entity* entity)
{
	mEntity=entity;

	if(mEntity)
	{
		mDreamsMaterial=WorldNameConverter::getDreamsName(mEntity->getSubEntity(0)->getMaterialName().c_str());
		mNightmaresMaterial=WorldNameConverter::getNightmaresName(mEntity->getSubEntity(0)->getMaterialName().c_str());
		mChangeWorldMaterial=WorldNameConverter::getChangeWorldName(mEntity->getSubEntity(0)->getMaterialName().c_str());
	}
}

void RenderComponentEntity::setVisible(bool visible)
{
	mEntity->setVisible(visible);
}
void RenderComponentEntity::initAnimations(std::vector<TRenderComponentEntityAnimParams> entityAnimParams)
{
	mAnimations.clear();
	mCurrentAnimationName="";
	if (mCurrentAnimation)
	{
		mCurrentAnimation=NULL; //Remember it is a pointer to an instance managed by Ogre, so we shouldn't delete it here.
	}
	if (!entityAnimParams.empty())
	{
		mIsAnimated=true;
		std::string animName;
		for (std::vector<TRenderComponentEntityAnimParams>::const_iterator it= entityAnimParams.begin();
			it!=entityAnimParams.end();++it)
		{
			if (mEntity)
			{
				animName=(*it).name;
				try
				{
					mAnimations[animName]=mEntity->getAnimationState(animName);
				}
				catch(Ogre::ItemIdentityException)
				{
					Logger::getInstance()->log("ANIMATION STATE NOT FOUND: "+animName);
				}
				if (mAnimations[animName])
				{
					mAnimations[animName]->setEnabled(false);
					mAnimations[animName]->setLoop((*it).loop);
				}
			}
		}
	}
	else mIsAnimated=false;
	//Initialise the animations mapping
}
void RenderComponentEntity::changeAnimation(const std::string& newAnimation /*TODO: Add options*/)
{
	if (mCurrentAnimation)
		mCurrentAnimation->setEnabled(false);

	mCurrentAnimationName=newAnimation;
	mCurrentAnimation= mAnimations[newAnimation];
	if (mCurrentAnimation)
	{
		mCurrentAnimation->setEnabled(true);		
		mCurrentAnimation->setTimePosition(0);
	}
}
Ogre::AnimationState* RenderComponentEntity::getCurrentAnimation() const
{
	return mCurrentAnimation;
}
std::string RenderComponentEntity::getCurrentAnimationName() const
{
	return mCurrentAnimationName;
}

bool RenderComponentEntity::isAnimated() const
{
	return mIsAnimated;
}
void RenderComponentEntity::update(double elapsedTime)
{
	if (mCurrentAnimation && mCurrentAnimation->getEnabled())
	{
		mCurrentAnimation->addTime(elapsedTime);//check what time unit arrives here
		if (mCurrentAnimation->hasEnded())
		{
			AnimationEndedEventPtr evt = AnimationEndedEventPtr(new AnimationEndedEvent(getParent(), mCurrentAnimation->getAnimationName()));
			getParent()->getGameWorldManager()->addEvent(evt);
		}
	}
}
void RenderComponentEntity::attachGameObjectToBone(const std::string& boneName,GameObjectPtr gameObject)
{
	bool isValidEntity = mEntity->hasSkeleton() && mEntity->getSkeleton()->hasBone(boneName);
	bool isValidGO = gameObject.get() && gameObject->hasRenderComponentEntity() && !gameObject->getEntityComponent()->getEntity()->isAttached();
	if ( isValidEntity && isValidGO)
	{		
		mEntity->attachObjectToBone(boneName,gameObject->getEntityComponent()->getEntity());
	}
	else
	{
		std::string msg = "RCENTITY - Invalid attempt to attach ";
		msg.append(gameObject.get()?gameObject->getName():"NULL");
		msg.append(" game object to ").append(getParent()->getName());
		Logger::getInstance()->log(msg);
	}
		
}
void RenderComponentEntity::detachGameObject(GameObjectPtr gameObject)
{
	if (gameObject.get() && gameObject->hasRenderComponentEntity())
	{
		mEntity->detachObjectFromBone(gameObject->getEntityComponent()->getEntity());
	}
}

void RenderComponentEntity::setMaterial(std::string material)
{
	Ogre::SubEntity* subEnt;
	Ogre::MaterialPtr original_material;
	unsigned int i;

	for ( i = 0; i < mEntity->getNumSubEntities(); i++)
	{
		// Get the material of this sub entity and build the clone material name
		subEnt = mEntity->getSubEntity(i);
		original_material = subEnt->getMaterial();

		// Get/Create the clone material

		if (Ogre::MaterialManager::getSingleton().resourceExists(material))
		{
			subEnt->setMaterial(Ogre::MaterialManager::getSingleton().getByName(material));
		}
		else
		{
			Logger::getInstance()->log("[RenderComponentEntity] material "+material+" does not exist.");
		}
	}
}

void RenderComponentEntity::setChangeWorldMaterials()
{
	setMaterial(mChangeWorldMaterial);
}

void RenderComponentEntity::setDreamsMaterials()
{
	setMaterial(mDreamsMaterial);
}

void RenderComponentEntity::setNightmaresMaterials()
{
	setMaterial(mNightmaresMaterial);
}
void RenderComponentEntity::applyTint(const Ogre::ColourValue& tintColour)
{
	Ogre::SubEntity* subEnt;
	Ogre::MaterialPtr material;
	Ogre::Pass* pass; 
	mTintColour=tintColour;

	for (unsigned int  i = 0; i < mEntity->getNumSubEntities(); i++)
	{		
		subEnt = mEntity->getSubEntity(i);
		material= subEnt->getMaterial();
		mOldMaterials[i]=material->getName();
		std::string oldMaterial=material->getName();

		int underscorePos=oldMaterial.find_last_of("_");
		if (underscorePos!=std::string::npos)
		{
			std::stringstream newName("");
			newName<<oldMaterial.substr(0,underscorePos)<<"_tint";
			if (Ogre::MaterialManager::getSingleton().resourceExists(newName.str()))
			{
				subEnt->setMaterialName(newName.str());
				material = subEnt->getMaterial();
				pass = material->getTechnique(0)->getPass(0);
				Ogre::GpuProgramParametersSharedPtr params = pass->getFragmentProgramParameters();
				if (params->_findNamedConstantDefinition("tintColour"))
				{
					params->setNamedConstant("tintColour", mTintColour);
				}
				if (params->_findNamedConstantDefinition("tintFactor"))
				{
					params->setNamedConstant("tintFactor", Ogre::Real(0.0));
				}				
			}
		}
	}
}
void RenderComponentEntity::removeTint()
{
	if (isTintBeingApplied())
	{
		Ogre::SubEntity* subEnt;
		Ogre::MaterialPtr material;
		for (unsigned int  i = 0; i < mEntity->getNumSubEntities(); i++)
		{		
			subEnt = mEntity->getSubEntity(i);
			subEnt->setMaterialName(mOldMaterials[i]);
		}
		mOldMaterials.clear();
	}	
}
void RenderComponentEntity::setTintFactor(double tintFactor)
{
	Ogre::MaterialPtr material;
	Ogre::Pass* pass; 
	for (unsigned int  i = 0; i < mEntity->getNumSubEntities(); i++)
	{	
		material = mEntity->getSubEntity(i)->getMaterial();
		pass = material->getTechnique(0)->getPass(0);
		Ogre::GpuProgramParametersSharedPtr params = pass->getFragmentProgramParameters();
		if (params->_findNamedConstantDefinition("tintFactor"))
		{
			params->setNamedConstant("tintFactor", Ogre::Real(tintFactor));
		}						
	}
}
bool RenderComponentEntity::isTintBeingApplied() const
{
	return !mOldMaterials.empty();
}

//void RenderComponentEntity::prepareForNormalMapping()
//{
//	//Ogre::MeshPtr mesh=mEntity->getMesh();
//	Ogre::String entityName=mEntity->getName();
//	Ogre::String meshName=mEntity->getMesh()->getName();
//	
//	//// Load the meshes with non-default HBU options
//	Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(
//		meshName,
//		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
//		Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY,
//		Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY,
//		true,true);
//	
//	// Build tangent vectors, all our meshes use only 1 texture coordset 
//	// Note we can build into VES_TANGENT now (SM2+)
//	unsigned short src, dest;
//	if (!mesh->suggestTangentVectorBuildParams(Ogre::VES_TANGENT, src, dest))
//	{
//		mesh->buildTangentVectors(Ogre::VES_TANGENT, src, dest);
//			// Second mode cleans mirrored / rotated UVs but requires quality models
//			//pMesh->buildTangentVectors(VES_TANGENT, src, dest, true, true);
//	}
//
//	Ogre::SceneManager* mgr=mParent->getGameWorldManager()->getParent()->getRenderSubsystem()->getSceneManager();
//	mgr->destroyEntity(entityName);
//	mEntity = mgr->createEntity(entityName,meshName);
//}

//--- Entity parameters

TRenderComponentEntityParameters::TRenderComponentEntityParameters() : TRenderComponentParameters()
{

}

TRenderComponentEntityParameters::~TRenderComponentEntityParameters()
{

}
//--- Subentities parameters

TRenderComponentSubEntityParameters::TRenderComponentSubEntityParameters() : TRenderComponentParameters()
{

}


TRenderComponentSubEntityParameters::~TRenderComponentSubEntityParameters()
{

}

//--- Entity animation parameters

TRenderComponentEntityAnimParams::TRenderComponentEntityAnimParams()
:TRenderComponentParameters()
{

}
TRenderComponentEntityAnimParams::~TRenderComponentEntityAnimParams()
{

}
