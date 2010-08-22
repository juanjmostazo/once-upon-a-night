#include "OUAN_Precompiled.h"

#include "RenderComponentEntity.h"
#include "RenderComponentPositional.h"
#include "../RenderSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameWorldManager.h"
#include "../../Event/EventDefs.h"
#include "../../Game/WorldNameConverter.h"

using namespace OUAN;

RenderComponentEntity::RenderComponentEntity(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_ENTITY)
,mEntity(NULL)
,mAnimationBlender(NULL)
{
	mOldMaterials.clear();

}

RenderComponentEntity::~RenderComponentEntity()
{
	mEntity=NULL;
	//for (TAnimationStateMap::iterator it=mAnimations.begin();it!=mAnimations.end();++it)
	//{
	//	it->second=NULL;
	//}
	mAnimations.clear();
}

Ogre::Entity* RenderComponentEntity::getEntity() const
{
	return mEntity;
}

void RenderComponentEntity::setEntity(Ogre::Entity* entity,bool existInDreams,bool existInNightmares)
{
	mEntity=entity;

	Ogre::SubEntity* subEnt;
	unsigned int i;

	mDreamsMaterial.clear();
	mNightmaresMaterial.clear();
	mChangeWorldMaterial.clear();

	if(mEntity)
	{
		for ( i = 0; i < mEntity->getNumSubEntities(); i++)
		{
			// Get the material of this sub entity and build the clone material name
			subEnt = mEntity->getSubEntity(i);

			if(subEnt)
			{
				mDreamsMaterial.push_back(WorldNameConverter::getDreamsName(subEnt->getMaterialName().c_str()));
				mNightmaresMaterial.push_back(WorldNameConverter::getNightmaresName(subEnt->getMaterialName().c_str()));
				mChangeWorldMaterial.push_back(WorldNameConverter::getChangeWorldName(subEnt->getMaterialName().c_str()));
				mChangeWorldMaterial[i]=setChangeWorldMaterialTransparentTextures(mChangeWorldMaterial[i],existInDreams,existInNightmares);
			}
		}
	}
}

void RenderComponentEntity::setVisible(bool visible)
{
	Ogre::SceneNode * pSceneNode;
	pSceneNode=getParent()->getPositionalComponent()->getSceneNode();

	if(visible)
	{
		if(!mEntity->isAttached())
		{
			pSceneNode->attachObject(mEntity);
		}
	}
	else
	{
		if(mEntity->isAttached() && mEntity->getParentSceneNode()->getName().compare(pSceneNode->getName())==0)
		{
			pSceneNode->detachObject(mEntity->getName());
		}
	}
}

bool RenderComponentEntity::isVisible()
{
	return mEntity->isAttached();
}
void RenderComponentEntity::initAnimationBlender(const std::string& defaultAnimation)
{
	SAFEDELETE(mAnimationBlender);
	mAnimationBlender=new AnimationBlender(mEntity);
	mAnimationBlender->init(defaultAnimation);
}
void RenderComponentEntity::destroyAnimationBlender()
{
	SAFEDELETE(mAnimationBlender);
}
void RenderComponentEntity::setAnimationBlenderVertexKeyMap(const TKeyFrameMap& keyFrameMap)
{
	if (mAnimationBlender)
		mAnimationBlender->setVertexPoseKeyFrames(keyFrameMap);
}
void RenderComponentEntity::initAnimations(std::vector<TRenderComponentEntityAnimParams> entityAnimParams)
{
	mAnimations.clear();
	if (!entityAnimParams.empty())
	{
		mIsAnimated=true;
		std::string animName;
		TAnimationData animData;
		TRenderComponentEntityAnimParams params;
		for (std::vector<TRenderComponentEntityAnimParams>::const_iterator it= entityAnimParams.begin();
			it!=entityAnimParams.end();++it)
		{
			if (mEntity)
			{
				params=(*it);
				animName=params.name;
				animData.name=animName;
				animData.loop=params.loop;
				animData.timescale=params.timescale;
				animData.transitions=params.transitions;
				
				mAnimations[animName]=animData;
			}
		}
	}
	else mIsAnimated=false;
}
void RenderComponentEntity::changeAnimation(const std::string& anim)
{
	TAnimationData oldAnimData= mAnimations[getCurrentAnimationName()];
	TAnimationData newAnimData= mAnimations[anim];

	if (!oldAnimData.transitions.empty() && 
		oldAnimData.transitions.find(anim)!=oldAnimData.transitions.end())
	{
		TTransitionData tranData = oldAnimData.transitions[anim];
		//Check if there's a source blend mask.
		if (!tranData.sourceBlendMask.empty())
		{
			mAnimationBlender->setBoneMask(tranData.sourceBlendMask);		
		}
		else mAnimationBlender->resetBoneMask();
		//Check for a target blend mask
		if (!tranData.targetBlendMask.empty())
		{
			mAnimationBlender->blend(anim,tranData.blendType,tranData.duration,tranData.targetBlendMask,newAnimData.loop,newAnimData.timescale);
		}
		else changeAnimation(anim,tranData.blendType,tranData.duration,newAnimData.loop,newAnimData.timescale);
	}
	else changeAnimation(anim,AnimationBlender::BT_SWITCH,0,newAnimData.loop,newAnimData.timescale);

}
void RenderComponentEntity::changeAnimation(const std::string& animation,AnimationBlender::TBlendingTransition transition, float duration, bool l/* =true */, float timeScale/* =1.0 */)
{
	if (mAnimationBlender)
		mAnimationBlender->blend(animation,transition,duration,l,timeScale);
}

bool RenderComponentEntity::isLoopingAnimation (const std::string& animationName)
{
	if (mEntity->getAnimationState(animationName))
		return mEntity->getAnimationState(animationName)->getLoop();
	return false;
}
bool RenderComponentEntity::hasFinishedAnimation(const std::string& animationName)
{
	if (mEntity->getAnimationState(animationName))
		return mEntity->getAnimationState(animationName)->hasEnded();
	return false;
}
Ogre::AnimationState* RenderComponentEntity::getCurrentAnimation() const
{
	if (mAnimationBlender)
		return mAnimationBlender->getSource();
	return NULL;
}
std::string RenderComponentEntity::getCurrentAnimationName() const
{
	if (mAnimationBlender)
	{
		return mAnimationBlender->getSource()->getAnimationName();
	}
	return "";
}
void RenderComponentEntity::setAnimationPosition(float pos)
{
	if (mAnimationBlender)
	{
		mAnimationBlender->setTimePosition(pos);
	}
}
float RenderComponentEntity::getCurrentAnimationLength() const
{
	if (mAnimationBlender)
		return mAnimationBlender->getSource()->getLength();
	return -1;
}
bool RenderComponentEntity::isAnimated() const
{
	return mIsAnimated;
}
void RenderComponentEntity::update(double elapsedTime)
{
	if(mEntity->isAttached())
	{
		if (mAnimationBlender)
		{
 			mAnimationBlender->addTime(elapsedTime);
			if (mAnimationBlender->hasEnded())
			{
				AnimationEndedEventPtr evt = AnimationEndedEventPtr(new AnimationEndedEvent(getParent(), getCurrentAnimationName()));
				getParent()->getGameWorldManager()->addEvent(evt);
			}
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

void RenderComponentEntity::setMaterial(std::vector<std::string> & material)
{
	Ogre::SubEntity* subEnt;
	Ogre::MaterialPtr original_material;
	unsigned int i;

	for ( i = 0; i < mEntity->getNumSubEntities(); i++)
	{
		// Get the material of this sub entity and build the clone material name
		subEnt = mEntity->getSubEntity(i);

		// Get/Create the clone material

		if (Ogre::MaterialManager::getSingleton().resourceExists(material[i]))
		{
			subEnt->setMaterial(Ogre::MaterialManager::getSingleton().getByName(material[i]));
		}
		else
		{
			Logger::getInstance()->log("[RenderComponentEntity] material "+material[i]+" does not exist.");
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

void RenderComponentEntity::setChangeWorldFactor(double factor)
{
	Ogre::Technique * technique;
	Ogre::Pass * pass;
	Ogre::GpuProgramParametersSharedPtr params;
	unsigned int i;

	for ( i = 0; i < mChangeWorldMaterial.size(); i++)
	{
		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(mChangeWorldMaterial[i]);

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

//--- Entity parameters

TRenderComponentEntityParameters::TRenderComponentEntityParameters() : TRenderComponentParameters()
,mInitManualAnimations(false)
,mManualAnimationName("")
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
